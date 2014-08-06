#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int* value;
	struct node* next;
} node;

node* findElementAtPos(node* dstData, int pos) {
    if(dstData == NULL || pos < 0) {
    	return NULL;
    }
    
    int span = 1;
    node* front = dstData;
    node* end = dstData;
    
    while(front != NULL) {
      front = front->next;
      if(span < pos) {
      	if(front != NULL) {
          span ++;
      	}
      } else if(front != NULL) {
        end = end->next;
      }
    }
    
    if(span == pos) {
    	return end;
    }
    
    return NULL;
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

  printf("dest list:\n");
  for(tail=dest;tail!=NULL;tail=tail->next) {
    printf(" %d, ", *(tail->value));
  }
  printf("\n");
  printf("==========================================\n");
	
  node* eleAtPos = findElementAtPos(dest, 8);

  if(eleAtPos) {
    printf("element at pos %d is %d ", 8, *(eleAtPos->value));
  } else {
    printf("element at pos %d cannot be found ", 8);
  }
}