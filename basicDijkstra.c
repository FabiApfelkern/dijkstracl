/*
 * basicDijkstra.c
 *
 *  Created on: May 18, 2013
 *      Author: fabi
 */


#define I 998

#include "basicDijkstra.h"

int nodesEmpty(int *nodes, int countNodes) {
	int i;
	for (i = 0; i < countNodes; i++) {
		if (nodes[i] == 0)
			return 0;
	}
	return 1;
}


void init(Route *route, int start, int *nodes) {

	int i;
	for (i = 0; i < route->countNodes; i++) {
		route->distance[i] = I;
		route->predec[i] = 0;
		nodes[i] = 0;
	}

	route->distance[start] = 0;
}

void updateDistance(Route *route, int weight, int node1, int node2) {

	int alt = route->distance[node1] + weight;
	if(alt < route->distance[node2]) {
		route->distance[node2] = alt;
		route->predec[node2] = node1;
	}

}

void basicDijkstra(Graph *graph, Route *route, int start){

	int *q = malloc(graph->countNodes * sizeof(int));
	init(route, start, q);

	// As long there are any nodes left
	while(!nodesEmpty(q, graph->countNodes)) {
		int smallestDist = I;
		int i;
		int node1, node2;

		// Search node with smallest value in distance
		// Do this in parallel
		for (i = 0; i < graph->countNodes; i++) {
			/*
			 * Usually we have just a smaller sign here,
			 * but the test data is not a valid graph.
			 *
			 */
			if(q[i] == 0 && route->distance[i] <= smallestDist) {
				node1 = i;
				smallestDist = route->distance[i];
			}
		}
		// Remove node from node list
		q[node1] = 1;

		// Determine distance for every neighbor
		// Do this in parallel

		int begin = graph->nodes[node1];
		int end;
		if(node1 + 1 < (graph->countNodes)) {
			end = graph->nodes[node1 + 1];
		} else {
			end = graph->countEdges;
		}

		for (i = begin; i < end; i++) {
				if(q[graph->edges[i]] == 0) {
					updateDistance(route, graph->weights[i], node1, graph->edges[i]);
				}

		}
	}

	free(q);

}
