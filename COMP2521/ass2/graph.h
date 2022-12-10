// Graph.h. Interface for a graph ADT (Adjacency Matrix) from lab07

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;

typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
    double weight;
} Edge;

/**
 * Creates a new instance of a graph
 */
Graph  GraphNew(int nV);

/**
 * Frees all memory associated with the given graph
 */
void   GraphFree(Graph g);

/**
 * Returns the number of vertices in the graph
 */
int    GraphNumVertices(Graph g);

/**
 * Inserts  an  edge into a graph. Does nothing if there is already an
 * edge between `e.v` and `e.w`. Returns true if successful, and false
 * if there was already an edge.
  */
void   GraphInsertEdge(Graph g, Vertex v, Vertex w, double weight);

/**
 * Removes an edge from a graph. Returns true if successful, and false
 * if the edge did not exist.
 */
void   GraphRemoveEdge(Graph g, Vertex v, Vertex w);

/**
 * Returns the weight of the edge between `v` and `w` if it exists, or
 * 0.0 otherwise
 */
double GraphIsAdjacent(Graph g, Vertex v, Vertex w);

/*
 * Displays information about the graph
 */
void   GraphShow(Graph g);

#endif
