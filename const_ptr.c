/*
 * ��������const���ε�ָ��ķ���Ȩ��
 *   const int * i1; i1Ϊָ�룬��ָ�������Ϊconst int�����i1ָ������޸ģ���ָ������ݲ����޸ġ�
 *   int const * i2; ͬi1
 *   int * const i3; i3Ϊconst��������Ϊ����ָ�룬���i3ָ�벻���޸ģ���ָ������ݿ����޸�, ���i3�����ʼ����
 *   const int const * const i4; i4Ϊconst��������Ϊ����ָ�룬���i4ָ�벻���޸ģ���ָ�������Ҳ�����޸�,
 */
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i5 = 6;
    const int * i1;
    int const * i2 = &i5;
    int * const i3 = &i5;
    const int const * const i4 = &i5;

    i1 = &i5; // i1���޸�
    //*i1 = 7;  // i1�����ݲ����޸�
    
    i2 = &i5; // i2���޸�
    //*i2 = 7;  // i2�����ݲ����޸�
    
    //i3 = &i5; // i3�����޸�
    *i3 = 8;  // i3���������޸�
    
    //i4 = &i5; // i4�����޸�
    //*i4 = 9;  // i4�����ݲ����޸�

    printf("i1 is %d %p\n", *i1, i1);
    printf("i2 is %d %p\n", *i2, i2);
    printf("i3 is %d %p\n", *i3, i3);
    printf("i4 is %d %p\n", *i4, i4);
    printf("i5 is %d %p\n", i5, &i5);
    return 0;
}