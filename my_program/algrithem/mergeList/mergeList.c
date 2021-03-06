#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node* next;
} node;

void mergeArray(int* dstData, int dstSize, int* srcData, int srcSize) {
  if(srcSize <=0 || srcData == NULL) {
    return;
  }

  if(dstSize <=0) {
    memcpy((void*)dstData, (void*)srcData, dstSize*sizeof(int));
    return;
  }

  int posDst = dstSize - 1;
  int posSrc = srcSize - 1;
  int posAll = dstSize + srcSize - 1;

  while(posDst >=0 && posSrc >= 0) {
    if(dstData[posDst] > srcData[posSrc]) {
      dstData[posAll] = dstData[posDst];
      posDst --;
      posAll --;
    } else {
      dstData[posAll] = srcData[posSrc];
      posSrc --;
      posAll --;
    }
  }

  printf("posSrc: %d\n", posSrc);
  if(posSrc) {
    memcpy((void*)dstData, (void*)srcData, (posSrc+1)*sizeof(int));
  }
  return;
}

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

node* mergeListInSequence(node* dstData, node* srcData) {
    if(dstData == NULL) {
    	return srcData;
    }
    if(srcData == NULL) {
    	return dstData;
    }
    
    node* head = NULL;
    node* curPos = head;
    
    while(dstData && srcData) {
    	if(dstData->value < srcData->value) {
          if(head == NULL) {
            head = dstData;
          }
          if(curPos)
            curPos->next = dstData;

          curPos = dstData;
          dstData = dstData->next;
        } else {
          if(head == NULL) {
            head = srcData;
          }
          if(curPos)
            curPos->next = srcData;

          curPos = srcData;
          srcData = srcData->next;
        }
    }

    curPos->next = dstData?dstData:srcData;
    return head;
}

void main() {
  //int sortData1[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
  //int sortData2[] = {2, 4, 6, 8, 10,12, 14, 16, 18, 20};
  int sortData1[] = {1, 3, 5, 8, 9, 10, 13, 16, 17, 18, 19};
  int sortData2[] = {2, 4, 6,  7, 11, 12, 14, 15, 20};
  int k;
  int length1 = sizeof(sortData1)/sizeof(int);
  int length2 = sizeof(sortData2)/sizeof(int);

  node* dest = NULL;
  node* tail = NULL;
  for(k=0;k<length1;k++){
  	node* elem = (node*)malloc(sizeof(node));
  	elem->value = sortData1[k];
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
  	elem->value = sortData2[k];
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
    printf(" %d, ", (tail->value));
  }
  printf("\n");
  printf("==========================================\n");
	
  printf("sortData2 :\n");
  for(tail=src;tail!=NULL;tail=tail->next) {
    printf(" %d, ", (tail->value));
  }
  printf("\n");
  
  // verify mergeListInSequence
  node* list = mergeListInSequence(dest, src);

  // print result
  printf("After Merge:\n");
  for(tail=list;tail!=NULL;tail=tail->next) {
    printf(" %d, ", (tail->value));
  }


  printf("\n\n\n\n");
  printf("==========================================\n");
  printf("Merge Array: ");

  // initialize the test data
  int* dstData = (int*)malloc((length1+length2)*sizeof(int));
  for(k=0;k<length1;k++){
  	dstData[k] = sortData1[k];
  }
  for(k=0;k<(length1+length2);k++) {
    printf(" %d, ", dstData[k]);
  }
  printf("\n");

  // verify mergeArray
  mergeArray(dstData, length1, sortData2, length2);

  // print result
  printf("After Merge:\n");
  for(k=0;k<(length1+length2);k++) {
    printf(" %d, ", dstData[k]);
  }
  printf("\n");
}
