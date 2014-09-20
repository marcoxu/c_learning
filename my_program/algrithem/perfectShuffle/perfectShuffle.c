#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int swap_count = 0;
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

void perfectShuffle(int* cards, int size) {
  if(cards == NULL || size <= 0 || size%2 != 0) {
    printf("perfectShuffle error: invalide input\n");
    return;
  }

  long curPos = size - 1;
  long aPosHead = (size-1)/2;
  long bPosHead = curPos;
  long bPosEnd = bPosHead;
  long bPosWrap = bPosHead;
  long bPosHead2 = bPosHead;

  while(aPosHead >= 0) {
    printArray(cards, size);
    printf("aPosHead = %d, bPosHead = %d, bPosWrap = %d, bPosHead2 = %d, curPos = %d\n\n", cards[aPosHead], cards[bPosHead], cards[bPosWrap], cards[bPosHead2], cards[curPos]);
    if(curPos%2) {
      if(bPosHead != curPos) {
    	swap(cards, curPos, bPosHead);
    	if(bPosHead2<=bPosHead) {
    	  bPosHead2 = bPosHead;
    	} else if(bPosHead2 == curPos) {
          bPosHead2 --;

          long tPos = bPosHead - 1;
          for(tPos; tPos > bPosWrap; tPos --) {
    	     swap(cards, tPos, tPos+1);
          }

          if(bPosHead2 == bPosHead) {
            bPosHead2 = bPosWrap;
          }
        }
    	curPos --;
    	bPosHead --;
    		
    	if(bPosHead < bPosWrap) {
    	  if(bPosHead < bPosHead2) {
    	    bPosHead = bPosHead2;
    	  }

          if(bPosWrap > aPosHead + 1) {
            long tPos = bPosWrap - 1;
            for(tPos; tPos > aPosHead; tPos --) {
    	       swap(cards, tPos, tPos+1);
            }
            bPosWrap = aPosHead + 1;
          }

          if(bPosHead == bPosHead2) {
            bPosHead2 = bPosWrap;
          }
    	}
      } else {
        curPos --;
        bPosHead --;
        bPosEnd = bPosHead;
        bPosWrap = bPosHead;
        bPosHead2 = bPosHead;
      }
    } else {
      if(bPosHead != curPos) {
    	swap(cards, curPos, aPosHead);
    	if(bPosHead2 == bPosWrap) {
    	  bPosHead2 = aPosHead;
    	  bPosWrap = aPosHead;
    	}
      } else {
   	swap(cards, curPos, aPosHead);
   	bPosHead = aPosHead;
   	bPosWrap = bPosHead;
   	bPosHead2 = bPosHead;
      }
      
      aPosHead --;
      curPos --;
    }
  }

  printArray(cards, size);
  return;
}

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

  printArray(cards, size);
  return;
}

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

  printArray(cards, size);
  return;
}

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

  printArray(cards, size);
  return;
}

int main() {
  int dataForSort1[]={10, 8, 6, 4, 2, 9, 7, 5, 3, 1};
  int dataForSort2[]={20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 
                      19, 17, 15, 13, 11, 9, 7, 5, 3, 1};
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

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort1, sizeof(dataForSort1));
  perfectShuffleImplA(dataCopyofSrc, 10);
  printf("perfectShuffleImplA: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort2, sizeof(dataForSort2));
  perfectShuffleImplB(dataCopyofSrc, 20);
  printf("perfectShuffleImplB: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort3, sizeof(dataForSort3));
  perfectShuffleImplB(dataCopyofSrc, 50);
  printf("perfectShuffleImplB: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort4, sizeof(dataForSort4));
  perfectShuffleImplB(dataCopyofSrc, 2);
  printf("perfectShuffleImplB: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((void*)dataCopyofSrc, (const void*)dataForSort5, sizeof(dataForSort5));
  perfectShuffleImplB(dataCopyofSrc, 70);
  printf("perfectShuffleImplB: swap_count = %d\n\n", swap_count);
  swap_count = 0;

  memcpy((char*)dataCopyofSrc, (const void*)dataForSort5, sizeof(dataForSort5));
  perfectShuffleImplA(dataCopyofSrc, 70);
  printf("perfectShuffleImplA: swap_count = %d\n\n", swap_count);
}


