#include <stdio.h>
#include <string.h>

/*
 *   ÊÈ×·�����½«Æ·­ת
 *   Example:  abcdedf ---> fdedcba
 */
char* revertString(char* in)
{
    if(in == NULL){
        return NULL;
    }
    
    int len = strlen(in);
    if(len <= 1){
        return in;
    }
    
    int n = len/2;
    char* s = in;
    int i;
    for(i=0;i<n;i++,s++){
        // exchange in[i] and in[len-1-i]
        char tmp = in[i];
        in[i] = in[len-1-i];
        in[len-1-i] = tmp;
    }
    return in;
}

int main()
{
    char buff[256];
    int  i = 0;
    printf("Input the string:\n");
    while(1){
         char c = getchar();
         if(c == '\n'){
             buff[i] = '\0';
             break;
         }
         if(i+1 > 255){
             buff[255] = '\0';
             break;
         }
         buff[i] = c;
         i++;
    }
    
    if(revertString(buff) != NULL){
        printf("Convert result:\n%s\n", buff);
    }
}
