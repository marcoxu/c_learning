#include <stdio.h>
#include <stdlib.h>

int findSubString(char* src, char** start) {
  if(src == NULL) {
    *start = NULL;
    return 0;
  }

  char* curLongStart = NULL;
  char* tmpStart = NULL;
  int curLongLength = 0;
  int tmpLength = 0;
  int curCount = -1;
  int curPos = 0;

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
          if(tmpLength > curLongLength) {
            curLongLength = tmpLength;
            curLongStart = tmpStart;
          }
        }
      }
    }
    //printf("src[curPos] = %c, curCount = %d, tmpLength = %d\n", src[curPos], curCount, tmpLength);
    curPos ++;
  }

  *start = curLongStart;
  return curLongLength;
}

int main() {
  const char* srcString = "()))((((((()())))))))))()";
  const char* srcStringa = "()()()()()()()()()()()()";
  const char* srcStringb = "())())())())";
  char* subStart = NULL;

  int length = findSubString((char*)srcString, &subStart);
  int i = 0;
  printf("length is %d\n", length);

  for(i;i<length && subStart != NULL;i++) {
    printf("%c", subStart[i]);
  }
  printf("\n");
}




