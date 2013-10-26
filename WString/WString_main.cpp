/*
 * WString ÓÃ·¨ÊµÀı
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "WString.h"

int main()
{
    // WString constructor
    WString test_str_0 = "Test 0";
    WString* test_str_1 = new WString("Test 1");
    WString test_str_2("Test 2");
    
    // Copy contstructor
    WString test_str_3 = test_str_0;
    
    // Operator =
    test_str_3 = *test_str_1;
    printf("test_str_3: %s\n", test_str_3.get());
    test_str_3 = "Test 3";
    printf("test_str_3: %s\n", test_str_3.get());

    // Operator +
    test_str_3 = test_str_3 + test_str_0;
    printf("test_str_3: %s\n", test_str_3.get());
        
    // End
    delete test_str_1;
}