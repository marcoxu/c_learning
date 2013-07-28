#include <stdio.h>
#include "merge.h"

/*
 *   ¹鲢ÅÐ
 */

static int global_static_var = 10;
int global_int = 101;

int merge(int* in, int len, int low, int mid, int high)
{
    printf("global static address: %p\n", &global_static_var);
    printf("global int address: %p\n", &global_int);

    if(in == NULL || len < 0|| low < 0 || high < 0 || mid < 0){
        return -1;
    }
    
    if(low > mid || low > high || mid > high || high >= len ){
        return -1;
    }

    int tmp[len];
    int pos = 0;
    int i = low;
    int j = mid + 1;
    for(;i<=mid&&j<=high;){
        // compare in[i] and in[j]
        if(in[i] >= in[j]){
             tmp[pos] = in[i];
             pos ++;
             i++;    
        }else if(in[i] < in[j]){
             tmp[pos] = in[j];
             pos ++;
             j++;    
        }
    }
    
    if(i > mid){
        for(;j<=high;j++){
             tmp[pos] = in[j];
             pos ++;
        }
    }else if(j > high){
        for(;i<=high;i++){
             tmp[pos] = in[i];
             pos ++;
        }
    }
    
    for(i=low;i<=high;i++){
        in[i] = tmp[i-low];
        printf("%d ", in[i]);
    }
    printf("\n");
    return 0;
}

int* recursionMergeSorting(int* in, int len)
{
    if(in == NULL || len < 0){
        return NULL;
    }

    if(len == 1){
        return in;
    }
    
    int mid = len/2;
    mergeSorting(in, mid);
    mergeSorting(in+mid, len-mid);
    printf("Merge [");
    int i;
    for(i=0;i<mid;i++){
        printf("%d ", in[i]);
    }
    printf("] and [");
    for(i=mid;i<len;i++){
        printf("%d ", in[i]);
    }
    printf("]:\n");

    merge(in, len, 0, mid-1, len-1);
    return in;
}


int* mergeSorting(int* in, int len)
{
    printf("global static address: %p\n", &global_static_var);
    printf("global int address: %p\n", &global_int);

    if(in == NULL || len < 0){
        return NULL;
    }

    if(len == 1){
        return in;
    }
    
    int sublen = 1;
    int i,j;
    
    while(sublen <= len){
        for(i=0;i<len;i+=2*sublen){
            int high = i+2*sublen-1;
            if(high > len-1)
                high = len - 1;
            printf("Merge [");
            int j;
            for(j=i;j<i+sublen&&j<len;j++){
                printf("%d ", in[j]);
            }
            printf("] and [");
            for(j=i+sublen;j<high+1&&j<len;j++){
                printf("%d ", in[j]);
            }
            printf("]:\nmerge(in+%d,%d,%d,%d,%d)\n",0,len,i,i+sublen-1,high);

            merge(in, len, i, i+sublen-1, high);
        }
        sublen *= 2;
    }
    return in;
}
