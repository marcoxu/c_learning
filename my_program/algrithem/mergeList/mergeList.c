#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int* value;
	struct node* next;
} node;

node* mergeList(node* dstData, node* srcData) {
    if(dstData == NULL) {
    	return srcData;
    }
    if(srcData == NULL) {
    	return dstData;
    }
    
    node* dstPos = dstData;
    node* srcPos = srcData;
    node* curPos = NULL;
    
    while(dstPos && srcPos) {
    	curPos = dstPos;
    	dstPos = dstPos->next;
    	curPos->next = srcPos;
    	srcPos = srcPos->next;
    	curPos->next->next = dstPos;
    }
    
    if(srcPos) {
    	curPos->next->next = srcPos;
    }
    return dstData;
}

void main() {
  int sortData1[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
  int sortData2[] = {2, 4, 6, 8, 10,12, 14, 16, 18, 20};
	int k;
	int length1 = sizeof(sortData1)/sizeof(int);
	int length2 = sizeof(sortData2)/sizeof(int);

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

  node* src  = NULL;
  tail = NULL;
  for(k=0;k<length2;k++){
  	node* elem = (node*)malloc(sizeof(node));
  	elem->value = sortData2+k;
  	elem->next = NULL;
  	if(src == NULL) {
  		src = elem;
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
	
  printf("sortData2 :\n");
  for(tail=src;tail!=NULL;tail=tail->next) {
    printf(" %d, ", *(tail->value));
  }
  printf("\n");
  
  node* list = mergeList(dest, src);
  printf("After Merge:\n");
  for(tail=list;tail!=NULL;tail=tail->next) {
    printf(" %d, ", *(tail->value));
  }
  printf("\n");
}