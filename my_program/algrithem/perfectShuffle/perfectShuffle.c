#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int swap_count = 0;
static const int DIVID_GROUP = 2;

#define swap(array, from, to) {int temp = (array)[from]; (array)[from] = (array)[to]; (array)[to] = temp; swap_count++;}

void printArray(int * array, unsigned int length) {
  int i = 0;
  int count = 0;
  for(i=0;i<length;i++) {
     printf("%02d, ", array[i]);
     if(count%10 == 9)
       printf("\n");
     count ++;
  }
  printf("\n");

}

// move: time: O(N^2) space: O(1)
void perfectShuffleImpl(int* cards, int size) {
  if(cards == NULL || size <= 0 || size%2 != 0) {
    printf("perfectShuffle error: invalide input\n");
    return;
  }

  if(size == 2) {
    printArray(cards, size);
    return;
  }

  long curPos = size - 1;
  long aPosHead = (size-1)/2;
  long bPosHead = -1;
  long bPosEnd = -1;

  while(curPos > 0) {
    printf("\n\n");
    printArray(cards, size);
    printf("aPosHead = %d, bPosHead = %d, bPosEnd = %d, curPos = %d\n", cards[aPosHead], bPosHead<0?-1:cards[bPosHead], bPosEnd<0?-1:cards[bPosEnd], cards[curPos]);


    if(curPos%2) { // insert number in b list
      if(bPosHead == curPos) {
        if(bPosHead-1 > aPosHead) {
          bPosHead--;
        } else {
          bPosHead = -1;
          bPosEnd = -1;
        }
        curPos --;
        continue;
      }

      if(bPosHead == -1) {

      } else {
        swap(cards, curPos, bPosHead);

        if(bPosHead == bPosEnd) {
          bPosEnd = bPosHead;
        } else if (bPosHead > bPosEnd) {
          swap(cards, bPosEnd-1, bPosHead);
          bPosEnd --;
          bPosHead --;
          if(aPosHead == bPosEnd) {
            aPosHead = bPosHead + 1;
          }
        } else {
          printf("Error: bPosHead = %d less than bPosEnd = %d\n\n", bPosHead<0?-1:cards[bPosHead], bPosEnd<0?-1:cards[bPosEnd]);
        }
      }

      if(aPosHead == curPos) {
        aPosHead = bPosEnd - 1;
      }
      curPos --;
    } else { // insert number in a list
      if(aPosHead == curPos) {
        if(aPosHead > bPosHead) {
          aPosHead = bPosEnd - 1;
        } else {
          aPosHead --;
        }
        curPos --;
        continue;
      }

      swap(cards, curPos, aPosHead);
      
      if(bPosHead == -1) {
        bPosHead = aPosHead;
        bPosEnd = bPosHead;
        aPosHead --;
      } else if(aPosHead-1 == bPosHead) {
        swap(cards, aPosHead, bPosEnd-1);
        bPosEnd --;
      } else if (aPosHead == bPosEnd-1) {
        aPosHead --;
        bPosEnd --;
      } else {
        // move backward from bPosEnd to aPosHead -1
        int tPos = aPosHead - 1;
        for(tPos; tPos >= bPosEnd; tPos --) {
          swap(cards, tPos, tPos+1);
          bPosHead ++;
        }
      }
      
      if(bPosHead == curPos) {
        bPosHead --;
      }
      curPos --;
    }
  }
  return;
}

// move: time: O(N^2) space: O(1)
void perfectShuffleImplA(int* cards, int size) {
  if(cards == NULL || size <= 0 || size%2 != 0) {
    printf("perfectShuffle error: invalide input\n");
    return;
  }

  if(size == 2) {
    printArray(cards, size);
    return;
  }

  long curPos = size - 1;
  long aPosHead = (size-1)/2;
  long bPosHead = -1;

  while(curPos > 0) {
    //printf("\n\n");
    //printArray(cards, size);
    //printf("aPosHead = %d, bPosHead = %d, curPos = %d\n", cards[aPosHead], bPosHead<0?-1:cards[bPosHead], cards[curPos]);


    if(curPos%2) { // insert number in b list
      if(bPosHead == curPos) {
        if(bPosHead-1 > aPosHead) {
          bPosHead--;
        } else {
          bPosHead = -1;
        }
        curPos --;
        continue;
      }

      if(bPosHead != -1) {
        swap(cards, curPos, bPosHead);
        // move backward from aPosHead+1 to bPosHead -1
        int tPos = bPosHead - 1;
        for(tPos; tPos > aPosHead; tPos --) {
          swap(cards, tPos, tPos+1);
        }
      }

      curPos --;
    } else { // insert number in a list
      swap(cards, curPos, aPosHead);
      
      if(bPosHead == -1) {
        bPosHead = aPosHead;
      } else if(bPosHead == curPos) {
        // move forward from aPosHead to bPosHead -1
        int tPos = aPosHead;
        for(tPos; tPos < bPosHead-1; tPos ++) {
          swap(cards, tPos, tPos+1);
        }
        bPosHead --;
      }
      aPosHead --;
      curPos --;
    }
  }
  return;
}

