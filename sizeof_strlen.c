/*
 * ����˵��sizeof��strlen���÷�
 *   char * s1 = "abcde";
 *   char s2[] = "abcde";
 *   char s3[] = { 'a', 'b', 'c', 'd', 'e' }; // no terminator
 *   int j = strlen(s1);
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char * s1 = "abcde";
    char s2[] = "abcde";
    char s3[] = { 'a', 'b', 'c', 'd', 'e' }; // no terminator
    int i = 0;
    int j = strlen(s1);
    int size = 0;

    size = sizeof (s1);      // s1Ϊ�ַ���ָ�룬 ָ���size��32λ����Ϊ4,64λ����Ϊ8
    printf("size is %d\n", size);
    size = sizeof (s2);      // s2Ϊ�ַ������飬 �����sizeΪ����ʵ���ݵĴ�С���˴�Ϊ6����Ϊs2��'\0'��β
    printf("size is %d\n", size);
    size = sizeof (s3);      // s3Ϊ�ַ������飬 �����sizeΪ����ʵ���ݵĴ�С���˴�Ϊ5����Ϊs3��'e'��β
    printf("size is %d\n", size);
    size = strlen (s2);      // s2Ϊ�ַ������飬 strlen���㵽��\0'�ĳ���֮ǰ���˴�Ϊ5
    printf("size is %d\n", size);
    size = strlen (s3);      // s3Ϊ�ַ������飬 strlen���㵽��\0'�ĳ���֮ǰ����s3����'\0'��β����˴˴�ֵ���
    printf("size is %d\n", size);
    size = sizeof (j/i);     // sizeof����������ռ�ڴ�Ĵ�С���˴�j/i�������м��㣬��˳�0����crash��j/iΪ���ͣ����
                            // �˴�ֵΪ4
    printf("size is %d\n", size);
    return 0;
}