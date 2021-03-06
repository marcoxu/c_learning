#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "smartptr.h"

template<typename T>
smart_ptr<T>::object_ptr::object_ptr(T* obj): refCount(1), optr(obj) {
  printf("object_ptr<T>::object_ptr(T* obj)\n");
}

template<typename T>
unsigned int smart_ptr<T>::incrCnt() {
  if(obj == NULL) {
    return 0;
  }

  obj->refCount ++; 
  printf("object_ptr<T>::incrCnt() = %u\n", obj->refCount);
  return obj->refCount;
}

template<typename T>
unsigned int smart_ptr<T>::descCnt() {
  if(obj == NULL) {
    return 0;
  }

  obj->refCount --;
  printf("object_ptr<T>::descCnt() = %u\n", obj->refCount);
  return obj->refCount;
}

template<typename T>
unsigned int smart_ptr<T>::getCnt() {
  if(obj == NULL) {
    return 0;
  }

  printf("object_ptr<T>::getCnt()\n");
  return obj->refCount;
}

template<typename T>
T* smart_ptr<T>::object_ptr::getPtr() {
  printf("object_ptr<T>::getPtr()\n");
  return optr;
}

template<typename T>
smart_ptr<T>::smart_ptr(smart_ptr& other): obj(other.obj) {
  printf("smart_ptr<T>::smart_ptr(smart_ptr& other)\n");
  other.incrCnt();
}

template<typename T>
smart_ptr<T>::smart_ptr(T* newObj): obj(new smart_ptr<T>::object_ptr(newObj)) {
  printf("smart_ptr<T>::smart_ptr(T* newObj)\n");
}


template<typename T>
smart_ptr<T>::smart_ptr(): obj(NULL) {
  printf("smart_ptr<T>::smart_ptr()\n");
}

template<typename T>
T* smart_ptr<T>::getPtr() {
  return this->obj?this->obj->getPtr():NULL;
}

template<typename T>
smart_ptr<T>::~smart_ptr() {
  printf("smart_ptr<T>::~smart_ptr()\n");
  if(obj != NULL && this->descCnt() == 0) {
    printf("smart_ptr<T>::~smart_ptr(): delete obj\n");
    delete obj;
  }
}

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator = (const smart_ptr<T>& other) {
  printf("smart_ptr<T>::operator =()\n");
  if(this->obj && this->descCnt() == 0) {
    delete obj;
  }
  
  this->obj = other.obj;
  this->incrCnt();
  return *this;
}

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
