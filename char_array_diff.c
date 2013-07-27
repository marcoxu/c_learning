/*
 * 该例说明字符数组和字符串指针的区别
 *   char * s1 = "abcde"; s1是字符串指针，指向保存在数据段的字符串，s1可以修改，修改数据段字符串"abcde"将造成crash
 *   char s2[] = "abcde"; s2是字符串数组，s2的内容可以修改，s2的最后成员为‘\0’
 *   char s3[] = { 'a', 'b', 'c', 'd', 'e' }; s3是字符串数组，s3的内容可以修改, s2的最后成员为‘e’
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