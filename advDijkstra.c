/*
 * basicDijkstra.c
 *
 *  Created on: May 18, 2013
 *      Author: fabi
 */


#include "advDijkstra.h"
#include "commonDijkstra.h"
#include "core.h"
#include <time.h>


void advDijkstra(Graph *graph, Route *route, int start) {

	clock_gettime(CLOCK_REALTIME, &CALCULATION_START);
	int *q = malloc(graph->countNodes * sizeof(int));
	init(route, start, q);

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
		for (t = 0; t < graph->countNodes; t++) {

			int old, i;
			if (q[t] == 0) {
				q[t] = 1;

				int begin = graph->nodes[t];
				int end;
				if (t + 1 < (graph->countNodes)) {
					end = graph->nodes[t + 1];
				} else {
					end = graph->countEdges;
				}

				int edge;
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

		for (t = 0; t < graph->countNodes; t++) {
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
