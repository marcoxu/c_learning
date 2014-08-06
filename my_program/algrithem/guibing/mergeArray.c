#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quickSort.h"

#define swap(data, a, b) {int t=(data)[a]; (data)[a]=(data)[b];(data)[b]=t;}

int mergeArray(int* dstData, int len1, int* srcData, int len2) {
    if(len1 <= 0 || dstData == NULL) {
    	return -1;
    }
    if(len2 <= 0 || srcData == NULL) {
    	return 0;
    }
    
    int startDest = len1 - 1;
    int startSrc = len2 - 1;
    int* dataEnd = dstData + len1 + len2 - 1;
    int* dataStart = dstData;
    
    while(dataEnd>=dataStart) {
    	if(startDest >= 0 && startSrc >= 0) {
    	  if(dstData[startDest] > srcData[startSrc]) {
    	  	*dataEnd = dstData[startDest];
    	  	startDest --;
    	  } else {
    	  	*dataEnd = srcData[startSrc];
    	  	startSrc --;
    	  }
    	  dataEnd --;
    	} else if (startDest >= 0) {
    	  	*dataEnd = dstData[startDest];
    	  	startDest --;
    	    dataEnd --;
    	} else if (startSrc >= 0) {
    	  	*dataEnd = srcData[startSrc];
    	  	startSrc --;
    	    dataEnd --;
    	} else {
    	    dataEnd --;
    	}
    }
    return;
}

int mergeArray1(int* dstData, int* srcData1, int len1, int* srcData2, int len2) {
    if(dstData == NULL) {
    	return -1;
    }
    
    if(len1 <= 0 || srcData1 == NULL) {
      if(len2 <= 0 || srcData2 == NULL) {
      	return 0;
      }
    }

    if(len2 <= 0 || srcData2 == NULL) {
    	memcpy(dstData, srcData1, len1*sizeof(int));
    	return 0;
    }
    
    int startSrc1 = 0;
    int startSrc2 = 0;
    int* dataStart = dstData;
    int* dataEnd = dstData + len1 + len2 - 1;
    
    while(dataEnd>=dataStart) {
    	if(startSrc1 < len1 && startSrc2 < len2) {
    	  if(srcData1[startSrc1] < srcData2[startSrc2]) {
    	  	*dataStart = srcData1[startSrc1];
    	  	startSrc1 ++;
    	  } else {
    	  	*dataStart = srcData2[startSrc2];
    	  	startSrc2 ++;
    	  }
    	  dataStart ++;
    	} else if (startSrc1 < len1) {
    	  	*dataStart = srcData1[startSrc1];
    	  	startSrc1 ++;
    	    dataStart ++;
    	} else if (startSrc2 < len2) {
    	  	*dataStart = srcData2[startSrc2];
    	  	startSrc2 ++;
    	    dataStart ++;
    	} else {
    	    dataStart ++;
    	}
    }
    return;
}

void main() {
  int sortData1[10] = {16, 14, 18, 8, 12, 4, 10, 6, 2, 20};
  int sortData2[10] = {11, 3, 1, 15, 5, 9, 13, 7, 19, 17};
	int k;
	int length1 = sizeof(sortData1)/sizeof(int);
	int length2 = sizeof(sortData2)/sizeof(int);
	int* dstData = (int*)malloc(sizeof(sortData1)+sizeof(sortData2));

  printf("sortData1 Before sorting:\n");
  for(k=0;k<length1;k++) {
    printf(" %d, ", sortData1[k]);
  }
  printf("\n");
  printf("==========================================\n");
	
  quickSort(sortData1, length1);

  printf("sortData1 After sorting:\n");
  for(k=0;k<length1;k++) {
    printf(" %d, ", sortData1[k]);
  }
  printf("\n");

  printf("==========================================\n");
  printf("sortData2 Before sorting:\n");
  for(k=0;k<length2;k++) {
    printf(" %d, ", sortData2[k]);
  }
  printf("\n");
  printf("==========================================\n");
	
  quickSort(sortData2, length2);

  printf("sortData2 After sorting:\n");
  for(k=0;k<length2;k++) {
    printf(" %d, ", sortData2[k]);
  }
  printf("\n");
  
  //mergeArray(sortData1, length1, sortData2, length2);
  mergeArray1(dstData, sortData1, length1, sortData2, length2);
  printf("After Merge:\n");
  for(k=0;k<length1+length2;k++) {
    printf(" %d, ", dstData[k]);
  }
  printf("\n");
}