/*
 * δ��ʼ����ָ��ָ��λ�õ��ڴ��ַ��д�õ�ַ
 * ��ϵͳ�������δ֪��Ӱ��
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