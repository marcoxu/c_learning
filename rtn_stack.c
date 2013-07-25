/*
 * 1. 函数hexfmt返回的栈的内存地址，但函数返回时栈已经释放
 * 2. val >> 4 并不改变val的值
 * 3. 转换的16进制数为倒序
 */
#include <stdlib.h>
#include <stdio.h>

//char* hexfmt(int val)
//{
//    char s[(2 * sizeof(int)) + 1];
//    char* p = s;
//    size_t i = 0;
//    char nibble;
//    while (i++ < (2 * sizeof(int)))
//    {
//        nibble = val & 0x0F;
//        *p++ = nibble <= 9 ? nibble + '0' : nibble + 'a' - 10;
//        val >> 4;
//    }
//    *p = '\0';
//    return s;
//}

char* hexfmt(int val)
{
    char s[(2 * sizeof(int)) + 1];
    char* q = (char*)malloc((2 * sizeof(int)) + 1);//char* p = s;
    char* p = q + 2 * sizeof(int) - 1;
    size_t i = 0;
    char nibble;
    while (i++ < (2 * sizeof(int)))
    {
        nibble = val & 0x0F;
        printf("hexfmt: %d > %d\n", val, nibble);
        *p-- = nibble <= 9 ? nibble + '0' : nibble + 'a' - 10;
        val = val >> 4; //val >> 4
    }
    *(q + 2 * sizeof(int)) = '\0';
    return q; //return s;
}

int main()
{
    int c = 33;
    char* hexStr = hexfmt(c);
    printf("C is %s\n", hexStr);
    return 0;
}