/*
 * basicDijkstra.h
 *
 *  Created on: May 18, 2013
 *      Author: fabi
 */

#ifndef BASICDIJKSTRA_H_
#define BASICDIJKSTRA_H_

#include <stdlib.h>
#include "graphStruct.h"

void basicDijkstra(Graph *graph, Route *route, int start);
void init(Route *route, int start, int *nodes);
void updateDistance(Route *route, int weight, int node1, int node2);
int nodesEmpty(int *nodes, int countNodes);


#endif /* BASICDIJKSTRA_H_ */
