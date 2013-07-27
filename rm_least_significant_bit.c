/*
 * 该例演示删除least significant bit的方法
 *   ((n & (n-1)) == 0) 该方法将最低的为1位清零，如：
 *   0001  => 0000
 *   1000  => 0000
 *   1011  => 1010
 *   1010  => 1000
 *   1000  => 0000
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CLEAR_LEAST_SIG(n) ((n & (n-1)))

void print_int_bit(int num, unsigned int size)
{
     unsigned int length = 4 * sizeof(num);
     unsigned int index = (1 << (length - 1));
     if ( (length > size) && (size > 0) ) {
          index = (1 << (size - 1));
     }
     while ( index > 0 ) {
          putchar((num & index) ? '1' : '0');
          index >>= 1;
     }
     
     printf("\n");
}

int main()
{
    int n1 = 0x8;
    int n2 = 0xb;
    int n1x = CLEAR_LEAST_SIG(n1);
    int n2x = CLEAR_LEAST_SIG(n2);

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