#include <stdio.h>
#include "quick.h"

int quickSort(int* in, int len, int low, int high)
{
    if(in == NULL || len < 0|| low < 0 || high < 0){
        return -1;
    }

    if(low > high || high >= len ){
        return -1;
    }
    
    // find the right position of low
    int i = low;
    int j = high;
    int tmp = in[low];
    for(;i<j;){
        for(;j>i;){
            if(tmp < in[j]){
                // exchange in[i] and in[j]
                int s = in[i];
                in[i] = in[j];
                in[j] = s;
                i++;
                break;
            }else{
                j--;
            }
        }

        for(;j>i;){
            if(tmp > in[i]){
                // exchange in[i] and in[j]
                int s = in[i];
                in[i] = in[j];
                in[j] = s;
                j--;
                break;
            }else{
                i++;
            }
        }
    }
 
    int x;
    for(x=0;x<len;x++){
        printf("%d ", in[x]);
    }
    printf("\n");

    
    if(i - low > 1){
        quickSort(in, len, low, i-1);
    }
    
    if(high - i > 1){
        quickSort(in, len, i+1, high);
    }
    
    return 0;
}

int* quickSorting(int* in, int len)
{
    if(in == NULL || len <= 0){
        return NULL;
    }
    
    if(len == 1){
        return in;
    }
    
    int ret = quickSort(in, len, 0, len-1);
    if(ret > 0)
        return in;
    else
        return NULL;
}

