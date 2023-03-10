//Amanda Yun, akyun, 1903241, pa2
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define NIL -1
#define INF -8


typedef struct GraphObj* Graph;

//constructors-destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);


//access functions
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);


/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
//void printPath(Graph G, int s, int x);
