/*
 * ������ʾC++�๹�캯���÷�
 *   ��������ʱ���ȹ��츸�࣬��������ʱ���������������������࣬����ջ
 *   ע�⣺���������в����׳��쳣
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
    D& f = d; // fΪ���ã������ʼ��
    //D& g = NULL; // fΪ���ã�����Ϊ��
    // create Base (����d)
    // create D (����d)
    Base *pb = new D();
    // create Base (����pb)
    // create D (����pb)

    foo(d); // foo����Ϊ��ʵ�����˴����ÿ�������Դ����d������ջ��, ���ӦΪBase id����Ϊid�����麯����ջ�ϵ�
            // d�����������Ǳ�����
    // copy Base
    // foo
    // Base id 1
    // delete Base
    bar(d); // bar����Ϊ�����ã��˴���ջ�ϱ���d�����ã�����Ҫ����, ���ӦΪBase id����Ϊid�����麯������������ʱ
            // ����������
    // bar
    // Base id 1

    // delete D (����d)
    // delete Base (����d)
    // pbû��������pb�ڶ���, �˴����������ڴ�й¶�� d��ջ�ϣ��Զ�����
    return 0;
}