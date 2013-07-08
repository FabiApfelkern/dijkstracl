#include <assert.h>

#include "graphCreator.c"
#include "commonDijkstra.c"
#include "clDijkstra.c"
#include "advDijkstra.c"
#include "graphStruct.h"
#include "core.c"
#include "basicDijkstra.c"

void test__advDijkstra(Graph *graph, Route *route, int start);
void test__clDijkstra(Graph *graph, Route *route, int start);
void test__basicDijkstra(Graph *graph, Route *route, int start);

void test__advDijkstra(Graph *graph, Route *route, int start)
{
	advDijkstra(graph,route,0);

	assert(route->distance[0] == 0);
	assert(route->distance[1] == 4);
	assert(route->distance[2] == 8);
	assert(route->distance[3] == 6);
	assert(route->distance[4] == 6);
	assert(route->distance[5] == 5);

	assert(route->predec[0] == -1);
	assert(route->predec[1] == 0);
	assert(route->predec[2] == 5);
	assert(route->predec[3] == 0);
	assert(route->predec[4] == 5);
	assert(route->predec[5] == 0);
}

void test__clDijkstra(Graph *graph, Route *route, int start)
{
	clDijkstra(graph,route,0);

	assert(route->distance[0] == 0);
	assert(route->distance[1] == 4);
	assert(route->distance[2] == 8);
	assert(route->distance[3] == 6);
	assert(route->distance[4] == 6);
	assert(route->distance[5] == 5);


	int i;
	for(i=0;i<route->countNodes;i++) {
		printf("%d\n", route->predec[i]);
	}


	assert(route->predec[0] == -1);
	assert(route->predec[1] == 0);
	assert(route->predec[2] == 5);
	assert(route->predec[3] == 0);
	assert(route->predec[4] == 5);
	assert(route->predec[5] == 0);
}


void test__basicDijkstra(Graph *graph, Route *route, int start)
{
	basicDijkstra(graph,route,0);

//	int i;
//	for(i=0;i<route->countNodes;i++) {
//		printf("%d\n", route->distance[i]);
//	}

	assert(route->distance[0] == 0);
	assert(route->distance[1] == 4);
	assert(route->distance[2] == 8);
	assert(route->distance[3] == 6);
	assert(route->distance[4] == 6);
	assert(route->distance[5] == 5);

	assert(route->predec[0] == -1);
	assert(route->predec[1] == 0);
	assert(route->predec[2] == 5);
	assert(route->predec[3] == 0);
	assert(route->predec[4] == 5);
	assert(route->predec[5] == 0);
}

/**
 * Main entry for the test.
 */
int main(int argc, char **argv)
{
	char* graphName = "ref";

	Graph graph;
	graph.name = graphName;
	gcGetDimension(&graph);
	graph.name = graphName;

	graph.countEdges = graph.nmbEdges * graph.countNodes;
	graph.nodes = malloc(graph.countNodes * sizeof(int));
	graph.edges = malloc(graph.countEdges * sizeof(int));
	graph.weights = malloc(graph.countEdges * sizeof(int));

	gcOpenGraph(&graph);

	Route route;
	route.countNodes = graph.countNodes;
	route.predec = malloc(graph.countNodes * sizeof(int));
	route.distance = malloc(graph.countNodes * sizeof(int));

	test__basicDijkstra(&graph, &route, 0);
	test__advDijkstra(&graph, &route, 0);
	test__clDijkstra(&graph, &route, 0);
	return 0;
}
