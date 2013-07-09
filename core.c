/**
 * @file core.c
 * @brief Structures the program cycle
 */

#include "core.h"

// Some Pre-Prop Constants
#define BILLION 1E9
#define YES 'y'
#define NO 'n'

// Error messages
#define ERROROPT "ERROR! To many, to less or wrong options!\n\n"
#define ERRORUNKNOWN "Fehler! Unbekannte Option.\n"
#define ERRORFILE "Fehler! Erstellen der temporären Datei fehlgeschlagen. Überprüfen Sie Ihre Berechtigung\n"

// Program options
const char DASH = '-';

#define BASIC 'b'
const char* BASICTEXT = "Calculates the shortest route with a plain Dijkstra algorithm";

#define CL 'c'
const char* CLTEXT = "Calculates the shortest route with an OpenCL optimized Dijkstra algorithm";

#define OPT 'o'
const char* OPTTEXT = "Calculates the shortest route with an optimized Dijkstra algorithm";

#define GEN 'g'
const char* GENTEXT = "Generates a new graph";

/**
 * Display the help text
 */
void help(void){

    printf("\n=== DIJKSTRA CL ===\n\n");
    printf("Options:\n");
    printf("\t-%c <name> <no. of nodes> [no. of edges]: %s\n", GEN, GENTEXT);
    printf("\t-%c <graph> [node]: %s\n", BASIC, BASICTEXT);
    printf("\t-%c <graph> [node]: %s\n", CL, CLTEXT);
    printf("\t-%c <graph> [node]: %s\n", OPT, OPTTEXT);
    printf("Instructions:\n");
    printf("\tFirst Step: Generate a new graph, e.g.: dijkstracl -g example \n");
    printf("\tSecond Step: Calculate the distance, e.g.: dijkstracl -b example \n");
    printf("\tAdding a node number to the command (dijkstracl -b example 6)\n");
    printf("\twill verbose the exact route to the specified node.\n");
    printf("\n");

}

void createGraph(int argc, char **argv) {

	if(argc >= 4) {

		// Proceed Arguments
		char* graphName = argv[2];
		int countNodes = atoi(argv[3]);
		int countEdges = 3;

		if(strcmp("ref", graphName) == 0) {
			printf("ERROR! This graph name is reserved and read-only.\n");
			return;
		}

		if(argc == 5) {
			countEdges = atoi(argv[4]);
		}

		printf("Creating a graph '%s' with %d nodes and %d edges per node...\n", graphName, countNodes, countEdges);

		Graph graph;
		graph.name = graphName;
		graph.countNodes = countNodes;
		graph.nmbEdges = countEdges;
		graph.countEdges = graph.nmbEdges * graph.countNodes;
		graph.nodes = malloc(graph.countNodes *  sizeof(int));
		graph.edges = malloc(graph.countEdges * sizeof(int));
		graph.weights = malloc(graph.countEdges * sizeof(int));

		gcCreateRandomGraph(&graph);
		if(!gcSaveGraph(&graph)) {
			printf("ERROR! Could not write graph to disk, please try again.");
		} else {
			printf("SUCCESS! Created Graph.\n");
		}

		free(graph.nodes);
		free(graph.edges);
		free(graph.weights);


	} else {
		printf(ERROROPT);
	}

}

Route calculatePath(char option, int argc, char **argv) {

	Route route;

	if(argc >= 3) {
		char* graphName = argv[2];

		if(gcGraphExists(graphName) == 0) {
			printf("ERROR! No graph with the name '%s' exists.\n", graphName);
		} else {
			Graph graph;
			graph.name = graphName;
			gcGetDimension(&graph);
			graph.name = graphName;

			graph.countEdges = graph.nmbEdges * graph.countNodes;
			graph.nodes = malloc(graph.countNodes *  sizeof(int));
			graph.edges = malloc(graph.countEdges * sizeof(int));
			graph.weights = malloc(graph.countEdges * sizeof(int));

			printf("\n== CALCULATING =====================================================\n");

			printf("Reading the graph ...\n");
			gcOpenGraph(&graph);
			route.countNodes = graph.countNodes;
			route.predec = malloc(graph.countNodes * sizeof(int));
			route.distance = malloc(graph.countNodes * sizeof(int));

			if(option == BASIC) {
				printf("Calculating with a basic Dijkstra algorithm. (%d nodes)\n", graph.countNodes);
				basicDijkstra(&graph,&route,0);
				printf("Done!\n");
			}

			if(option == OPT) {
				printf("Calculating with a optimized Dijkstra algorithm. (%d nodes)\n", graph.countNodes);
				advDijkstra(&graph,&route,0);
				printf("Done!\n");
			}

			if(option == CL) {
				printf("Calculating with a OpenCL Dijkstra algorithm. (%d nodes)\n", graph.countNodes);
				clDijkstra(&graph,&route,0);
				printf("Done!\n");
			}

			int distance = route.distance[(route.countNodes)-1];

			printf("\n== RESULT ==========================================================\n");

			if(distance != I){
				printf("The distance from the start node to the last node %d is: %d\n", (route.countNodes)-1, distance);
			} else {
				printf("There does not exist any way from the start node to last node %d.\n", (route.countNodes)-1);
			}

			if(argc == 4) {
				int target = atoi(argv[3]);
				getResult(target, &route);
			}

			free(route.predec);
			free(route.distance);
		}

	} else {
		printf(ERROROPT);
	}

	printf("\n== BENCHMARK =======================================================\n");
	double accum = (CALCULATION_END.tv_sec - CALCULATION_START.tv_sec) + (CALCULATION_END.tv_nsec - CALCULATION_START.tv_nsec) / BILLION;
	printf("The pure calculation took %lf seconds.\n\n", accum);

	return route;
}

void getResult(int target, Route *result) {

	int lTarget = target;
	int allocSize = 10;
	int *route =  malloc(sizeof(int)*allocSize);
	int i = 0;
	int count = 0;

	// Node is not part of the graph
	if(target >= result->countNodes) {
		printf("ERROR!. The target does not exist.\n");
	} else {

		int success = 1;

		// Traverse through predecessor array
		while(lTarget != 0) {
			// Add new stop on the route
			route[count] = lTarget;
			count++;
			// Get more memory
			if(count == allocSize){
				allocSize = allocSize*2;
				route = realloc(route, sizeof(int)*allocSize);
			}
			lTarget = result->predec[lTarget];
			if(lTarget == -1){
				lTarget = 0;
				success = 0;
			}
		}

		if (success) {
			route[count] = 0;
			printf("The distance from the start node to node %d is: %d\n", target, result->distance[target]);
			printf("The best route: ");

			// Print route backwards
			for (i = count; i >= 0; i--) {
				if (i == 0) {
					printf("%d", route[i]);
				} else {
					printf("%d >> ", route[i]);
				}

			}
		} else {
			printf("There does not exist any way from the start node to node %d.", target);
		}


	printf("\n");
	free(route);
	}
}

int mainProgram(int argc, char **argv) {

	char option;


	if(argc == 1) {
		help();
	} else {
		// The main option has to consist out of two chars
		if(strlen(argv[1]) == 2) {
			option = argv[1][1];
			// Delegate option to responsible function
			switch (option) {
				case GEN:
					createGraph(argc, argv);
					break;
				case BASIC:
					calculatePath(option, argc, argv);
					break;
				case OPT:
					calculatePath(option, argc, argv);
					break;
				case CL:
					calculatePath(option, argc, argv);
					break;
				default:
					help();
					break;
			}
		} else {
			printf(ERRORUNKNOWN);
		}

	}

	return EXIT_SUCCESS;
}

