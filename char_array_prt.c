/*
 * 本例测试字符串和字符数组修改权限
 * char *s1        = "abc";  s1指向数据段字符串“abc", s1可以修改，但"abc"字符串的内容不能修改
 * const char * s2 = "def";  s2为字符串指针，其内容"def"在数据段，不可修改，s2指针本身可以修改
 * char * const s3 = "xyz";  s3指针为常量，不可修改，其指向的内容可以修改。”xyz"存在数据段，修改将crash
 * char  s4[]      = "abcdef"; s4为字符数组，数组长度为7, s4内容可修改，s4作为指针不能修改
 
 * s1,s2指针可以修改
 * s4内容可修改，s1,s3内容页可修改，但会造成程序crash
 */
#include <stdlib.h>
#include <stdio.h>

char *s1        = "abc";
const char * s2 = "def";
char * const s3 = "xyz";
char  s4[]      = "abcdef";
char  s5[]      = "fegeagss";
char  s6[]      = "fegeag";

char * foobar(char * s)
{
    *s = '\0';
    s[1] = '1';
    s[2] = '2';
    s[3] = '3';
    return s;
}

int main()
{
    //s1[0] = 'd'; //编译器不报错误，但修改数据段内容, 程序将crash
    s1 = (char*)s2; // s1指针可以修改

    //s2[0] = 'g'; //s2指向常量字符串，不能修改其内容, 编译错误
    s2 = (const char*)s3; // s2指针可以修改

    //s3[0] = 'e'; //s3为常量指针，指向字符串，不能修改指针指向，但可以修改内容。
    //s3 = (char* const)s4; // s3指针不可以修改
    
    s4[5]='x'; //内容可修改，数组存在数据段，修改将导致程序crash
    //s4 = s3; // 不可修改，类型不匹配
    //s4 = s5; // 不可修改，数组长度不匹配
    //s4 = s6;

    char* s7 = foobar((char*)s4);
    printf("s1 is %s %p\n", s1, s1);
    printf("s2 is %s %p\n", s2, s2);
    printf("s3 is %s %p\n", s3, s3);
    printf("s4 is %s %p\n", s4, s4);
    printf("s7 is %s %p\n", s7, s7);
    return 0;
}