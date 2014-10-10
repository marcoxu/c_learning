#include <stdlib.h>
#include <stdio.h>
#include "smartptr.h"

class testClass {
public:
  int a;
  char b;
  long c;
  void doTest() {printf("testClass.doTest()\n");};
  ~testClass() {printf("delete testClass with a = %d\n", a);};
};

int main() {
  smart_ptr<int> p1;

  testClass* test1 = new testClass();
  test1->a = 10;
  smart_ptr<testClass> p2;
  smart_ptr<testClass> p3(test1);
  smart_ptr<testClass> p4 = p3;
  smart_ptr<testClass> p5 = p3;

  testClass* ptr = p3.getPtr();
  if(ptr) {
    ptr->doTest();
  }
}
