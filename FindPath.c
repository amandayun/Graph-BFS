//Amanda Yun, akyun, 1903241, pa2

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

/* for findPath




*/

int main(int argc, char **argv) {
	
	int numberVertices;
	int one;
	int two;
	
	FILE *in, *out;
	Graph G;
	List L;
	
	
	if(argc!=3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	in = fopen(argv[1], "r");
	if(in ==NULL){
		printf("unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	
	out = fopen(argv[2], "w");
	if(out==NULL){
		printf("unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
		
	//prints out the number of vertices which is the same in the in and out file
	fscanf(in, "%d", &numberVertices);
	
	
	G = newGraph(numberVertices);
	one = 1;
	two = 1;
	
	while(one!=0 || two!=0){
		fscanf(in, "%d", &one);
		fscanf(in, "%d", &two);
		
		if(one==0 ||two==0){
			break;
		}
		addEdge(G, one, two);
	}
	
	printGraph(out, G);
	L = newList();
	
	//makeNull(G);
	
	
	
	//this is for source and destination
	
	one = 1;
	two = 1;
	while(one != 0 || two != 0){
		fscanf(in, " %d", &one);
		fscanf(in, " %d", &two);
		
		if(one ==0 || two==0){
			break;
		}
	
		BFS(G, one);
		//printPath()
		//dont use getPath?
		getPath(L, G, two);
		
		if(length(L)==0 || getDist(G, two)<0){
			fprintf(out, "\nThe distance from %d to %d is infinity\n", one, two);
			fprintf(out, "No %d-%d path exists\n", one, two);
			
		}else{
			fprintf(out, "\nThe distance from %d to %d is %d\n", one, two, getDist(G, two));
			fprintf(out, "A shortest %d-%d path is: ", one, two);
			
			//print the list to out
			moveFront(L);
			while(index(L)>=0){
				fprintf(out, "%d ", get(L));
				moveNext(L);
			}
			fprintf(out, "\n");
				
//			fprintf(out, "%s", printPath(G, one, two));
//			printPath(G, one, two);
		//	fprintf(out, "\n");
			
			
		}

		clear(L);
		
	}
	
	
	
	freeGraph(&G);
	freeList(&L);
	
	fclose(in);
	fclose(out);
	
	return 0;
}
