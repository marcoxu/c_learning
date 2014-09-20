#include <stdio.h>
#include <stdlib.h>
#include "quickSort.h"

static long MAX_LONG = ~((unsigned long)1<<(8*sizeof(unsigned long)-1));
static long MIN_LONG = ((unsigned long)1<<(8*sizeof(unsigned long)-1));

void quickSort(unsigned long* array, int length) {
  if(array == NULL || length <= 1) {
    return;
  }

  int from, end;
  int pos = 0;
  from = pos;
  end = length - 1;
  int fromEnd = 1;

  while(from <= end) {
    if(fromEnd) {
       if(array[end] < array[pos]) {
         fromEnd = 0;
         unsigned long temp = array[end];
         array[end] = array[pos];
         array[pos] = temp;
         pos = end;
       }
       end --;
       //printArray(array, length);
    } else {
       if(array[from] > array[pos]) {
         fromEnd = 1;
         unsigned long temp = array[from];
         array[from] = array[pos];
         array[pos] = temp;
         pos = from;
       }
       from ++;
       //printArray(array, length);
    }
  }


  quickSort(array, pos);
  quickSort(array+pos+1, length-pos-1);
  return;
}

void quickSortImpl1(unsigned long* array, int length) {
  if(array == NULL || length <= 1) {
    return;
  }

  int from, end;
  from = 0;
  end = length - 1;
  int fromEnd = 1;
  unsigned long value = array[length/2];

  do {
     while(array[from] < value) from ++;
     while(array[end] > value) end --;
     if(from < end) {
         unsigned long temp = array[from];
         array[from] = array[end];
         array[end] = temp;
         from ++;
         end --;
     }
  } while (from < end);


  quickSortImpl1(array, from);
  quickSortImpl1(array+from+1, length-from-1);
  return;
}

void printArray(unsigned long * array, unsigned int length) {
  int i = 0;
  for(i=0;i<length;i++) {
     printf("%lu, ", array[i]);
  }
  printf("\n");
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

  printArray(dataForSort1, sizeof(dataForSort1)/sizeof(unsigned long));
  quickSortImpl1(dataForSort1, sizeof(dataForSort1)/sizeof(unsigned long));
  printArray(dataForSort1, sizeof(dataForSort1)/sizeof(unsigned long));
  printf("MAX=%ld\n", MAX_LONG);
  printf("MIN=%ld\n", MIN_LONG);
}
