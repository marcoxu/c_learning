#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quickSort.h"

#define GROUP_SIZE 5
static unsigned long compareCount = 0;

unsigned long findMinimumK(unsigned long* data, int length, unsigned int k);

void printArray(unsigned long * array, unsigned int length) {
  int i = 0;
  for(i=0;i<length;i++) {
     printf("%lu, ", array[i]);
  }
  printf("\n");
}

unsigned long selectPivot(unsigned long* array, int length) {
  if(length == 0 || array == NULL) {
    return 0;
  }
  int groupNum = length/GROUP_SIZE;
  
  if(length%GROUP_SIZE > 0) {
    groupNum += 1;
  }
  //printf("groupNum is %d\n", groupNum);
  unsigned long * pivotGroup = (unsigned long*)malloc(groupNum*sizeof(unsigned long));
  int i;
  for(i=0;i<groupNum;i++) {
    int len = GROUP_SIZE;
    if(i == groupNum -1 && length%GROUP_SIZE > 0) {
       len = length%GROUP_SIZE;
    }

    pivotGroup[i] = findMinimumK(array+i*GROUP_SIZE, len, GROUP_SIZE/2+1);
    //printf("pivotGroup[%d] is %lu, len is %d\n", i, pivotGroup[i], len);
  }

  unsigned long pivot = findMinimumK(pivotGroup, groupNum, groupNum/2+1);;
  free(pivotGroup);
  return pivot;
}

void swap(unsigned long * array, int from, int to) {
  unsigned long temp = array[to];
  array[to] = array[from];
  array[from] = temp;
}

int partialQuickSortByPivotPos(unsigned long* array, int length, int pivot) {
  if(array == NULL || length <= 1) {
    return 0;
  }

  swap(array, 0, pivot);

  int from, end;
  int pos = 0;
  from = pos;
  end = length - 1;
  int fromEnd = 1;

  while(from <= end) {
    if(fromEnd) {
       if(array[end] < array[pos]) {
         compareCount ++;
         fromEnd = 0;
         swap(array, pos, end);
         pos = end;
       }
       end --;
    } else {
       if(array[from] > array[pos]) {
         compareCount ++;
         fromEnd = 1;
         swap(array, pos, from);
         pos = from;
       }
       from ++;
    }
    //printArray(array, length);	
  }
  return pos;
}

int partialQuickSortByPivotValue(unsigned long* array, int length, unsigned long pivot) {
  if(array == NULL || length <= 1) {
    return 0;
  }

  int from, end;
  from = 0;
  end = length - 1;
  int fromEnd = 1;
  int pos = -1;

  //printf("pivot: %lu\n", pivot);
  while(from <= end) {
  //printf("==========================================================\n");
  //printf("pos=%d, from[%d]: %lu, end[%d]: %lu\n", pos ,from, array[from], end, array[end]);
  //printArray(array, length);

    if(fromEnd) {
       if(array[end] < pivot) {
         compareCount ++;
         fromEnd = 0;
         int switchPos = (pos >=0 ? pos: from);
         swap(array, switchPos, end);
         if(pos >= 0)
            pos = end;
       } else {
         if(array[end] == pivot && pos == -1) {
            pos = end;
            fromEnd = 0;
         } else 
           end --;
       }
    } else {
       if(array[from] > pivot) {
         compareCount ++;
         fromEnd = 1;
         int switchPos = (pos >=0 ? pos: end);
         swap(array, switchPos, from);
         if(pos >= 0)
            pos = from;
       } else {
         if(array[from] == pivot && pos == -1) {
            pos = from;
           fromEnd = 1;
         } else 
           from ++;
       }
    }
    //printArray(array, length);
  }
  return pos;
}

unsigned long findMinimumK(unsigned long* data, int length, unsigned int k) {
   int pos = 0;
   unsigned long * array = data;
   int len = length;
   
   if(k > length) {
      return data[length-1];
   }

   while(1) {
     int posT = partialQuickSortByPivotValue(array, len, array[0]);
     //printArray(array, len);
     //printf("posT: %d\n", posT);
     if(pos+posT+1 == k) {
        break;
     } else if (pos+posT+1 < k) {
        pos += posT+1;
        array += posT+1;
        len = len - posT - 1;
     } else {
        len = posT;
     }
   }
   return data[k-1];
}

