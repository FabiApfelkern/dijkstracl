/*
 * fileWriter.c
 *
 *  Created on: May 18, 2013
 *      Author: fabi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graphCreator.h"
#include "graphStruct.h"

#define MAX 7
#define I 998

const char* GRAPHPATH = "graphs";
const char* RESULTPATH = "results";

/**
 * Checks, if the file exists already
 *
 * @param graphName
 * @return 0 - file does not exist, 1 - file exists
 */
int gcGraphExists(char* graphName) {
	FILE *file;
	char* path = gcBuildPath(graphName);
	file = fopen(path, "r");
	if (file) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * Creates the path to open graph file
 *
 * @param graphName
 * @return relative path to the graph file
 */
char* gcBuildPath(char* graphName) {
	int size = strlen(graphName) + strlen(GRAPHPATH) + 2;
	char* path = malloc(size);
	snprintf(path, size, "%s/%s", GRAPHPATH, graphName);
	return path;
}

char* gcBuildResultPath(char* name) {
	int size = strlen(name) + strlen(RESULTPATH) + 2;
	char* path = malloc(size);
	snprintf(path, size, "%s/%s", RESULTPATH, name);
	return path;
}


int gcSaveGraph(Graph *graph) {

	FILE *file;
	char* path = gcBuildPath(graph->name);
	file = fopen(path, "w+");
	if (!file) {
		return 0;
	}

	int i;

	fprintf(file, "%d %d %d\n", graph->countNodes, graph->countEdges, graph->nmbEdges);
	for (i = 0; i < graph->countNodes; i++) {
		fprintf(file, "%d ", graph->nodes[i]);
	}
	fprintf(file, "\n");
	for (i = 0; i < graph->countEdges; i++) {
		fprintf(file, "%d ", graph->edges[i]);
	}
	fprintf(file, "\n");
	for (i = 0; i < graph->countEdges; i++) {
		fprintf(file, "%d ", graph->weights[i]);
	}
	fprintf(file, "\n");
	fclose(file);

	return 1;

}

void gcOpenGraph(Graph *graph) {

	FILE *file;
	char* path = gcBuildPath(graph->name);
	file = fopen(path, "r");
	int scan = 0;

	int i, dummy;
	scan = fscanf(file, "%d %d %d\n", &dummy, &dummy, &dummy);


	for (i = 0; i < graph->countNodes; i++) {
		scan = fscanf(file, "%d ", &graph->nodes[i]);
	}

	for (i = 0; i < graph->countEdges; i++) {
		scan = fscanf(file, "%d ", &graph->edges[i]);
	}

	for (i = 0; i < graph->countEdges; i++) {
		scan = fscanf(file, "%d ", &graph->weights[i]);
	}

	(void)scan;
	fclose(file);
}

void gcGetDimension(Graph *graph) {
	FILE *file;
	char* path = gcBuildPath(graph->name);
	file = fopen(path, "r");
	int scan = fscanf(file, "%d %d %d\n", &graph->countNodes, &graph->countEdges, &graph->nmbEdges);
	(void)scan;
	fclose(file);
}

void gcCreateRandomGraph(Graph *graph) {

	int i,j,pos,edge;
	srand(time(NULL));
	for(i = 0; i < graph->countNodes; i++) {
		graph->nodes[i] = i *graph->nmbEdges;

		for(j=0; j < graph->nmbEdges; j++) {
			edge = (rand() % graph->countNodes);
			while(edge == i) {
				edge = (rand() % graph->countNodes);
			}
			pos = (i*graph->nmbEdges)+j;
			graph->edges[pos] = edge;
			graph->weights[pos] = (rand() % 15) + 1;
		}
	}

//	for(i = 0; i < graph->countEdges; i++) {
//
//		while(edge != i) {
//			edge = (rand() % graph->countNodes);
//		}
//
//		graph->edges[i] =
//		graph->weights[i] = (rand() % 15) + 1;
//
//	}
}

int gcSaveResult(char* name, int* predec, int* distance, int size) {

	FILE *file;
	char* path = gcBuildResultPath(name);
	file = fopen(path, "w+");
	if (!file) {
		return 0;
	}

	int i;
	fprintf(file, "%d\n", size);
	for (i = 0; i < size; i++) {
		fprintf(file, "%d ", distance[i]);
	}
	fprintf(file, "\n");
	for (i = 0; i < size; i++) {
		fprintf(file, "%d ", predec[i]);
	}
	fprintf(file, "\n");
	fclose(file);

	return 1;
}



