/**
 * @file commonDijkstra.h
 * @brief Common function, uses by all Dijkstra implementations
 */


#ifndef COMMONDIJKSTRA_H_
#define COMMONDIJKSTRA_H_

#include "graphStruct.h"

/**
 * @brief Initializes the Route struct
 *
 * The function takes an already allocated
 * Route struct and initializes the contained
 * array with the necessary values. The distances
 * are set to infinity (defined as 998) and the
 * predecessors to -1 (as no predecessor yet).
 * The nodes array is set to 0.
 *
 * @param route An empty Route struct
 * @param start The start node
 * @param nodes The array for already visited nodes
 */
void init(Route *route, int start, int *nodes);

/**
 * @brief Checks if the nodes array is already empty
 *
 * @param nodes The array for already visited nodes
 * @param countNodes
 * @return 0 - still nodes left, 1 - all nodes visited
 */
int nodesEmpty(int *nodes, int countNodes);


#endif /* COMMONDIJKSTRA_H_ */
