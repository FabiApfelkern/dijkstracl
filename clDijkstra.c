/*
 * basicDijkstra.c
 *
 *  Created on: May 18, 2013
 *      Author: fabi
 */


#define I 998

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CL/cl.h>
#include "clDijkstra.h"

static char *read_file_contents(const char *filename)
{
	long size;
	char *ret = NULL;
	char *contents = NULL;
	FILE *fh;

	if (!(fh = fopen(filename,"r")))
		return NULL;

	fseek(fh,0,SEEK_END);
	size = ftell(fh);
	if (size < 1)
		goto out;
	fseek(fh,0,SEEK_SET);

	if (!(contents = malloc(size+1)))
		goto out;
	if ((fread(contents, 1, size, fh) != size))
		goto out;

	contents[size] = 0;

	ret = contents;
	contents = NULL;
out:
	fclose(fh);
	free(contents);
	return ret;
}

int clNodesEmpty(int *nodes, int dimension) {
	int i;
	for (i = 0; i < dimension; i++) {
		if (nodes[i] == 0)
			return 0;
	}
	return 1;
}

void clInit(Route *route, int start, int *nodes) {

	int i;
	for (i = 0; i < route->countNodes; i++) {
		route->distance[i] = I;
		route->predec[i] = -1;
		nodes[i] = 0;
	}
	route->distance[start] = 0;
}


