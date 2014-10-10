#ifndef SMART_PTR_H
#define SMART_PTR_H

template<typename T>
class smart_ptr {
private:
  class object_ptr {
    public:
      object_ptr(T* obj);
      ~object_ptr() {delete optr;};
      T* getPtr();
      unsigned int refCount;
      T* optr;
  };
  object_ptr* obj;
  unsigned int incrCnt();
  unsigned int descCnt();
  unsigned int getCnt();

public:
  smart_ptr(smart_ptr& other);
  smart_ptr();
  smart_ptr(T* newObj);
  ~smart_ptr();
  smart_ptr& operator = (const smart_ptr& other);
  T* getPtr();
};

#endif