unsigned int findMinimumKSmartPivot(unsigned long* data, int length, unsigned int k) {
   int pos = 0;
   unsigned long * array = data;
   int len = length;
   int count = 0;

   while(1) {
     count ++;
     unsigned long pivot = selectPivot(array, len);
     //printf("pivot is %lu, len is %d\n", pivot, len);
     int posT = partialQuickSortByPivotValue(array, len, pivot);
     //printf("posT is %d\n", posT);
     //printArray(array, len);
     if(pos+posT+1 == k) {
        break;
     } else if (pos+posT+1 < k) {
        pos += posT+1;
        array += posT+1;
        len = len - posT - 1;
     } else {
        len = posT;
     }
   }
   return data[k-1];
}

int main() {
  unsigned long dataForSort1[]={10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  unsigned long dataForSort2[]={81509631,17360533,15539299,64493064,64645058,87825487,  
                      33900461,4945505,15941463,71719600,33547516,7519808,  
                      26594898,29884844,27119583,81863654,59673947,84147293,  
                      9059351,7602292,83556926,37027377,75613515,93681811,  
                      7952779,60044456,98264756,67951181,26925847,22994199,  
                      31900994,18462642,9142808,36512424,8589397,65003012,  
                      50519485,63287896,27573828,82252268,63300436,87128823,  
                      48058746,8633666,55332881,61522155,88747604,29979896,  
                      22489406,43687198,2492180,91630320,16002389,75781403,  
                      57871937,8803618,89285976,11751109,40281540,22122151,  
                      13194234,18823824,70845645,55985568,10967476,92437158,  
                      89459068,17676128,66174144,39733764,17145305,75974958,  
                      11895329,59458458,14862124,20811108,9863145,51935822,  
                      33956581,17530466,15311298,8616585,22966662,65420236,  
                      44315494,76347881,93961092,78556039,3529430,73342285,  
                      38929178,36935665,39496167,18536269,71760501,83187750,  
                      67284000,91035727,66780185,94022027,12416029,35114323,  
                      59427850,31203431,10652528,35584440,28212772,84184997,  
                      59600395,4622020,32839956,58298468,400951,94479104,77962861,  
                      82427078,78885887,38543465,94902132,85359893,26182181,  
                      1299345,25702676,51437241,29489005,52205900,58991659,95743251,  
                      22271901,2074436,40743771,46382245,53875748,48138885,19686345,  
                      12289464,44726496,26239089,84581121,64361813,82495717,59275005,  
                      19287553,57530620,31526077,25269250,4957225,21500576,38595138,  
                      70705661,35608130,47769609,24306886,5200032,68301732,40811553,  
                      43024796,24475167,48355438,25501447,28554316,31471507,47641698,  
                      63229167,63685827,96720378,54736518,19690144,7705313,5972805,  
                      5902292,18461652,20283817,74773721,63408346,1334492,15542468,  
                      16486207,39129819,63788537,6178430,17315589,27070237,20483236,  
                      1082584,96921242,25938585,71799656,31463668,93111205,91860702,  
                      23510866,85667996,76688782,4609454,79901560,61821340,79590883,  
                      57517711,62374479};
  int length = sizeof(dataForSort2)/sizeof(unsigned long);
  unsigned long intK = 0;
  unsigned long* dataForSortSrc = (unsigned long*)malloc(length*sizeof(unsigned long));
  memcpy((void*)dataForSortSrc, (void*)dataForSort2, length*sizeof(unsigned long));

//  quickSort(dataForSortSrc, length);
//  printArray(dataForSortSrc, length);

  int i;
  for(i=0;i<length;i++) {

    //compareCount = 0;
    memcpy((void*)dataForSortSrc, (void*)dataForSort2, length*sizeof(unsigned long));
    
    // test partial quick sort
    //partialQuickSortByPivotValue(dataForSortSrc, length, i+1);
    //printArray(dataForSortSrc, length);

    // test pivot selection
    // unsigned long pivot = selectPivot(dataForSortSrc, length);
    // printf("pivot is %lu\n", pivot);
    // int posT = partialQuickSortByPivotValue(dataForSortSrc, length, pivot);
    // printArray(dataForSortSrc, length);
    // printf("posT is %d\n", posT);

    intK = findMinimumK(dataForSortSrc, length, i+1);
    printf("The minimum %03d is : %lu, compareCount = %lu\n", i+1, intK, compareCount);

    memcpy((void*)dataForSortSrc, (void*)dataForSort2, length*sizeof(unsigned long));
    intK = findMinimumKSmartPivot(dataForSortSrc, length, i+1);
    printf("The minimum %03d is : %lu, compareCount = %lu\n", i+1, intK, compareCount);
  }
  free(dataForSortSrc);
}
