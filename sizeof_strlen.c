/*
 * 该例说明sizeof和strlen的用法
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

    size = sizeof (s1);      // s1为字符串指针， 指针的size在32位机上为4,64位机上为8
    printf("size is %d\n", size);
    size = sizeof (s2);      // s2为字符串数组， 数组的size为其真实内容的大小，此处为6，因为s2以'\0'结尾
    printf("size is %d\n", size);
    size = sizeof (s3);      // s3为字符串数组， 数组的size为其真实内容的大小，此处为5，因为s3以'e'结尾
    printf("size is %d\n", size);
    size = strlen (s2);      // s2为字符串数组， strlen计算到‘\0'的长度之前，此处为5
    printf("size is %d\n", size);
    size = strlen (s3);      // s3为字符串数组， strlen计算到‘\0'的长度之前，而s3不以'\0'结尾，因此此处值随机
    printf("size is %d\n", size);
    size = sizeof (j/i);     // sizeof计算类型所占内存的大小，此处j/i并不进行计算，因此除0并不crash，j/i为整型，因此
                            // 此处值为4
    printf("size is %d\n", size);
    return 0;
}