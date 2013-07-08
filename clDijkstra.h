/**
 * @file clDijkstra.h
 */

#ifndef CLDIJKSTRA_H_
#define CLDIJKSTRA_H_

#include <stdlib.h>
#include "graphStruct.h"

void clDijkstra(Graph *graph, Route *route, int start);
char *read_file_contents(const char *filename);

#endif /* BASICDIJKSTRA_H_ */
