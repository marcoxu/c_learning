#include <stdio.h>
#include <stdlib.h>

/* 
 Find the longest sub string which contains brackets in pairs
 */
int findSubString(char* src, char** start) {
  if(src == NULL) {
    *start = NULL;
    return 0;
  }

  char* curMaxStart = NULL;
  char* tmpStart = NULL;
  int curMaxLength = 0;
  int tmpLength = 0;
  int curCount = -1;
  int curPos = 0;

  /*
   Loop over the string
   For example:
   (   )  )  )  (  (  (  (  (  (  (  )  (  )  )  )  )  )  )  )  )  )  )  (   )  (  (  (  (  (  (  )  )
   1   0 -1 -1  1  2  3  4  5  6  7  6  7  6  5  4  3  2  1  0 -1 -1 -1  1   0  1  2  3  4  5  6  5  4
   |-2-|        |----------------- 16 -----------------------|           |-2-|              |----4---|
   
   Max sub string length is 16.   
  */
  while(src[curPos]) {
    if(curCount == -1) {
      if(src[curPos] == '(') {
        tmpStart = src + curPos;
        tmpLength = 0;
        curCount = 1;
      }
    } else if (curCount == 0) {
      if(src[curPos] == '(') {
        curCount ++;
      } else {
        curCount = -1;
      }
    } else {
      if(src[curPos] == '(') {
        curCount ++;
      } else {
        if (src[curPos] == ')') {
          curCount --;
          if(curCount == 0)
            tmpLength = curPos - (tmpStart - src) + 1;
        } else {
          curCount = -1;
        }
        
        if(curCount <= 0) {
          if(tmpLength > curMaxLength) {
            curMaxLength = tmpLength;
            curMaxStart = tmpStart;
          }
        }
      }
    }
    //printf("src[curPos] = %c, curCount = %d, tmpLength = %d\n", src[curPos], curCount, tmpLength);
    curPos ++;
  }

  if(curCount > 0) {
    tmpStart = tmpStart + tmpLength + curCount;
    tmpLength = src + curPos - tmpStart;
    if(tmpLength > curMaxLength) {
      curMaxLength = tmpLength;
      curMaxStart = tmpStart;
    }
  }

  *start = curMaxStart;
  return curMaxLength;
}

int main() {
  const char* srcString = "()))((((((()())))))))))()(((((())";
  const char* srcStringa = "()()()()()()()()()()()()";
  const char* srcStringb = "())())())())";
  const char* srcStringc = "())(((((())";
  char* subStart = NULL;

  int length = findSubString((char*)srcString, &subStart);
  int i = 0;
  printf("length is %d\n", length);

  for(i;i<length && subStart != NULL;i++) {
    printf("%c", subStart[i]);
  }
  printf("\n");
}




