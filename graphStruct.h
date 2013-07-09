/**
 * @file graphStruct.h
 * @brief Structures for storing graphs and calculated routes
 */

#ifndef GRAPHSTRUCT_H_
#define GRAPHSTRUCT_H_

/**
 * @struct Graph
 */
typedef struct {

	/**
	 * @brief Array of Integers to store the actual nodes. The number itself
	 * refers to the starting point in the Arrays edges and weights. Example:
	 * A nodes array filled with the values 0 and 3 would refer to the edges and
	 * weights array in the way that the corresponding values for the first edge
	 * are stored in the fields 0-2.
	 */
	int *nodes;
	/**
	 * @brief Number of nodes accessible in nodes
	 */
	int countNodes;
	/**
	 * @brief Array to store the edges
	 */
	int *edges;
	/**
	 * @brief Number of edges accessible in edges and weights
	 */
	int countEdges;
	/**
	 * @brief Array to the store the weight of each edge
	 */
	int *weights;
	/**
	 * @brief Number of edges per node
	 */
	int nmbEdges;
	/**
	 * @brief Name of the graph
	 */
	char* name;

} Graph;

/**
 * @struct Route
 */
typedef struct {

	/**
	 * @brief Number of nodes in the route
	 */
	int countNodes;
	/**
	 * @brief Distance to each node from the start node
	 */
	int *distance;
	/**
	 * @brief Predecessor for each node
	 */
	int *predec;

} Route;

#endif /* GRAPHSTRUCT_H_ */
