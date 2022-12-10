// COMP2521 Assignment 2

// Written by:
// Date:

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "readData.h"


////////////////////////////
double outDegree(Graph g, Vertex v, int nUrls);
double inDegree(Graph g, Vertex v, int nUrls);
double referenceOut(Graph g, Vertex v, int nUrls);
double referenceIn(Graph g, Vertex v, int nUrls);
double calculateWOut(Graph g, Vertex v, Vertex w, int nUrls);
double calculateWIn(Graph g, Vertex v, Vertex w, int nUrls);
////////////////////////////


int main(int argc, char *argv[]) {
    // argc is the number of command-line arguments, which includes the
    // program name
    // argv is the array of command-line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s dampingFactor diffPR maxIterations\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    // Command-line arguments are received as strings. They can be converted
    // to number types using atoi and atof.
    // double d = atof(argv[1]);
    // double diffPR = atof(argv[2]);
    // int maxIterations = atoi(argv[3]);
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);
    
    
    // Read the collection of web pages and store them in urlList
    char *urlList[1000];
    readData("collection.txt", urlList);
    int nUrls = getNumUrl();
    
    // Create the graph of the web pages
    Graph g = createGraph();

    // Convert nUrls to a double
    double PR = (double) nUrls;
    double pageRank[nUrls];
    double oldPageRank[nUrls];

    for (int i = 0; i < nUrls; i++) {
        pageRank[i] = (double) 1.0/nUrls;
        oldPageRank[i] = (double) 1.0/nUrls;
    }
    
    // PageRank algorithm
    double diff = diffPR;
    int iteration = 0;

    while (iteration < maxIterations && diff >= diffPR) {
        // Calculate page rank of each url
        for (int i = 0; i < nUrls; i++) {
            double sum = 0.0;
            // Calculate the sum of the page rank of all urls that link to i
            for (int j = 0; j < nUrls; j++) {
                if (i != j) {
                    if (GraphIsAdjacent(g, j, i)) {
                        sum = sum + (oldPageRank[j] 
                            * calculateWIn(g, j, i, nUrls)
                            * calculateWOut(g, j, i, nUrls));
                    }
                }
            }

            pageRank[i] = ((1.0 - d)/PR) + (d * sum);
        }

        // Calculate the difference between the old page rank and the new page rank
        for (int i = 0; i < nUrls; i++) {
            diff += fabs(pageRank[i] - oldPageRank[i]);
            oldPageRank[i] = pageRank[i];
        }
      
        iteration++;
    }

    // Store outLinks in an array
    int outLinks[nUrls];
    for (int i = 0; i < nUrls; i++) {
        outLinks[i] = outDegree(g, i, nUrls);
    }

    /*
    // Print all the wOut and wIn values for debugging
    for (int i = 0; i < nUrls; i++) {
        for (int j = 0; j < nUrls; j++) {
            if (GraphIsAdjacent(g, i, j)) {
                printf("wIn[%d][%d]: %.7f ||", i, j, calculateWIn(g, i, j, nUrls));
                printf("wOut[%d][%d]: %.7f\n", i, j, calculateWOut(g, i, j, nUrls));
            }            
        }
    }
    W in and W out is matched with log.txt but page rank is 2 digits off
    */
    
    
    
    // Sort the urls by pageRank
    for (int i = 0; i < nUrls; i++) {
        for (int j = i + 1; j < nUrls; j++) {
            if (pageRank[i] < pageRank[j]) {
                double temp = pageRank[i];
                pageRank[i] = pageRank[j];
                pageRank[j] = temp;
                
                char *tempUrl = urlList[i];
                urlList[i] = urlList[j];
                urlList[j] = tempUrl;

                int tempOutLink = outLinks[i];
                outLinks[i] = outLinks[j];
                outLinks[j] = tempOutLink;
            }
        }
    }
    
    // Print the pageRank
    for (int i = 0; i < nUrls; i++) {
        printf("%s %d %0.7lf\n", urlList[i], outLinks[i], pageRank[i]);
    }    
    
    // Free the memory
    for (int i = 0; i < nUrls; i++) {
        free(urlList[i]);
    }
    GraphFree(g);

    return 0;
}


// Calculate the out degree of a vertex
double outDegree(Graph g, Vertex v, int nUrls) {
    double out = 0;
    for (int i = 0; i < nUrls; i++) {
        if (GraphIsAdjacent(g, v, i)) {
            out++;
        }
    }
    if (out == 0) {
        out = 0.5;
    }
    return out;
}

// Calculate the in degree of a vertex
double inDegree(Graph g, Vertex v, int nUrls) {
    double in = 0.0;
    for (int i = 0; i < nUrls; i++) {
        if (GraphIsAdjacent(g, i, v) && i != v) {
            in++;
        }
    }
    return in;
}

// Reference pages that the current page links to
double referenceOut(Graph g, Vertex v, int nUrls) {
    double total = 0.0;
    for (int i = 0; i < nUrls; i++) {
        if (GraphIsAdjacent(g, v, i) && i != v) {
            total += outDegree(g, i, nUrls);
        }
    }
    return total;
}

// Reference pages that link to the current page
double referenceIn(Graph g, Vertex v, int nUrls) {
    double total = 0;
    for (int i = 0; i < nUrls; i++) {
        if (GraphIsAdjacent(g, v, i) && i != v) {
            total += inDegree(g, i, nUrls);
        }
    }
    return total;
}

// Calculate W out 
double calculateWOut(Graph g, Vertex v, Vertex w, int nUrls) {
    double wOut = 0.0;
    wOut = (double) outDegree(g, w, nUrls) / referenceOut(g, v, nUrls);
    return wOut;
}

// Calculate W in
double calculateWIn(Graph g, Vertex v, Vertex w, int nUrls) {
    double wIn = 0.0;
    wIn = (double) inDegree(g, w, nUrls) / referenceIn(g, v, nUrls);
    return wIn;
}