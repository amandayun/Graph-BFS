//Amanda Yun, akyun, 1903241, pa2
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"
#include <assert.h>
#include <stdbool.h>



typedef struct GraphObj{
	List* neighbors;
	int* color;
	int* parent;
	int* distance;
	
	
	int vertices;
	int edges;
	int source;
	
	
}GraphObj;



Graph newGraph(int n){
	
	if(n<1){
		printf("Graph error: calling newGraph when number of vertices is less than 1/n");
		exit(EXIT_FAILURE);
	}
	Graph G = malloc(sizeof(GraphObj));
	assert(G!=NULL);
	

	G->vertices = n;
	G->edges = 0;
	G->source = NIL;

	
	//white = 0, grey = 1, black = 2
	G->color = malloc(sizeof(int)*(n+1));
	G->parent = malloc(sizeof(int)*(n+1));
	G->distance = malloc(sizeof(int)*(n+1));
	G->neighbors = malloc(sizeof(List)*(n+1));
	
	for(int i = 1; i<=n; i++){
		G->neighbors[i] = newList();
		G->color[i] =  0;
		G->parent[i] = NIL;
		G->distance[i] = INF;
		
	}
	
	//*G->neighbors = newList();

	
	return(G);
	
}


//gdb --args ./
//run
//bt


void freeGraph(Graph* pG){
	int n;
	
	if(pG==NULL){
		printf("Graph error: calling freeGraph() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	if(*pG==NULL){
		printf("Graph error: calling freeGraph() on a NULL pointer to Graph/n");
		exit(EXIT_FAILURE);
	}
	
	n = (*pG)->vertices;
	for(int i=1; i<n+1; i++){
		freeList(&(*pG)->neighbors[i]);
	}
	//freeList((*pG)->neighbors);
	
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->distance);
	free((*pG)->neighbors);
	
	
	free(*pG);
	*pG = NULL;
}

