/**
 * @file core.h
 * @brief Structures the program cycle
 */

#ifndef CORE_H_
#define CORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "graphCreator.h"
#include "basicDijkstra.h"
#include "clDijkstra.h"
#include "advDijkstra.h"
#include "graphStruct.h"

/**
 * @brief Global variable for the time measurement
 */
struct timespec CALCULATION_START;
/**
 * @brief Global variable for the time measurement
 */
struct timespec CALCULATION_END;

#define I 998

Graph initGraph(char* graphName, int countNodes, int countEdges);

/**
 * @brief Function to handle the creation of graphs
 *
 * The function parses the parameters and creates a new
 * graph. It utilizes the functions provided by @link graphCreator.h @endlink
 *
 * @param argc
 * @param argv
 */
void createGraph(int argc, char **argv);

/**
 * @brief Wraps the different methods of calculating
 *
 * The function parses the parameters and calculates the
 * route with the specified method set in option.
 * It allocates the necessary memory structured as @link Graph @endlink .
 * The method are defined in @link basicDijkstra.c @endlink, @link advDijkstra.c @endlink
 * and @link clDijkstra.c @endlink.
 * If the 4. parameter is set with a node number the
 * function displays the exact route to this node as well. (see @link getResult @endlink)
 * Furthermore it outputs the calculation time of the respective
 * algorithm. It return the calculated route.
 *
 * @param option The desired calculating method ('b', 'o', 'c')
 * @param argc
 * @param argv
 * @return Route The calculated route
 */
Route calculatePath(char option, int argc, char **argv);

/**
 * @brief Displays the precise route to the specified target node
 *
 * The function traverses the predecessor array to determine the precise
 * route from the start node (0) to the specified target node and displays
 * it. If the node is not part of the graph or not reachable it displays
 * adequate error messages.
 *
 * @param target The desired target
 * @param Route A already calculated Route struct
 */
void getResult(int target, Route *route);

/**
 * @brief Displays the help text
 */
void help(void);

/**
 * @brief Encapsulates the main entry point.
 *
 * This function should be called from the C-Main-Function. (see @link dijkstracl.c @endlink)
 * Some pre-validation of the user input is performed and the
 * selected option is delegated to a matching function.
 *
 * @param argc
 * @param argv
 * @return Status code
 */
int mainProgram(int argc, char **argv);

#endif /* CORE_H_ */
