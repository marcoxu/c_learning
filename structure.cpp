/*
 * 该例演示C++类构造函数用法
 *   构造子类时会先构造父类，析构子类时会先析构子类再析构父类，类似栈
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct foo {
    foo(){                           // A
       printf("foo()\n");
    }
    foo(int) {                       // B
       printf("foo(int)\n");
    }
    foo(const foo &){                // C
       printf("foo(const foo &)\n");
    }
    foo & operator= (foo & f){         // D
       printf("operator= (foo &)\n");
    }
};

class foo1
{
private:
	  int k;
    ~foo1() {
    	printf("delete foo1\n");
    }
public:
    foo1(){
    	k = 0;
    	printf("create foo1\n");
    }
    
    void stuff(int i) const {
    	//k = i;  const函数不能修改类的成员，只能调用const函数
    	stuff1();
    }
    
    void stuff1() const {
    	//k = 2;
    }
    
    void release() {
       this->~foo1();
    }
};

void funct() {
    int i;
    char c = 10;
    foo a1;                         // 默认构造函数 foo()
    foo a2(i);                      // i为整数，调用foo(int)
    foo a3(c);                      // c为字符，不存在foo(char), 隐式转换为int，调用foo(int)
    foo a4(a2);                     // a2为foo类型，调用拷贝构造 
    foo a5 = a2;                    // a5还未构造，调用拷贝构造
    a1 = a4;                        // 调用=运算符
}

int main()
{
	  //foo1 f1; // foo1的析构函数为私有，因此不能被隐式调用，f1不能存在栈上，只能在堆上，通过封装的删除函数release析构
    foo1* f1 = new foo1();
    f1->release();
    funct();
    return 0;
}