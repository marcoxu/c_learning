#include <stdio.h>
#include "shell.h"

/*
 *   shell sorting
*/
int* shellSorting(int* in, int len)
{
    if(in == NULL || len < 0){
        return NULL;
    }

    if(len == 1){
        return in;
    }
    
    int span = len/2;
    int i, j, round;
    
    for(round=1;span>0;span/=2,round++){
        // insert sorting the sub array
        for(i=0;i<span;i++){
            for(j=i;j<len;j+=span){
                // insert sorting
                int k;
                for(k=i;k<j;k+=span){
                    if(in[j] < in[k]){
                        int tmp = in[j];
                        int from = j;
                        for(;from>k;from-=span){
                            in[from] = in[from-span];
                        }
                        in[k] = tmp;
                    }
                }
            }
        }
        
        int k;
        printf("Shell sort round %d:", round);
        for(k=0;k<len;k++){
            printf("%d ", in[k]);
        }
        printf("\n");
    }
    return in;
}
