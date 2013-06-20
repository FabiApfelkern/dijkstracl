/*
 * fileWriter.h
 *
 *  Created on: May 18, 2013
 *      Author: fabi
 */

#ifndef GRAPHCREATOR_H_
#define GRAPHCREATOR_H_

#include "graphStruct.h"

int gcGraphExists(char* graphName);
char* gcBuildPath(char* graphName);
char* gcBuildResultPath(char* name);
int gcSaveGraph(Graph *graph);
void gcOpenGraph(Graph *graph);
void gcGetDimension(Graph *graph);
void gcCreateRandomGraph(Graph *graph);
int gcSaveResult(char* name, int* predec, int* distance, int size);


#endif /* FILEWRITER_H_ */
