/*
 * ����˵���ַ�������ַ���ָ�������
 *   char * s1 = "abcde"; s1���ַ���ָ�룬ָ�򱣴������ݶε��ַ�����s1�����޸ģ��޸����ݶ��ַ���"abcde"�����crash
 *   char s2[] = "abcde"; s2���ַ������飬s2�����ݿ����޸ģ�s2������ԱΪ��\0��
 *   char s3[] = { 'a', 'b', 'c', 'd', 'e' }; s3���ַ������飬s3�����ݿ����޸�, s2������ԱΪ��e��
 */
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char * s1 = "abcde";
    char s2[] = "abcde";
    char s3[] = { 'a', 'b', 'c', 'd', 'e' };

    //s1[1] = 'c'; // crash
    s1 = "xyz";
    printf("s1 is %s %p\n", s1, s1);
    
    s2[2] = 'v';
    printf("s2 is %s %p\n", s2, s2);

    s3[2] = 'v';
    printf("s3 is %s %p\n", s3, s3);
    return 0;
}