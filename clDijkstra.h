/**
 * @file clDijkstra.h
 * @brief The Dijkstra algorithm with OpenCL
 */

#ifndef CLDIJKSTRA_H_
#define CLDIJKSTRA_H_

#include <stdlib.h>
#include "graphStruct.h"

/**
 * @brief Calculates the shortest routes with a Dijkstra algorithm and OpenCL
 *
 * The function implements the proposal of the paper
 * "Accelerating large graph algorithms on the GPU using CUDA" and implements
 * the Dijkstra algorithm with OpenCL.
 * The function initializes the OpenCL environment and platform, loads the Kernels
 * (see @link clDijkstraKernel.cl @endlink) and enqueues the Kernels.
 *
 * @param graph A filled Graph struct
 * @param route A initialized Route struct
 * @param start The start node
 */
void clDijkstra(Graph *graph, Route *route, int start);

/**
 * @brief Reads Kernel file
 *
 *
 * @param filename Kernel filename
 * @return Content of the Kernel file
 */
char *read_file_contents(const char *filename);

#endif /* BASICDIJKSTRA_H_ */
