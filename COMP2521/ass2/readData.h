#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"


// readData reads the data from the file and stores it in an array. Returns the
// number of url
void readData(char *filename, char **urlArray);

// Create a new graph with url as the vertices
Graph createGraph(void);

// Check if the url is connected to the current 
bool isConnected(char *url, char **urlArray);

// Count the number of urls in the file
int getNumUrl(void);