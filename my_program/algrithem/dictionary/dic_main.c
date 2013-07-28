#include <stdio.h>

int gen_string(char* orig, int size, int* result)
{
    if(orig == NULL || size <= 0 || result == NULL){
        return -1;
    }
    
    int start = -1;
    int len = size + 1;
    int startValue = 0;
    int i, j;
    result[0] = 1;
   
    for(i=0;i<size;i++){
        if(orig[i] == 'I'){
            if(start == -1 && i == 0){
                startValue ++;
                result[i] = startValue;
                result[i+1] = result[i] + 1;
                start = i;
                continue;
            }else if(i - start == 1){
                startValue ++;
                result[i+1] = startValue;
                start = i;
                continue;
            }
            
            if(start < i){
               int contuneD = i - start - 1;
               result[start+1] = result[start+1] + contuneD;
               
               for(j=start+1; j<i; j++){
                   result[j+1] = result[j] - 1;
               }
               startValue = result[start+1] + 1;
               result[i+1] = startValue;
               start = i;
            }
        } else if(orig[i] == 'D') {
            continue;
        } else {
            return -1;
        }
    }
    
    if(orig[size-1] == 'D'){
        if(start < size){
           int contuneD = size - start - 1;
           result[start+1] = result[start+1] + contuneD;
           
           for(j=start+1; j<size; j++){
               result[j+1] = result[j] - 1;
           }
        }
    }
    return len;
}

int main()
{
    char buff[256];
    int result[256];
    int  i = 0;
    printf("Input the origin list of (DI):\n");
    while(1){
         if(i > 255){
             i--;
             break;
         }
         scanf("%c",&buff[i]);
         if(buff[i] == '\n'){
             break;
         }
         i++;
    }

    int len = 0;
    if((len = gen_string(buff, i, result)) > 0){
        printf("String result:\n");
        int j = 0;
        for(j=0;j<len;j++){
            printf("%d ", result[j]);
        }
        printf("\n");
    }
}