int getOrder(Graph G){
	//returns the number of vertices
	if(G==NULL){
		printf("Graph error: calling getOrder() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	return G->vertices;
}


int getSize(Graph G){
	//returns the number of sides
	if(G==NULL){
		printf("Graph error: calling getSize() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	return G->edges;
	//return G->vertices;
}

int getSource(Graph G){
	//the starting point in a pair of vertices on each line
	if(G==NULL){
		printf("Graph error: calling getSource() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	
	return G->source;

}


int getParent(Graph G, int u){
	if(G==NULL){
		printf("Graph error: calling getParent() on a NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(u<1 || u>getOrder(G)){
		printf("Source error: calling getParent() when u is out of range");
		exit(EXIT_FAILURE);
	}
	
	return G->parent[u];
}


int getDist(Graph G, int u){
	if(G==NULL){
		printf("Graph error: calling getDist() on a NULL Graph\n");
		exit(EXIT_FAILURE);
	}
	if(u<1 || u>getOrder(G)){
		printf("Source error: calling getDist() when u is out of range\n");
		exit(EXIT_FAILURE);
	}
	if(G->source<0){
		return INF;
	}
	
	return G->distance[u];
	
}

void getPath(List L, Graph G, int u){
	if(G==NULL){
		printf("Graph error: calling getPath() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G)==NIL){
		printf("Source error: calling getPath() on a graph with a NIL source");
		exit(EXIT_FAILURE);
	}
	if(u<1 || u>getOrder(G)){
		printf("Source error: calling getPath() when u is out of range");
		exit(EXIT_FAILURE);
	}
	
	int s = G->source;
	
	if(u == s){
		append(L, s);
	}else if(G->parent[u] == NIL){
		append(L, NIL);
		//printf("\nThe distance from %d to %d is infinity\n", s, u);
	}else{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
	
//	if(x==s){
//		printf("%d ", s);
//	}else if(G->parent[x]==NIL){
//		printf("%d is not reachable from %d", x, s);
//	}else{
//		printPath(G, s, G->parent[x]);
//		printf("%d ", x);
//	}
	
}


void makeNull(Graph G){
	if(G==NULL){
		printf("Graph error: calling makeNULL() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	//set n back to original order??????
	G->vertices = 0;
	
	G->edges = 0;
	G->source = NIL;
	
	for(int i = 0; i<G->vertices; i++){

		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->color[i] = 0;
		
		clear(G->neighbors[i]);
	}
	
	
}

/*
for addEdge:

add u to the adj[v] (add 1 to the adj[at index 3])

*/

void addEdge(Graph G, int u, int v){
	if(G==NULL){
		printf("Graph error: calling addEdge() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	if(u<1 || u>getOrder(G)){
		printf("Source error: calling getPath() when u is out of range");
		exit(EXIT_FAILURE);
	}
	if(v<1 || v>getOrder(G)){
		printf("Source error: calling getPath() when v is out of range");
		exit(EXIT_FAILURE);
	}
	
	
	//for u
	//append(G->neighbors[u], v);
	//moveFront(G->neighbors[u]);
	if(length(G->neighbors[u])==0){
		append(G->neighbors[u], v);
	}else{
		moveFront(G->neighbors[u]);
		while(get(G->neighbors[u])<v){
			moveNext(G->neighbors[u]);
			if(index(G->neighbors[u])<0){
				break;
			}
		}
		
		if(index(G->neighbors[u])<0){
			append(G->neighbors[u], v);
		}else{
			insertBefore(G->neighbors[u], v);
		}
			
			
	}
	
	
	//for v
	//append(G->neighbors[v], u);
	//moveFront(G->neighbors[v]);
	if(length(G->neighbors[v])==0){
		append(G->neighbors[v], u);
	}else{
		moveFront(G->neighbors[v]);
		while(get(G->neighbors[v])<u){
			moveNext(G->neighbors[v]);
			if(index(G->neighbors[v])<0){
				break;
			}
		}
		
		if(index(G->neighbors[v])<0){
			append(G->neighbors[v], u);
		}else{
			insertBefore(G->neighbors[v], u);
		}
	}

	
	G->edges++;
	
	
}


//same as addEdge but don't need to do it the other way
//only adding v to u not u to v
void addArc(Graph G, int u, int v){
	if(G==NULL){
		
		printf("Graph error: calling addArc() on a NULL Graph/n");
		exit(EXIT_FAILURE);
	}
	if(u<1 || u>getOrder(G)){
		printf("Source error: calling getArc() when u is out of range");
		exit(EXIT_FAILURE);
	}
	if(v<1 || v>getOrder(G)){
		printf("Source error: calling getArc() when v is out of range");
		exit(EXIT_FAILURE);
	}
	
	if(length(G->neighbors[u])==0){
		append(G->neighbors[u], v);
	}else{
		moveFront(G->neighbors[u]);
		while(get(G->neighbors[u])<v){
			moveNext(G->neighbors[u]);
			if(index(G->neighbors[u])<0){
				break;
			}
		}
		
		if(index(G->neighbors[u])<0){
			append(G->neighbors[u], v);
		}else{
			insertBefore(G->neighbors[u], v);
		}
	
		
	}
	
	
	
	

	G->edges++;
	
	
	
}

void BFS(Graph G, int s){
	if(G==NULL){
		printf("Graph error: calling addEdge() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(s<0){
		printf("Input error: calling BFS with invalid, negative input s");
		exit(EXIT_FAILURE);
	}
	
	if(s>G->vertices){
		printf("Input error: calling BFS when input s is out of range");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 1; i<=G->vertices; i++){
		G->color[i] =  0;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	
	G->source = s;
	G->color[s] = 1;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	
	List L = newList();
	//moveFront(G->neighbors[s]);
	
	append(L, s);
	
	while(length(L)>0){
		moveFront(L);
		int x = get(L);
		deleteFront(L);
		moveFront(G->neighbors[x]);
	
		for(int i = 1; i<=length(G->neighbors[x]); i++){
			int y = get(G->neighbors[x]);
			if(G->color[y]==0){
				G->color[y]=1;
				G->distance[y] = G->distance[x]+1;
				G->parent[y] = x;
				append(L, y);
			}
			moveNext(G->neighbors[x]);
		}
				
		
		
		G->color[x] = 2;
		//deleteFront(L);

	}
	
	freeList(&L);
	L=NULL;
}

void printGraph(FILE* out, Graph G){
	if(G==NULL){
		fprintf(stderr, "Error in printGraph(). empty graph.\n");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 1; i<= G->vertices; i++){
		if(length(G->neighbors[i])>0){
			moveFront(G->neighbors[i]);
			fprintf(out, "%d: ", i);
			while(index(G->neighbors[i])>-1){
				fprintf(out, "%d ", get(G->neighbors[i]));
				moveNext(G->neighbors[i]);
			}
			fprintf(out, "\n");
		}
	}

	/*
	for(int i = 1; i<= G->vertices; i++){
		moveFront(G->neighbors[i]);
		fprintf(out, "%d: ", i);
		while(index(G->neighbors[i])>-1){
			fprintf(out, "%d ", get(G->neighbors[i]));
			moveNext(G->neighbors[i]);
		}
		fprintf(out, "\n");
	}*/
	
}

//void printPath(Graph G, int s, int x){
//	if(G==NULL){
//		fprintf(stderr, "Error in printGraph(). empty graph.\n");
//		exit(EXIT_FAILURE);
//	}
//	
//	if(x==s){
//		printf("%d ", s);
//	}else if(G->parent[x]==NIL){
//		printf("%d is not reachable from %d", x, s);
//	}else{
//		printPath(G, s, G->parent[x]);
//		printf("%d ", x);
//	}
//	
//	
//}


/*

printPath

recursively call printpath(A, p[B])
once at end of call stack (if Parent[B] = NIL)
	print(B) and return up the call stack

*/

//getPath is the same as printpath pseudocode but instead of printing you append it to a list
/*
List path = newList();
BFS(G, s);
getPath(path, 6);
printList(Path)

*/
	