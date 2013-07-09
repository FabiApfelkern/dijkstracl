/**
 * @file graphCreator.h
 * @brief Provides functions for the Graph creation and handling
 */

#ifndef GRAPHCREATOR_H_
#define GRAPHCREATOR_H_

#include "graphStruct.h"

/**
 * @brief Checks, if the graph file exists already
 *
 * @param graphName
 * @return 0 - file does not exist, 1 - file exists
 */
int gcGraphExists(char* graphName);

/**
 * @brief Builds the relative path to the given Graph
 *
 * @param graphName
 * @return Relative path of the Graph
 */
char* gcBuildPath(char* graphName);

/**
 * @brief Saves the Graph struct to the disk
 *
 * The function saves a given Graph struct to the hard disk.
 * In converts the arrays of the struct into a simple ASCII
 * representation a writes it into a file. The filename
 * is specified in the struct.
 * (see @link graphStruct.h @endlink)
 *
 * @param graph
 * @return 0 - Failure, 1 - Success
 */
int gcSaveGraph(Graph *graph);

/**
 * @brief Opens a Graph struct from the disk
 *
 * The function parses a graph file from the disk
 * and transfers the data into the given Graph struct.
 * The filename has to be pre-defined in the Graph struct.
 * (see @link graphStruct.h @endlink)
 * Important: The needed memory of the Graph struct has to
 * be allocated before the function call. Please take advantage
 * of the function @link gcGetDimension @endlink to determine
 * the necessary array size.
 *
 * @param graph
 */
void gcOpenGraph(Graph *graph);

/**
 * @brief Determines the number of nodes, edges from a Graph struct file
 *
 * The function opens a Graph file, already specified in
 * the Graph struct and stores the number of nodes, edges and edges
 * per node in the struct. Those numbers are needed to allocate
 * the memory for the Graph struct.
 *
 * @param graph
 */
void gcGetDimension(Graph *graph);

/**
 * @brief Fills a graph struct with random values
 *
 * The function takes a Graph struct and fills it
 * with random values. Note: The struct has to be
 * initialized and completely allocated already.
 * The values are generated purely randomly.
 *
 * @param graph
 */
void gcCreateRandomGraph(Graph *graph);


#endif /* FILEWRITER_H_ */
