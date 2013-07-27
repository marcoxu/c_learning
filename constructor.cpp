/*
 * 该例演示C++类构造函数用法
 *   构造子类时会先构造父类，析构子类时会先析构子类再析构父类，类似栈
 *   注意：析构函数中不能抛出异常
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Base {
public:
	void id() {
    printf("Base id 1\n");
	}
	Base() {
		printf("Create Base\n");
	}
	~Base() {
		printf("Delete Base\n");
	}
	
	Base(const Base& b) {
		printf("Copy Base\n");
	}
};

class D : public Base {
public:
	void id() {
    printf("D id 1\n");
	}
	D() {
		printf("Create D\n");
	}
	~D() {
		printf("Delete D\n");
	}
	
	D(const D& d) {
		printf("Copy D\n");
	}
};

void foo(Base b) {
    printf("foo\n");
    b.id();
}
void bar(Base &b) {
    printf("bar\n");
    b.id();
}

int main()
{
    D d;
    D& f = d; // f为引用，必须初始化
    //D& g = NULL; // f为引用，不能为空
    // create Base (构造d)
    // create D (构造d)
    Base *pb = new D();
    // create Base (构造pb)
    // create D (构造pb)

    foo(d); // foo参数为类实例，此处调用拷贝构造对传入的d拷贝到栈上, 输出应为Base id，因为id不是虚函数，栈上的
            // d在行数返回是被析构
    // copy Base
    // foo
    // Base id 1
    // delete Base
    bar(d); // bar参数为类引用，此处在栈上保存d的引用，不需要拷贝, 输出应为Base id，因为id不是虚函数，函数返回时
            // 不析构引用
    // bar
    // Base id 1

    // delete D (析构d)
    // delete Base (析构d)
    // pb没有析构，pb在堆上, 此处不析构，内存泄露。 d在栈上，自动析构
    return 0;
}