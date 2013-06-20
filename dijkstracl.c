/**
 * @file dijkstracl.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "core.h"


/**
 * Main entry point of the program. Some pre-validation of the user input is performed and the
 * selected option is delegated to a matching function.
 *
 * @param argc Number of arguments
 * @param argv Arguments
 * @return
 */
int main(int argc, char **argv) {

	mainProgram(argc, argv);
	return EXIT_SUCCESS;
}




