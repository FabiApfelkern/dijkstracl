/**
 * @file basicDijkstra.h
 */

#ifndef BASICDIJKSTRA_H_
#define BASICDIJKSTRA_H_

#include <stdlib.h>
#include "graphStruct.h"

void basicDijkstra(Graph *graph, Route *route, int start);
void updateDistance(Route *route, int weight, int node1, int node2);

#endif /* BASICDIJKSTRA_H_ */
