#include <stdio.h>
#include<stdlib.h>
#include <string.h>

/*
 *   ѰÕ¶ԳÆַû*   Example:  abcdcbaabaa ---> abcdcba, baab, aabaa
 */
 
typedef struct strRange{
    int start;
    int end;
    int len;
    int allSame;
    struct strRange* next;
} dupString;

dupString* createDupString(int start, int end)
{
    if(start <= end && start >= 0){
        dupString* newString = (dupString*)malloc(sizeof(dupString));
        newString->start = start;
        newString->end = end;
        newString->len = start-end+1;
        newString->next = NULL;
        newString->allSame = 0;
        return newString;
    }
    return NULL;
}

void freeDupString(dupString* head)
{
    while(head != NULL){
        dupString* curr = head;
        head = head->next;
        free(curr);
    }
    return;
}

dupString* initDupString(char* in)
{
    if(in == NULL){
        return NULL;
    }
    
    int i=0;
    dupString* strArrayHead = NULL;
    dupString* strArrayCurr = NULL;
    while(in[i] != '\0'){
        dupString* strArrayTmp = NULL;
        if(strArrayHead == NULL){
            strArrayHead = createDupString(i, i);
            strArrayHead->allSame = 1;
            strArrayCurr = strArrayHead;
            i ++;
            continue;
        }
        else
            strArrayTmp = createDupString(i, i);
        
        if(strArrayTmp == NULL){
            printf("Fail to allocate memory\n");
            freeDupString(strArrayHead);
            break;
        }
        strArrayTmp->allSame = 1;
        strArrayCurr->next = strArrayTmp;
        strArrayCurr = strArrayTmp;
        i ++;
    }
    return strArrayHead;
}

void findDupString(char* in)
{
    if(in == NULL){
        return;
    }
    
    int len = strlen(in);
    if(len <= 0){
        return;
    }

    if(len <= 1){
        printf("%s\n",in);
        return;
    }
    
    dupString* strHead;
    strHead = initDupString(in);
    int change = 0;
    dupString* strTmp;
    
    do {
        change = 0;
        strTmp = strHead;
        while(strTmp){
            int changeItem = 0;
            while(strTmp->start-1>=0 || strTmp->end+1<len){
                changeItem = 0;
                if(strTmp->allSame == 1 && strTmp->start-1>=0 && in[strTmp->start-1] == in[strTmp->start]){
                    strTmp->start -= 1;
                    strTmp->len += 1;
                    changeItem = 1;
                    change = 1;
                }else if(strTmp->allSame == 1 && strTmp->end+1<len && in[strTmp->end+1] == in[strTmp->start]){
                    strTmp->end += 1;
                    strTmp->len += 1;
                    changeItem = 1;
                    change = 1;
                }else if(strTmp->start-1>=0 && strTmp->end+1<len && in[strTmp->start-1] == in[strTmp->end+1]){
                    strTmp->start -= 1;
                    strTmp->end += 1;
                    strTmp->len += 2;
                    changeItem = 1;
                    strTmp->allSame = 0;
                    change = 1;
                }
                
                if(!changeItem)
                    break;
            }
           
            if(!changeItem){
                while(strTmp->next && strTmp->start<=strTmp->next->start && strTmp->end>=strTmp->next->end){
                    dupString* nextRange = strTmp->next;
                    strTmp->next = nextRange->next;
                    free(nextRange);
                }
                strTmp = strTmp->next;
            }
        }
    } while(change); 
    
    strTmp = strHead;
    while(strTmp){
        if(strTmp->len > 1){
            int i;
            for(i=strTmp->start;i<=strTmp->end;i++){
                printf("%c", in[i]);
            }
            printf("\n");
        }
        strTmp = strTmp->next;
    }
    
    freeDupString(strHead);
    return;
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
    
    findDupString(buff);
}

