/**
 * @file advDijkstra.h
 * @brief A more advanced and optimized Dijkstra algorithm
 */

#ifndef ADVDIJKSTRA_H_
#define ADVDIJKSTRA_H_

#include <stdlib.h>
#include "graphStruct.h"

/**
 * @brief Calculates the shortest routes with an optimized Dijkstra algorithm
 *
 * This is the reference implementation of the Dijkstra algorithm
 * proposed in the paper "Accelerating large graph algorithms on the GPU using CUDA".
 * Its purpose is to verify the accuracy of the OpenCL implementation of
 * this algorithm. Furthermore it is much faster than the basic algorithm
 * even without the utilization of OpenCL.
 *
 * @param graph A filled Graph struct
 * @param route A initialized Route struct
 * @param start The start node
 */
void advDijkstra(Graph *graph, Route *route, int start);

#endif /* BASICDIJKSTRA_H_ */
