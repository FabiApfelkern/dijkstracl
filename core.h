/**
 * @file core.h
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

struct timespec CALCULATION_START, CALCULATION_END;

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
 * @param option
 * @param argc
 * @param argv
 * @return Route
 */
Route calculatePath(char option, int argc, char **argv);

/**
 *
 *
 * @param target
 * @param Route route
 */
void getResult(int target, Route *route);

/**
 * Displays the help text
 */
void help(void);
int mainProgram(int argc, char **argv);
void myClock(time_t start);


#endif /* CORE_H_ */
