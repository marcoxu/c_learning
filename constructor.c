/*
 * ������ʾC++�๹�캯���÷�
 *   ((n & (n-1)) == 0) �÷�������͵�Ϊ1λ���㣬�磺
 *   0001  => 0000
 *   1000  => 0000
 *   1011  => 1010
 *   1010  => 1000
 *   1000  => 0000
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Base {
};

class D : public Base {
};

int main()
{
    D d;
    Base *pb = new D();

    printf("n1 is ");
    print_int_bit(n1, sizeof(int));
    printf("n1x is ");
    print_int_bit(n1x, sizeof(int));
    printf("n2 is ");
    print_int_bit(n2, sizeof(int));
    printf("n2x is ");
    print_int_bit(n2x, sizeof(int));
    return 0;
}