// move: time: O(N^2) space: O(1)
void perfectShuffleImplB(int* cards, int size) {
  if(cards == NULL || size <= 0 || size%2 != 0) {
    printf("perfectShuffle error: invalide input\n");
    return;
  }

  if(size == 2) {
    printArray(cards, size);
    return;
  }

  long curPos = size - 1;
  long aPosHead = (size-1)/2;
  long bPosHead = -1;
  int wrapArround = 0;

  while(curPos > 0) {
    //printf("\n\n");
    //printArray(cards, size);
    //printf("aPosHead = %d, bPosHead = %d, curPos = %d, wrapArround = %d\n", cards[aPosHead], bPosHead<0?-1:cards[bPosHead], cards[curPos], wrapArround);


    if(curPos%2) { // insert number in b list
      if(bPosHead == curPos) {
        if(bPosHead-1 > aPosHead) {
          bPosHead--;
        } else {
          bPosHead = -1;
        }
        curPos --;
        continue;
      }

      if(bPosHead != -1) {
        swap(cards, curPos, bPosHead);
        // move backward from aPosHead+1 to bPosHead -1
        int tPos = bPosHead - 1;
        for(tPos; tPos > aPosHead; tPos --) {
          swap(cards, tPos, tPos+1);
        }
      }

      curPos --;
    } else { // insert number in a list
      swap(cards, curPos, aPosHead);
      
      if(bPosHead == -1) {
        if(!wrapArround) {
          bPosHead = aPosHead;
        }
      } else if(bPosHead == curPos) {
        bPosHead = aPosHead;
      }
      aPosHead --;
      curPos --;
    }
  }
  return;
}

#define FIND_NEXT_IN_CYCLE(size, i)   (2*((i))%((size)+1))

int getNextInCycle(int size, int index) {
  if(index <= size/2) {
    return 2*index - 1;
  } else {
    return 2*index - size;
  }
}

// move: time: O(N) space: O(1)
// a1, a2, a3, ..., an, b1, b2, b3, ... , bn ===>
// a1, b1, a2, b2, a3, b3, ..., an-1, bn-1, an, bn
//
// The array can be divided into k circles and the shuffle can be done
// by right rotating all circles with 1 step. for example:
// source array: 8, 6, 4, 2, 7, 5, 3, 1
//     circle 1: 8, 6, 2, 1, 3, 7 --> 7, 8, 6, 2, 1, 3
//     circle 2: 4, 5             --> 5, 4
// After rotation: 7, 8, 5, 6, 3, 4, 1, 2
void perfectShuffleImplC(int* cards, int size) {
  if(cards == NULL || size <= 0 || size%2 != 0) {
    printf("perfectShuffle error: invalide input\n");
    return;
  }

  if(size == 2) {
    printArray(cards, size);
    return;
  }

  int curPos = 1;
  for(curPos; curPos <= size; curPos++) {
    if(cards[curPos-1] > 0) {
      int from = getNextInCycle(size, curPos);
      int curr = cards[curPos-1];
      for(from; from != curPos; from = getNextInCycle(size, from)) {
        int tmp = cards[from-1];
        cards[from-1] = -1*curr;
        curr = tmp;
        swap_count ++;
      }
      cards[from-1] = -1*curr;
      swap_count ++;
    }
  }

  for(curPos=0; curPos < size/2; curPos++) {
    cards[2*curPos] *= -1;
    cards[2*curPos+1] *= -1;
  }

  return;
}

void reverse(int* src, int size) {
  if(src == NULL || size < 1) {
    printf("reverse error: invalide input\n");
    return;
  }

  int i;
  for(i=0;i<size/2;i++) {
    swap(src, i, size-i-1); 
  }
}

void rightMoveCycle(int* src, int start, int size) {
  if(src == NULL || size <= 0 || size%2 != 0 || start <= 0 || start > size) {
    printf("rightMoveCycle error: invalide input\n");
    return;
  }

  if(size == 2) {
    return;
  }

  printf("circle: %d, ", start);
  int from = FIND_NEXT_IN_CYCLE(size, start);
  int curr = src[start-1];
  for(from; from != start; from = FIND_NEXT_IN_CYCLE(size, from)) {
    printf(" %d, ", from);
    int tmp = src[from-1];
    src[from-1] = curr;
    curr = tmp;
    swap_count ++;
  }
  src[from-1] = curr;
  swap_count ++;
  printf("\n");
}

