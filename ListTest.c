//Amanda Yun, akyun, 1903241, pa2
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <assert.h>
#include <stdbool.h>



int main(int argc, char *argv[]) {
	
	List L = newList();
	
	append(L, 3);
	append(L, 7);
	append(L, 0);
	
	prepend(L, 4);
	deleteBack(L);
	
	printf("%d\n", length(L));

	printList(stdout, L);
	
	moveFront(L);
	moveNext(L);
	


	
	
	//set(L, 34);
	printf("num at cursor: %d\n", get(L));
	
	insertBefore(L, 55);
	
	printf("num at cursor: %d\n", get(L));

	
	printList(stdout, L);
	printf("%d\n", length(L));
	
	insertAfter(L, 44);
	deleteFront(L);
	
	
	printList(stdout, L);
	printf("length: %d\n", length(L));
	
	delete(L);
	printList(stdout, L);
	
	moveFront(L);
	delete(L);
	printList(stdout, L);
	
	
	moveFront(L);
	printf("num at cursor: %d\n", get(L));
	delete(L);
	printList(stdout, L);
	
	
	moveFront(L);
	printf("num at cursor: %d\n", get(L));
	delete(L);
	printList(stdout, L);
	
	printf("length: %d\n", length(L));

	
	freeList(&L);
	
	
	
	return 0;
}