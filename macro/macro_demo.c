/*
 * C���Ժ���÷�
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h> //��������
#include <float.h>  //����������

#define TEST(variable) {printf("%s%s is %d, %s is %d\n", "test_", #variable, test_##variable, #variable, variable);}
int main()
{
    int test_v = 100;
    int test_test_v = 100;
    TEST(test_v);
    return 0;
}