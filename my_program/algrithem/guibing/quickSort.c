#include <stdio.h>
#include <stdlib.h>
#include "quickSort.h"

#define swap(data, a, b) {int t=(data)[a]; (data)[a]=(data)[b];(data)[b]=t;}

void quickSort(int* data, int len) {
    if(len <= 1 || data == NULL) {
    	return;
    }
    
    unsigned int i = 0;
    unsigned int j = len - 1;
    unsigned int k = 0;
    int key = data[0];
    
    for(;i<j;) {
    	while(i<j){
    		if(data[j] < key) {
    			swap(data, j, i);
    			i++;
    			break;
    		}
    		j--;
    	}

    	while(i<j){
    		if(data[i] > key) {
    			swap(data, i, j);
    			j--;
    			break;
    		}
    		i++;
    	}
    }
    
    quickSort(data, i);
    quickSort(data+i+1, len-i-1);
    return;
}

void main() {
  int sortData[10] = {-19, 12, 1, -3, 10, 2, 48, -9, 84, -29};
	int k;
	int length = sizeof(sortData)/sizeof(int);

  printf("Before sorting:\n");
    for(k=0;k<length;k++) {
      printf(" %d, ", sortData[k]);
    }
    printf("\n");
  printf("==========================================\n");
	
  quickSort(sortData, length);

  printf("After sorting:\n");
    for(k=0;k<length;k++) {
      printf(" %d, ", sortData[k]);
    }
    printf("\n");
}