/**
 * @file graphStruct.h
 */

#ifndef GRAPHSTRUCT_H_
#define GRAPHSTRUCT_H_

typedef struct {

	int *nodes;
	int countNodes;
	int *edges;
	int countEdges;
	int *weights;
	int nmbEdges;
	char* name;

} Graph;

typedef struct {

	int countNodes;
	int *distance;
	int *predec;

} Route;

#endif /* GRAPHSTRUCT_H_ */
