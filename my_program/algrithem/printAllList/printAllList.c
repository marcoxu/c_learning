#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(src, x, y) do{ \
                            char a=src[x];  \
                            src[x]=src[y]; \
                            src[y]=a; \
                          }while(0)

int printAllList(char* src, int from, int length) {
  int count = 0;
  if(src == NULL || length == 0){
    printf("Invalid input\n");
    return count;
  }
  
  if(from == length-1) {
    printf("Result is %s\n", src);
    count ++;
    return count;
  }
  
  int i;
  for(i=from;i<length;i++) {
    swap(src, from, i);
    count += printAllList(src, from+1, length);
    swap(src, from, i);
  }
  return count;
}

int main() {
  char src[] = "abc";
  int count = printAllList(src, 0, strlen(src));
  printf("Totally %d lists\n", count);
}
