/*
 * 未初始化的指针指向位置的内存地址，写该地址
 * 对系统可能造成未知的影响
 */
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int c = 33;
    int * x;

    *x = c;
    printf("x is %d %p\n", *x, x);
    return 0;
}