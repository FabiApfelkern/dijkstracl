/**
 * @file graphCreator.h
 */

#ifndef GRAPHCREATOR_H_
#define GRAPHCREATOR_H_

#include "graphStruct.h"

int gcGraphExists(char* graphName);
char* gcBuildPath(char* graphName);
int gcSaveGraph(Graph *graph);
void gcOpenGraph(Graph *graph);
void gcGetDimension(Graph *graph);
void gcCreateRandomGraph(Graph *graph);


#endif /* FILEWRITER_H_ */
