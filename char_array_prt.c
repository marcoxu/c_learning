/*
 * ���������ַ������ַ������޸�Ȩ��
 * char *s1        = "abc";  s1ָ�����ݶ��ַ�����abc", s1�����޸ģ���"abc"�ַ��������ݲ����޸�
 * const char * s2 = "def";  s2Ϊ�ַ���ָ�룬������"def"�����ݶΣ������޸ģ�s2ָ�뱾������޸�
 * char * const s3 = "xyz";  s3ָ��Ϊ�����������޸ģ���ָ������ݿ����޸ġ���xyz"�������ݶΣ��޸Ľ�crash
 * char  s4[]      = "abcdef"; s4Ϊ�ַ����飬���鳤��Ϊ7, s4���ݿ��޸ģ�s4��Ϊָ�벻���޸�
 
 * s1,s2ָ������޸�
 * s4���ݿ��޸ģ�s1,s3����ҳ���޸ģ�������ɳ���crash
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
    //s1[0] = 'd'; //�������������󣬵��޸����ݶ�����, ����crash
    s1 = (char*)s2; // s1ָ������޸�

    //s2[0] = 'g'; //s2ָ�����ַ����������޸�������, �������
    s2 = (const char*)s3; // s2ָ������޸�

    //s3[0] = 'e'; //s3Ϊ����ָ�룬ָ���ַ����������޸�ָ��ָ�򣬵������޸����ݡ�
    //s3 = (char* const)s4; // s3ָ�벻�����޸�
    
    s4[5]='x'; //���ݿ��޸ģ�����������ݶΣ��޸Ľ����³���crash
    //s4 = s3; // �����޸ģ����Ͳ�ƥ��
    //s4 = s5; // �����޸ģ����鳤�Ȳ�ƥ��
    //s4 = s6;

    char* s7 = foobar((char*)s4);
    printf("s1 is %s %p\n", s1, s1);
    printf("s2 is %s %p\n", s2, s2);
    printf("s3 is %s %p\n", s3, s3);
    printf("s4 is %s %p\n", s4, s4);
    printf("s7 is %s %p\n", s7, s7);
    return 0;
}