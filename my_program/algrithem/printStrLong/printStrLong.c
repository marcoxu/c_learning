#include <stdio.h>
#include <stdlib.h>


static long MAX_LONG = ~((unsigned long)1<<(8*sizeof(unsigned long)-1));
static long MIN_LONG = ((unsigned long)1<<(8*sizeof(unsigned long)-1));


void printStrLong(char* numberStr) {
  if(numberStr == NULL) {
    printf("printStrLong error: NULL pointer\n");
    return;
  }

  long value = 0;
  long sign = 1;
  int pos = 0;
  int checkFirst = 0;
  char cPos;

  // check sign
  if(numberStr[0] == '-') {
    sign = -1;
    pos ++;
  } else if (numberStr[0] == '+') {
    pos ++;
  }

  while((cPos=numberStr[pos++]) != '\0') {
    long vPos = 0;

    if(cPos >= '0' && cPos <= '9') {
      vPos = sign * (cPos - '0');

      // check range of long
      if(sign == 1) {
        if(value != 0 &&
          ((MAX_LONG-vPos)/value < 10 ||
           ((MAX_LONG-vPos)/value == 10 && 
            (MAX_LONG-vPos)%value != 0))) {
          printf("printStrLong error: out of range - '+'\n");
          return;
        }
          
      } else {
        if(value != 0 &&
          ((MIN_LONG-vPos)/value < 10 ||
           ((MIN_LONG-vPos)/value == 10 && 
            (MIN_LONG-vPos)%value != 0))) {
          printf("printStrLong error: out of range - '-'\n");
          return;
        }
          
      }
      
      value = value*10 + vPos;
    } else {
      printf("printStrLong error: invalid charactor is detected - '%c'\n", cPos);
      return;
    }
  }

  printf("printStrLong: '%s' = %ld\n", numberStr, value);
  return;
}

int main() {
  char* dataForSort1 ="9223372036854775807";
  char* dataForSort2 ="-9223372036854775808";
  char* dataForSort3 ="+9223372036854775808";
  char* dataForSort4 ="+9223372036854775807";
  char* dataForSort5 ="+1392233720368775807";
  char* dataForSort6 ="+d1392233720368775807";

  printStrLong(dataForSort1);
  printStrLong(dataForSort2);
  printStrLong(dataForSort3);
  printStrLong(dataForSort4);
  printStrLong(dataForSort5);
  printStrLong(dataForSort6);
}
