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
char *read_file_contents(const char *filename);

#endif /* BASICDIJKSTRA_H_ */
