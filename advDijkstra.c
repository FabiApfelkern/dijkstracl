/**
 * @file advDijkstra.c
 * @brief A more advanced and optimized Dijkstra algorithm
 */

#include "advDijkstra.h"
#include "commonDijkstra.h"
#include "core.h"
#include <time.h>


void advDijkstra(Graph *graph, Route *route, int start) {

	clock_gettime(CLOCK_REALTIME, &CALCULATION_START);
	int *q = malloc(graph->countNodes * sizeof(int));
	init(route, start, q);

	// Init the helper arrays to store intermediate results
	int *updateDistance = malloc(graph->countNodes * sizeof(int));
	int *updatePredec = malloc(graph->countNodes * sizeof(int));
	int i;
	for(i = 0; i < graph->countNodes; i++) {
		updateDistance[i] = I;
		updatePredec[i] = -1;
	}
	updateDistance[0] = 0;

	// As long there are any nodes left
	while (!nodesEmpty(q, graph->countNodes)) {

		int t;
		// Loop through all nodes of the graph
		// This represents the the Kernel 1
		for (t = 0; t < graph->countNodes; t++) {

			int old, i;
			if (q[t] == 0) {
				q[t] = 1;

				// Determine neighbors
				int begin = graph->nodes[t];
				int end;
				if (t + 1 < (graph->countNodes)) {
					end = graph->nodes[t + 1];
				} else {
					end = graph->countEdges;
				}

				int edge;
				// Set distance to neighbor and store it in the helper array
				for (i = begin; i < end; i++) {
					edge = graph->edges[i];
					old = route->distance[t] + graph->weights[i];
					if (old <= updateDistance[edge]) {
						updateDistance[edge] = old;
						updatePredec[edge] = t;
					}

				}
			}
		}

		// Loop again over all nodes
		// This represents the the Kernel 2
		for (t = 0; t < graph->countNodes; t++) {
			// Check if the new distance may be shorter than the previous calculated one
			if (route->distance[t] > updateDistance[t]) {
				route->distance[t] = updateDistance[t];
				route->predec[t] = updatePredec[t];
				q[t] = 0;
			}

			updateDistance[t] = route->distance[t];
			updatePredec[t] = route->predec[t];
		}

	}

	free(q);
	clock_gettime(CLOCK_REALTIME, &CALCULATION_END);
}
