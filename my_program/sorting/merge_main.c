#include <stdio.h>
#include "merge.h"

int main()
{
    int buff[256];
    int  i = 0;
    printf("Input the integers that needs to be sorted:\n");
    while(1){
         if(i > 255){
             i--;
             break;
         }
         scanf("%d",&buff[i]);
         if(buff[i] == -1){
             break;
         }
         i++;
    }

    //if(recursionMergeSorting(buff, i) != NULL){
    if(mergeSorting(buff, i) != NULL){
        printf("Sort result:\n");
        int j = 0;
        for(j=0;j<i;j++){
            printf("%d ", buff[j]);
        }
        printf("\n");
    }

    scanf("%d",&buff[0]);
}

