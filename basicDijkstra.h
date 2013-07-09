/**
 * @file basicDijkstra.h
 * @brief A very basic Dijkstra algorithm without any optimization
 */

#ifndef BASICDIJKSTRA_H_
#define BASICDIJKSTRA_H_

#include <stdlib.h>
#include "graphStruct.h"

/**
 * @brief Calculates the shortest routes with a basic Dijkstra algorithm
 *
 * The function takes a Graph struct a calculates the distance and
 * the predecessor for every node for the given start node. It stores
 * the results into the Route struct.
 *
 * @param graph A filled Graph struct
 * @param route A initialized Route struct
 * @param start The start node
 */
void basicDijkstra(Graph *graph, Route *route, int start);

/**
 * @brief Updated the distance between two nodes
 *
 * The function takes to nodes and determines if the
 * the route via the node1 to node2 is shorter than the
 * already known route for node2. In this case it updates
 * the regarding field in the distance array
 *
 * @param route The Route struct
 * @param weight The weight between the two nodes
 * @param node1
 * @param node2
 */
void updateDistance(Route *route, int weight, int node1, int node2);

#endif /* BASICDIJKSTRA_H_ */
