#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int* value;
	struct node* next;
} node;

void printReverseList(node* dstData) {
    if(dstData == NULL) {
    	return;
    }
    
    node* tail = NULL;
    node* current = dstData;
    node* next = dstData->next;
    
    while(next) {
    	current->next = tail;
    	tail = current;
    	current = next;
    	next = next->next;
    }
    
    current->next = tail;
    
    printf("After Merge:\n");
    for(tail=current;tail!=NULL;tail=tail->next) {
      printf(" %d, ", *(tail->value));
    }
    printf("\n");
}

void printReverseList1(node* dstData) {
    if(dstData == NULL) {
    	return;
    }
    
    printReverseList1(dstData->next);
    
    printf(" %d, ", *(dstData->value));
}

void delNodeAtPos(node* dest, node* pos) {
    if(dest == NULL || pos == NULL) {
    	return;
    }
}

void main() {
  int sortData1[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
	int k;
	int length1 = sizeof(sortData1)/sizeof(int);

  node* dest = NULL;
  node* tail = NULL;
  for(k=0;k<length1;k++){
  	node* elem = (node*)malloc(sizeof(node));
  	elem->value = sortData1+k;
  	elem->next = NULL;
  	if(dest == NULL) {
  		dest = elem;
  	}
  	if(tail) {
  	  tail->next = elem;
  	}
  	tail = elem;
  }

  printf("sortData1:\n");
  for(tail=dest;tail!=NULL;tail=tail->next) {
    printf(" %d, ", *(tail->value));
  }
  printf("\n");
  printf("==========================================\n");
	
  //delNodeAtPos(dest, node* pos);
  printReverseList1(dest);
}