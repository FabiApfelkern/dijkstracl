/*
 * basicDijkstra.h
 *
 *  Created on: May 18, 2013
 *      Author: fabi
 */

#ifndef CLDIJKSTRA_H_
#define CLDIJKSTRA_H_

#include <stdlib.h>
#include "graphStruct.h"

void clDijkstra(Graph *graph, Route *route, int start);
void clInit(Route *route, int start, int *nodes);
int clNodesEmpty(int *nodes, int dimension);


#endif /* BASICDIJKSTRA_H_ */
