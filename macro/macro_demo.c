/*
 * C语言宏的用法
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h> //整数限制
#include <float.h>  //浮点数限制

#define TEST(variable) {printf("%s%s is %d, %s is %d\n", "test_", #variable, test_##variable, #variable, variable);}
int main()
{
    int test_v = 100;
    int test_test_v = 100;
    TEST(test_v);
    return 0;
}