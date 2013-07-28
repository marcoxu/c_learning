#include <stdio.h>
#include "pop.h"

/*
 *   ðÅÅÐ
 */
int* popSorting(int* in, int len)
{
    if(in == NULL || len <=0){
        return NULL;
    }
    
    if(len == 1){
        return in;
    }
    
    int i, j;
    int* current = in;
    int change = 0;
    for(i=0;i<len-1;i++){
        for(j=0;j<len-i-1;j++){
            if(current[j]>current[j+1]){
                // exchange current[j] and current[j+1]
                int tmp = current[j];
                current[j] = current[j+1];
                current[j+1] = tmp;
                change = 1;
            }
        }
        printf("Pop sorting result for round %d:", i+1);
        for(j=0;j<len;j++){
            printf("%d ", in[j]);
        }
        printf("\n");
        if(change == 0){
            break;
        }
    }
    return in;
}

