/**
 * @file clDijstraKernel.cl
 * @brief The OpenCL Dijkstra Kernels
 *
 * This file contains the two OpenCL Kernels described
 * in the paper "Accelerating large graph algorithms on the GPU using CUDA"
 * by Pawan Harish and P. J. Narayanan.
 * 
 */

#define I 998
/**
 * @brief Kernel 1 to go through every node and determine the shortest way
 * 
 * This is the Kernel labeled as "CUDA_SSSP_KERNEL1" from the paper.
 * Each execution of it deals with one node.
 *
 * @param distance Distance array to store the calculated distances
 * @param updateDistance Helper array to store intermediate distance results
 * @param preced Array to store the determined predecessor
 * @param updatePreced Helper array to store intermediate predecessors
 * @param visited Array with the already visited nodes
 * @param nodes The actual nodes
 * @param edges The edges for each node
 * @param weights The weights for each edge
 * @param countNodes Number of nodes
 * @param countEdges Number of edges
 */
__kernel void dijkstraKernel1(
		__global int *distance,
		__global int *updateDistance,
		__global int *preced,
		__global int *updatePreced,
		__global int *visited,
		__global int *nodes,
		__global int *edges,
		__global int *weights,
		int countNodes,
		int countEdges
		)
{
	// Get the current node wrom the workitem id
	int t = get_global_id(0);
	int old, i;
	
	// Is it still unvisited
	if (visited[t] == 0) {
		// Mark as visited
		visited[t] = 1;
		
		// Get the neighbours
		int begin = nodes[t];
		int end;
		if(t + 1 < (countNodes)) {
			end = nodes[t + 1];
		} else {
			end = countEdges;
		}
		
		int edge;
		// Loop through the neighbors
		for (i = begin; i < end; i++) {
			edge = edges[i];
			old = distance[t] + weights[i];
			// Its shorter than the old one
			if(old <= updateDistance[edge]) {
				updateDistance[edge] = old;
				updatePreced[edge] = t;
			}
			
		}
	}

}

/**
 * @brief Kernel 2 checks if the calculated intermediate shortest path is
 * actually the shortest one
 *
 * This is the Kernel labeled as "CUDA_SSSP_KERNEL2" from the paper.
 * Each execution of it deals with one node. According
 * to the paper the seperation of the Kernels is necessary due to
 * some possible race conditions otherwise.
 *
 * @param distance Distance array to store the calculated distances
 * @param updateDistance Helper array to store intermediate distance results
 * @param preced Array to store the determined predecessor
 * @param updatePreced Helper array to store intermediate predecessors
 * @param visited Array with the already visited nodes
 */
__kernel void dijkstraKernel2(
		__global int *distance,
		__global int *updateDistance,
		__global int *preced,
		__global int *updatePreced,
		__global int *visited
		)
{
	// Get the current node wrom the workitem id
	int t = get_global_id(0);
	
	// Check if the new distance is actually shorter
	if (distance[t] > updateDistance[t]) {	
		distance[t] = updateDistance[t];
		preced[t] = updatePreced[t];
		// Reset visited state
		visited[t] = 0;
	}

	updatePreced[t] = preced[t];
	updateDistance[t] = distance[t];
}

