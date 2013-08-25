/*
 * 整型与字符串转换
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h> //整数限制
#include <float.h>  //浮点数限制

#define HEX_TO_CHAR(x,c) {if(0 <= (x) && (x) <= 9) (c)='0'+(x)-0; \
	                        else if (0xa <= (x) && (x) <= 0xf) (c)='A'+(x)-0xa;}

#define CHAR_TO_HEX(c,x) {if('0' <= (c) && (c) <= '9') (x)=0+(c)-'0'; \
	                        else if ('a' <= (x) && (x) <= 'f') (x)=0xa+(c)-'a'; \ 
	                        else if ('A' <= (x) && (x) <= 'F') (x)=0xa+(c)-'A'; }
	                        	
void itoh(char* buf, int hex)
{
    if(buf == NULL)
    	return;
    	
    int pos = 0;
    int tempHex = hex;
    int size = sizeof(int);
    int start = 0;
    
    // check the sign
    if(hex < 0)
    {
    	buf[pos++] = '-';
    	tempHex = ~hex + 1;
    }
    buf[pos++] = '0';
    buf[pos++] = 'x';
    
    for(start = 0; start < size; start ++)
    {
    	 char tmp;
    	 tmp = (tempHex >> (size-start-1)*8) & 0xff;
       printf("tmp 0x%02x\n", tmp);
    	 HEX_TO_CHAR(tmp>>4, buf[pos]);
    	 pos ++;
    	 HEX_TO_CHAR(tmp&0xff, buf[pos]);
    	 pos ++;
    }
    return;
}

void htoi(char* buf, int* hex)
{
    if(buf == NULL)
    	return;
    	
    int minus = 0;
    int tempHex = 0;
    int size = strlen(buf);
    int start = 0;

    printf("buf length %d\n", size);
    if(buf[start] == '-')
    {
       minus = 1;
       start ++;
    }
    if(buf[start] == '0' && (buf[start+1] == 'x' || buf[start+1] == 'X'))
    {
       start += 2;
    }
    
    for(; start < size; start ++, tempHex << 4)
    {
    	 char tmp;
       printf("buf[start] 0x%c\n", buf[start]);
    	 CHAR_TO_HEX(buf[start], tmp);
    	 tempHex += tmp;
    }
    if(minus)
    	tempHex *= -1;
    	
    *hex = tempHex;
    return;
}

int main()
{
    int test_v = 1;
    int test_v2 = 0;
    char buf[100] = {0};
    itoh(buf, test_v);
    printf("test_v is 0x%08x, %s\n", test_v, buf);
    htoi(buf, &test_v2);
    printf("test_v2 is 0x%08x, %s\n", test_v2, buf);
    return 0;
}