#include <stdio.h>
#include <stdlib.h>
#include "quickSort.h"

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
