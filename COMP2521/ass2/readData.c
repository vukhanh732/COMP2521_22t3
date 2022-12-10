#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"


int getNumUrl(void);
bool isConnected(char *url, char **urlArray);

// Read the data from the file and store the url in a list
void readData(char *filename, char **urlArray) {
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);
    int i = 0;
    char url[100];
    while (fscanf(fp, "%s", url) != EOF) {
        urlArray[i] = malloc(strlen(url) + 1);
        strcpy(urlArray[i], url);
        i++;
    }
    fclose(fp);
}


// Create a graph from the list of url. Url is the vertex of the graph
Graph createGraph(void) {
    int numUrl = getNumUrl();
    char **urlArray = malloc(sizeof(char *) * 100);
    readData("collection.txt", urlArray);
    Graph g = GraphNew(numUrl);
    
    char temp[1000];
    
    // Open each file to see the url it links to. Add .txt to the url to open the file
    for (int i = 0; i < numUrl; i++) {
        char *fileName = malloc(strlen(urlArray[i]) + 5);
        strcpy(fileName, urlArray[i]);
        strcat(fileName, ".txt");

        FILE *fp = fopen(fileName, "r");
        assert(fp != NULL);
        while (fscanf(fp, "%s", temp) != EOF) {
            // Scan the file until the line starts with "#end Section-1"
            if (strcmp(temp, "#end Section-1") == 0) {
                break;
            } else {
            // Check if the url is connected. Add to the graph if it is
                if (isConnected(temp, urlArray)) {
                    for (int j = 0; j < numUrl; j++) {
                        if (strcmp(temp, urlArray[j]) == 0 && i != j) {
                            GraphInsertEdge(g, i, j, 1);
                        }
                    }
                }
            }

        }
        free(fileName);
        fclose(fp);
    }
    
    // Free the memory
    for (int i = 0; i < numUrl; i++) {
        free(urlArray[i]);
    }
    free(urlArray);
    
    return g;
}

// Check if the url is connected to the current url
bool isConnected(char *url, char **urlArray) {
    int numUrl = getNumUrl();
    for (int i = 0; i < numUrl; i++) {
        if (strcmp(urlArray[i], url) == 0) {
            return true;
        }
    }
    return false;
}

// Get the number of url in the file
int getNumUrl(void) {
    FILE *fp = fopen("collection.txt", "r");
    assert(fp != NULL);
    int i = 0;
    char url[100];
    while (fscanf(fp, "%s", url) != EOF) {
        i++;
    }
    fclose(fp);
    return i;
}