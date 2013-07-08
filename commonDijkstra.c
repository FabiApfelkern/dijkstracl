/**
 * @file commonDijkstra.c
 */

#include "commonDijkstra.h"
#include "core.h"

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
		route->predec[i] = -1;
		nodes[i] = 0;
	}

	route->distance[start] = 0;
}

