#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printString(char* src, int length) {
  int i;
  for(i=0;i<length;i++) {
    printf("%c", src[i]);
  }
  printf("\n");
}


void stringPlus(char* src, int value, int pos) {
  if(src == NULL || value == 0) {
    return;
  }

  int digAtPos = src[pos] - '0';
  src[pos] = (digAtPos + value)%10 + '0';
  int increase = (digAtPos + value)/10;

  if(increase > 0) {
    stringPlus(src, increase, pos+1);
  }
}

void swapString(char* src, int length) {
  if(src == NULL || length <= 0) {
    return;
  }
  
  int i;
  int pos = 0;
  for(i=length-1;i>=0;i--) {
    if(src[i]!='0') {
      pos = i;
      break;
    }
  }
  src[pos+1] = '\0';

  for(i=0;i<(pos+1)/2;i++) {
    char tmp = src[i];
    src[i] = src[pos-i];
    src[pos-i] = tmp;
  }
}

char* longIntTimes(char* arg0, char* arg1) {
  if(arg0 == NULL || arg1 == NULL) {
    return NULL;
  }

  int length0 = strlen(arg0);
  int length1 = strlen(arg1);
  int lengthResult = length0 + length1 + 2;
  char* longResult = (char*) malloc(lengthResult);

  // init the memory
  memset(longResult, lengthResult, 0);
  int i,j;
  for(i=0;i<lengthResult-1;i++){
    longResult[i] = '0';
  }

  for(i=length1-1; i>=0; i--) {
    int operator1 = arg1[i] - '0';
    int increase = 0;
    int posFromEnd = length1-1-i;

    for(j=length0-1; j>=0; j--) {
      int operator0 = arg0[j] - '0';
      int tmpRes = operator0*operator1;
      int value = tmpRes%10;
      increase = tmpRes/10;
      stringPlus(longResult, value, posFromEnd+(length0-1-j));
      stringPlus(longResult, increase, posFromEnd+(length0-1-j)+1);
    }
  }
  swapString(longResult, lengthResult-1);
  return longResult;
}

int main() {
  char* valueA = "1599968000239999200001";
  char* valueB = "1599968000239999200001";

  char* result = longIntTimes(valueA, valueB);
  if(result != NULL) { 
    printf("Result is %s\n", result);
  }

  free(result);
}