// move: time: O(N) space: O(1)
// It is similar with perfectShuffleImplC. For array with length = 3^(k-1), the circles are startd
// at 1, 3, 9 ... 3^(k-1). For array with rando length, it can be divided into 2 arrays:
// 1st: array[0] ~ array[3^(k-1)-1]
// 2nd: array[3^(k-1)] ~ array[size-1]
// For first array, it can be handled like perfectShuffleImplC. And for the 2nd array, it can be handled
// recursivly as the source array.
void perfectShuffleImplD(int* cards, int size) {
  if(cards == NULL || size <= 0 || size%2 != 0) {
    printf("perfectShuffle error: invalide input\n");
    return;
  }

  if(size == 2) {
    return;
  }

  int k = 1;
  while(k<size) {
    k *= 3;
  }
  k /= 3;

  int m = k/2;

  // m~m+size/2 right rotate for m steps
  reverse(cards+m, size/2-m);
  reverse(cards+size/2, m);
  reverse(cards+m, size/2);

  int cycleStart = 1;
  for(cycleStart; cycleStart <= m*2; cycleStart = cycleStart*3) {
      rightMoveCycle(cards, cycleStart, 2*m);
  }

  int i=0;
  for(i;i<2*m;i += 2) {
    swap(cards, i, i+1);
  }
  
  // do the same for cards+2*m ~ cards+size
  perfectShuffleImplD(cards+m*2, size-2*m);
  return;
}

int main() {
  int dataForSort1[]={8, 6, 4, 2, 7, 5, 3, 1};
  int dataForSort2[]={18, 16, 14, 12, 10, 8, 6, 4, 2, 
                      17, 15, 13, 11, 9, 7, 5, 3, 1};
  int dataForSort3[]={50, 48, 46, 44, 42,
                      40, 38, 36, 34, 32,
                      30, 28, 26, 24, 22,
                      20, 18, 16, 14, 12,
                      10, 8, 6, 4, 2, 
                      49, 47, 45, 43, 41,
                      39, 37, 35, 33, 31,
                      29, 27, 25, 23, 21,
                      19, 17, 15, 13, 11,
                      9, 7, 5, 3, 1};
  int dataForSort4[]={1,2};
  int dataForSort5[]={70, 68, 66, 64, 62,
                      60, 58, 56, 54, 52,
                      50, 48, 46, 44, 42,
                      40, 38, 36, 34, 32,
                      30, 28, 26, 24, 22,
                      20, 18, 16, 14, 12,
                      10, 8, 6, 4, 2, 
                      69, 67, 65, 63, 61,
                      59, 57, 55, 53, 51,
                      49, 47, 45, 43, 41,
                      39, 37, 35, 33, 31,
                      29, 27, 25, 23, 21,
                      19, 17, 15, 13, 11,
                      9, 7, 5, 3, 1};

  int* dataCopyofSrc = (int*)malloc(sizeof(int)*100);

  //memcpy((void*)dataCopyofSrc, (const void*)dataForSort1, sizeof(dataForSort1));
  //perfectShuffleImplA(dataCopyofSrc, sizeof(dataForSort1)/sizeof(int));
  //printArray(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  //printf("perfectShuffleImplA: swap_count = %d\n\n", swap_count);
  //swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort1, sizeof(dataForSort1));
  perfectShuffleImplD(dataCopyofSrc, sizeof(dataForSort1)/sizeof(int));
  printf("perfectShuffleImplD: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort2, sizeof(dataForSort2));
  perfectShuffleImplD(dataCopyofSrc, sizeof(dataForSort2)/sizeof(int));
  printArray(dataCopyofSrc, sizeof(dataForSort2)/sizeof(int));
  printf("perfectShuffleImplD: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  //memcpy((void*)dataCopyofSrc, (const void*)dataForSort2, sizeof(dataForSort2));
  //perfectShuffleImplB(dataCopyofSrc, sizeof(dataForSort2)/sizeof(int));
  //printArray(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  //printf("perfectShuffleImplB: swap_count = %d\n\n", swap_count);
  //swap_count = 0;

  //memcpy((void*)dataCopyofSrc, (const void*)dataForSort2, sizeof(dataForSort2));
  //perfectShuffleImplD(dataCopyofSrc, sizeof(dataForSort2)/sizeof(int));
  //printArray(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  //printf("perfectShuffleImplD: swap_count = %d\n\n", swap_count);
  //swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort3, sizeof(dataForSort3));
  perfectShuffleImplD(dataCopyofSrc, sizeof(dataForSort3)/sizeof(int));
  printArray(dataCopyofSrc, sizeof(dataForSort3)/sizeof(int));
  printf("perfectShuffleImplD: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  //memcpy((void*)dataCopyofSrc, (const void*)dataForSort4, sizeof(dataForSort4));
  //perfectShuffleImplB(dataCopyofSrc, 2);
  //printArray(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  //printf("perfectShuffleImplB: swap_count = %d\n\n", swap_count);
  //swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort5, sizeof(dataForSort5));
  perfectShuffleImplB(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  printArray(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  printf("perfectShuffleImplB: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((char*)dataCopyofSrc, (const void*)dataForSort5, sizeof(dataForSort5));
  perfectShuffleImplC(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  printArray(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  printf("perfectShuffleImplC: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((char*)dataCopyofSrc, (const void*)dataForSort5, sizeof(dataForSort5));
  perfectShuffleImplD(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  printArray(dataCopyofSrc, sizeof(dataForSort5)/sizeof(int));
  printf("perfectShuffleImplD: swap_count = %d\n\n", swap_count);
  swap_count = 0;
}



