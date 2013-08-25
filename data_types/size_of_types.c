/*
 * 计算各种数据类型的大小和取值范围
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h> //整数限制
#include <float.h>  //浮点数限制
 
int main()
{
    int            a = ~0;
    unsigned int   b = ~0;
    unsigned       k = ~0;
    short          c = ~0;
    unsigned short d = ~0;
    long           e = ~0;
    unsigned long  f = ~0;
    long long      l = ~0;
    char           j = ~0;
    float          g = ~0;
    double         h = ~0;
    long double    i = ~0;
    
    char x = 127;
    char y = -128;
    printf(" 127 & -128 = 0x%x\n", x&y);
    printf(" 127 ^ -128 = 0x%x\n", x^y);
    printf(" 127 | -128 = 0x%x\n", x|y);
    
    // Integer
    printf("         Integer: size = %d,  range [%d ~ %d]\n", (int)sizeof(int), (int)(~((unsigned int)a >> 1)), (int)((unsigned int)a >> 1));
    // Unsigned Integer
    printf("unsigned Integer: size = %d,  range [%u ~ %u]\n", (int)sizeof(unsigned int), 0, b);
    // Unsigned
    printf("        unsigned: size = %d,  range [%u ~ %u]\n", (int)sizeof(unsigned), 0, k);
    // short
    printf("           short: size = %d,  range [%d ~ %d]\n", (int)sizeof(c), (int)(~((unsigned short)c >> 1)), (int)((unsigned short)c >> 1));
    // Unsigned short
    printf("  unsigned short: size = %d,  range [%d ~ %d]\n", (int)sizeof(d), 0, d);
    // long
    printf("            long: size = %d,  range [%ld ~ %ld]\n", (int)sizeof(e), (long)(~((unsigned long)e >> 1)), (long)((unsigned long)e >> 1));
    // unsigned long
    printf("   unsigned long: size = %d,  range [%d ~ %lu]\n", (int)sizeof(f), 0, f);
    // long long
    printf("       long long: size = %d,  range [%lld ~ %lld]\n", (int)sizeof(l), (long long)(~((unsigned long long)l >> 1)), (long long)((unsigned long long)l >> 1));
    // Char
    printf("            char: size = %d,  range [%d ~ %d]\n", (int)sizeof(j), (int)(~((unsigned char)j >> 1)), (int)((unsigned char)j >> 1));
    // float
    printf("           float: size = %d,  range [%e ~ %e]\n", (int)sizeof(g), (float)(~((unsigned int)g >> 1)), (float)((unsigned int)g >> 1));
    printf("           float: size = %d,  range [%e ~ %e]\n", (int)sizeof(g), FLT_MIN, FLT_MAX);
    // double
    printf("          double: size = %d,  range [%e ~ %e]\n", (int)sizeof(h), (double)(~((unsigned long)h >> 1)), (double)((unsigned long)h >> 1));
    printf("          double: size = %d,  range [%e ~ %e]\n", (int)sizeof(h), DBL_MIN, DBL_MAX);
    // long double
    int ld_size = sizeof(i) * 8;
    unsigned long max  = 1 << (ld_size - 1);
    unsigned long least_sig = ~max;
    long double max_long_double = 0;
    long double min_long_double = 0;
    unsigned long * max_least  = (unsigned long *)&max_long_double;
    unsigned long * max_most   = (unsigned long *)((char *)&max_long_double+4);
    unsigned long * min_least  = (unsigned long *)&min_long_double;
    unsigned long * min_most   = (unsigned long *)((char *)&min_long_double+4);
    memset(max_most, max, sizeof(max));
    memset(max_least, 0, sizeof(max));
    memset(min_most, least_sig, sizeof(least_sig));
    memset(min_least, 0xff, sizeof(least_sig));
    printf("     long double: size = %d, range [%Lf ~ %Lf]\n", (int)sizeof(i), max_long_double, min_long_double);
    return 0;
}