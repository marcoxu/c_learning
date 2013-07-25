/*
 * 本例测试const修饰的指针的访问权限
 *   const int * i1; i1为指针，其指向的内容为const int，因此i1指针可以修改，其指向的内容不能修改。
 *   int const * i2; 同i1
 *   int * const i3; i3为const，其类型为整型指针，因此i3指针不可修改，其指向的内容可以修改, 因此i3必须初始化。
 *   const int const * const i4; i4为const，其类型为整型指针，因此i4指针不可修改，其指向的内容也不可修改,
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

    i1 = &i5; // i1可修改
    //*i1 = 7;  // i1的内容不能修改
    
    i2 = &i5; // i2可修改
    //*i2 = 7;  // i2的内容不能修改
    
    //i3 = &i5; // i3不可修改
    *i3 = 8;  // i3的内容能修改
    
    //i4 = &i5; // i4不可修改
    //*i4 = 9;  // i4的内容不能修改

    printf("i1 is %d %p\n", *i1, i1);
    printf("i2 is %d %p\n", *i2, i2);
    printf("i3 is %d %p\n", *i3, i3);
    printf("i4 is %d %p\n", *i4, i4);
    printf("i5 is %d %p\n", i5, &i5);
    return 0;
}