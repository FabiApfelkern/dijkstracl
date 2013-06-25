#include "core.h"

#define I 998

#define YES 'y'
#define NO 'n'
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

Graph initGraph(char* graphName, int countNodes, int countEdges) {
	Graph graph;
	graph.name = graphName;
	graph.nmbEdges = countEdges;
	graph.countNodes = countNodes;
	graph.countEdges = graph.nmbEdges * graph.countNodes;
	graph.nodes = malloc(graph.countNodes *  sizeof(int));
	graph.edges = malloc(graph.countEdges * sizeof(int));
	graph.weights = malloc(graph.countEdges * sizeof(int));
	return graph;
}

/**
 * Displays the interactive mode to create a graph.
 *
 * @param argc
 * @param argv
 */
void createGraph(int argc, char **argv) {

	if(argc == 3) {

		char* graphName = argv[2];
		int countNodes;
		int countEdges;
		int step = 1;
		int scan;

		if(strcmp("ref", graphName) == 0) {
			printf("ERROR! This graph name is reserved and read-only.\n");
			step = 0;
		}

		while(step){
			char input;

			switch (step) {
				case 1:
					if(gcGraphExists(graphName) == 1) {
						printf("The graph %s does already exist. Do you want to override it? [n/y]\n", graphName);
						scan = scanf("%c", &input);
						if(input == YES) {
							step++;
						} else {
							step = 0;
						}
					} else {
						step++;
					}
					break;

				case 2:
					printf("How many nodes do you want to create?\n");
					scan = scanf("%d", &countNodes);
					if(countNodes >= 1 && countNodes < INT_MAX) {
						step++;
					} else {
						printf("ERROR! Wrong input format.\n");
					}
					break;

				case 3:
					printf("How many connections does each node has?\n");
					scan = scanf("%d", &countEdges);
					if (countEdges >= 1 && countEdges < INT_MAX) {
						step++;
					} else {
						printf("ERROR! Wrong input format.\n");
					}
					break;

				case 4:
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
					step = 0;
					break;

				default:
					break;
			}

			fseek(stdin,0,SEEK_END);
		}
		(void)scan;

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

			printf("The distance from the start node to the last node %d is: %d\n", (route.countNodes)-1, route.distance[(route.countNodes)-1]);

			if(argc == 4) {
				//char* resultName = argv[3];
				//gcSaveResult(resultName, predec, distance, graph.countNodes);
				int target = atoi(argv[3]);
				getResult(target, route.predec, route.distance, graph.countNodes);
			}

			free(route.predec);
			free(route.distance);
		}

	} else {
		printf(ERROROPT);
	}

	return route;
}

void getResult(int target, int *predec, int *distance, int countNodes) {

	int lTarget = target;
	int *route =  malloc(sizeof(int));
	int i = 0;
	int count = 0;

//	for(i = 0; i<countNodes;i++) {
//		printf("%d ", predec[i]);
//
//	}

	if(target >= countNodes) {
		printf("ERROR!. The target does not exist.\n");
	} else {

		while(lTarget != 0) {
			route[count] = lTarget;
			count++;
			route = realloc(route, (count+1)*sizeof(int));
			lTarget = predec[lTarget];
		}
		route[count] = 0;

	printf("The distance from the start node to node %d is: %d\n", target, distance[target]);
	printf("The best route: ");

	for (i = count; i >= 0; i--) {
		if(i == 0) {
			printf("%d", route[i]);
		} else {
			printf("%d >> ", route[i]);
		}

	}
	free(route);
	}
}


/**
 * Display the help text
 */
void help(void){

    printf("\n=== DIJKSTRA CL ===\n\n");
    printf("Options:\n");
    printf("\t-%c <name>: %s\n", GEN, GENTEXT);
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


void myClock(time_t start) {
	printf("%.1f: ",difftime(time(NULL),start));
}


