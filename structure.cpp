/*
 * ������ʾC++�๹�캯���÷�
 *   ��������ʱ���ȹ��츸�࣬��������ʱ���������������������࣬����ջ
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
    	//k = i;  const���������޸���ĳ�Ա��ֻ�ܵ���const����
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
    foo a1;                         // Ĭ�Ϲ��캯�� foo()
    foo a2(i);                      // iΪ����������foo(int)
    foo a3(c);                      // cΪ�ַ���������foo(char), ��ʽת��Ϊint������foo(int)
    foo a4(a2);                     // a2Ϊfoo���ͣ����ÿ������� 
    foo a5 = a2;                    // a5��δ���죬���ÿ�������
    a1 = a4;                        // ����=�����
}

int main()
{
	  //foo1 f1; // foo1����������Ϊ˽�У���˲��ܱ���ʽ���ã�f1���ܴ���ջ�ϣ�ֻ���ڶ��ϣ�ͨ����װ��ɾ������release����
    foo1* f1 = new foo1();
    f1->release();
    funct();
    return 0;
}