void clDijkstra(Graph *graph, Route *route, int start) {

	/* The Kernels */
	char *dijkstraKernel = "dijkstra.cl";

	/* The error variable. We need it everywhere */
	cl_int error;

	/* Phase 1 variables */
	cl_platform_id platform;
	cl_device_id device;
	cl_uint platforms, devices;
	char name[128];

	/* Phase 2 variables */
	char *k_src = NULL; /* kernel source */
	cl_context context = NULL;

	/**** Phase 1: Find platform and device (will OpenCL work at all?) *****/

	/* Fetch available platform; we only want the first one. */
	error = clGetPlatformIDs(1, &platform, &platforms);
	if (error != CL_SUCCESS) {
		fprintf(stderr, "Couldn't get platform ids\n");
		goto out;
	}
	printf("Number of available platforms = %d\n",platforms);

	/* Get the name of the platform and print it */
	error = clGetPlatformInfo(platform, CL_PLATFORM_NAME, sizeof(name), name, NULL);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't get platform name\n");
		goto out;
	}
	printf("Platform = %s\n",name);

	/* Now get the first device of our platform */
	error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &devices);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't get device ids\n");
		goto out;
	}

	/**** Phase 2: Create the context and all of its associates *****/

	/* Create a CL context for the selected device, note that nVidia's OpenCL requires the platform property */
	cl_context_properties properties[]= { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 };

	context = clCreateContext(properties, 1, &device, NULL, NULL, &error);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't create the context\n");
		goto out;
	}

	/* Now create the command queue */
	cl_command_queue cq = clCreateCommandQueue(context, device, 0, &error);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't create the command queue\n");
		goto out;
	}

	/* Now read in the file with the kernel */
    if (!(k_src = read_file_contents(dijkstraKernel)))
    {
		fprintf(stderr,"Couldn't read the contents of the kernel file!\n");
		goto out;
    }

    /* Array of all sources, we only have one source file */
	const char *srcptr[]={k_src};

	/* Submit the just loaded source code to OpenCL. The resulting
	 * program/kernel is associated with the given context */
	cl_program prog = clCreateProgramWithSource(context, 1, srcptr, NULL, &error);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't create the kernel from source\n");
		goto out;
	}

	/* Now compile */
	error = clBuildProgram(prog, 0, NULL, "", NULL, NULL);
	if (error != CL_SUCCESS )
	{
		char build_c[4096];

		fprintf(stderr, "Error on buildProgram\n");
		fprintf(stderr, "\nRequestingInfo\n");
		clGetProgramBuildInfo( prog, device, CL_PROGRAM_BUILD_LOG, sizeof(build_c), build_c, NULL );
		fprintf(stderr, "Build Log for %s_program:\n%s\n", "dijkstra", build_c );
		goto out;
	}



	/******** Dijkstra itself *********/

	int *nodes = malloc(graph->countNodes * sizeof(int));
	clInit(route, start, nodes);

	int *updateDistance = malloc(graph->countNodes * sizeof(int));
	int i;
	for(i = 0; i < graph->countNodes; i++) {
		updateDistance[i] = I;
	}
	updateDistance[0] = 0;
	int lastEdge;


	/* Allocate the input memory for the kernel. */
	cl_mem clDistance = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int)*graph->countNodes, route->distance, &error);
	cl_mem clUpdateDistance = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int)*graph->countNodes, updateDistance, &error);
	cl_mem clPreced = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int)*graph->countNodes, route->predec, &error);
	cl_mem clVisited = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int)*graph->countNodes, nodes, &error);
	cl_mem clNodes = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int)*graph->countNodes, graph->nodes, &error);
	cl_mem clEdges = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int)*graph->countEdges, graph->edges, &error);
	cl_mem clWeights = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int)*graph->countEdges, graph->weights, &error);
	cl_mem clLastEdge = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,  sizeof(int), &lastEdge, &error);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't create buffers!\n");
		goto out;
	}

	/* We now get access to a kernel handle */
	cl_kernel kernel1 = clCreateKernel(prog, "dijkstraKernel1", &error);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't create kernel!\n");
		goto out;
	}
	/* PARAMETERS */
	error = clSetKernelArg(kernel1, 0, sizeof(cl_mem), &clDistance);
	error = clSetKernelArg(kernel1, 1, sizeof(cl_mem), &clUpdateDistance);
	error = clSetKernelArg(kernel1, 2, sizeof(cl_mem), &clPreced);
	error = clSetKernelArg(kernel1, 3, sizeof(cl_mem), &clVisited);
	error = clSetKernelArg(kernel1, 4, sizeof(cl_mem), &clNodes);
	error = clSetKernelArg(kernel1, 5, sizeof(cl_mem), &clEdges);
	error = clSetKernelArg(kernel1, 6, sizeof(cl_mem), &clWeights);
	error = clSetKernelArg(kernel1, 7, sizeof(int), &graph->countNodes);
	error = clSetKernelArg(kernel1, 8, sizeof(int), &graph->countEdges);
	error = clSetKernelArg(kernel1, 9, sizeof(cl_mem), &clLastEdge);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't set argument for kernel!\n");
		goto out;
	}


	/* We now get access to a kernel handle */
	cl_kernel kernel2 = clCreateKernel(prog, "dijkstraKernel2", &error);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't create kernel!\n");
		goto out;
	}
	/* PARAMETERS */
	error = clSetKernelArg(kernel2, 0, sizeof(cl_mem), &clDistance);
	error = clSetKernelArg(kernel2, 1, sizeof(cl_mem), &clUpdateDistance);
	error = clSetKernelArg(kernel2, 2, sizeof(cl_mem), &clPreced);
	error = clSetKernelArg(kernel2, 3, sizeof(cl_mem), &clVisited);
	error = clSetKernelArg(kernel2, 4, sizeof(cl_mem), &clLastEdge);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't set argument for kernel!\n");
		goto out;
	}


	cl_event readDone;

	const size_t worksize = graph->countNodes;
	// As long there are any nodes left
	while (!clNodesEmpty(nodes, graph->countNodes)) {


		error = clEnqueueNDRangeKernel(cq, kernel1, 1, NULL, &worksize, NULL, 0, NULL, NULL);
		if (error != CL_SUCCESS)
		{
			fprintf(stderr,"Couldn't enqueue the kernel1!\n");
			goto out;
		}

		error = clEnqueueNDRangeKernel(cq, kernel2, 1, NULL, &worksize, NULL, 0, NULL, NULL );
		if (error != CL_SUCCESS) {
			fprintf(stderr, "Couldn't enqueue the kernel2!\n");
			goto out;
		}

		/* Read the result back into buf2 */
		error = clEnqueueReadBuffer(cq, clVisited, CL_FALSE, 0, sizeof(int)*graph->countNodes, nodes, 0, NULL, &readDone);
		if (error != CL_SUCCESS)
		{
			fprintf(stderr,"Couldn't read buffer back!\n");
			goto out;
		}
		clWaitForEvents(1, &readDone);

	}

	/* Read the result back into buf2 */
	error = clEnqueueReadBuffer(cq, clDistance, CL_FALSE, 0, sizeof(int)*graph->countNodes, route->distance, 0, NULL, &readDone);
	error = clEnqueueReadBuffer(cq, clPreced, CL_FALSE, 0, sizeof(int)*graph->countNodes, route->predec, 0, NULL, &readDone);
	if (error != CL_SUCCESS)
	{
		fprintf(stderr,"Couldn't read buffer back!\n");
		goto out;
	}
	clWaitForEvents(1, &readDone);

	clReleaseMemObject(clDistance);
	clReleaseMemObject(clVisited);
	clReleaseMemObject(clNodes);
	clReleaseMemObject(clPreced);
	clReleaseMemObject(clUpdateDistance);
	clReleaseMemObject(clEdges);
	clReleaseMemObject(clWeights);

	free(nodes);
	free(updateDistance);


	out:
	if (error != CL_SUCCESS)
	fprintf(stderr, "Error number %d\n", error);

}
