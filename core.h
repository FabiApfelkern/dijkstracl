/*
 * core.h
 *
 *  Created on: Jun 14, 2013
 *      Author: fabi
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


Graph initGraph(char* graphName, int countNodes, int countEdges);
/**
 * Displays the interactive mode to create a graph.
 *
 * @param argc
 * @param argv
 */
void createGraph(int argc, char **argv);
Route calculatePath(char option, int argc, char **argv);
void getResult(int target, int *predec, int *distance, int countNodes);

/**
 * Display the help text
 */
void help(void);
int mainProgram(int argc, char **argv);
void myClock(time_t start);


#endif /* CORE_H_ */
