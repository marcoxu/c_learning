/*
 * ������ʾC++��̳е��÷�
 *   public�̳У������public������public��protect������protect��private������private�����������ֻ�ܷ���public��protecteed
 *   protect�̳У������public��protect������protect��private������private, ���������ֻ�ܷ���public��protecteed
 *   private�̳У������public��protect��private�����඼Ϊprivate, ��������಻�ܷ���
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Base {
public:
	int baseIdPub;
	void id() {
    printf("Base public id %d\n", baseIdPub);
    printf("Base protected id %d\n", baseIdPro);
    printf("Base private id %d\n", baseIdPri);
	}
	Base() {
		printf("Create Base\n");
		baseIdPub = 0;
		baseIdPro = 1;
		baseIdPri = 2;
	}
	~Base() {
		printf("Delete Base\n");
	}
	
	Base(const Base& b) {
		printf("Copy Base\n");
	}
protected:
	int baseIdPro;
private:
	int baseIdPri;
};

class D1 : public Base {
public:
	void id() {
    printf("D1 public id %d\n", baseIdPub);
    printf("D1 protected id %d\n", baseIdPro);
    //printf("D1 private id %d\n", baseIdPri);
	}
	D1() {
		printf("Create D1\n");
	}
	~D1() {
		printf("Delete D1\n");
	}
	
	D1(const D1& d) {
		printf("Copy D1\n");
	}
};

class D2 : protected Base {
public:
	void id() {
    printf("D2 public id %d\n", baseIdPub);
    printf("D2 protected id %d\n", baseIdPro);
    //printf("D2 private id %d\n", baseIdPri);
	}
	D2() {
		printf("Create D2\n");
	}
	~D2() {
		printf("Delete D2\n");
	}
	
	D2(const D2& d) {
		printf("Copy D2\n");
	}
};

class D3 : private Base {
public:
	void id() {
    printf("D3 public id %d\n", baseIdPub);
    printf("D3 protected id %d\n", baseIdPro);
    //printf("D3 private id %d\n", baseIdPri);
	}
	D3() {
		printf("Create D3\n");
	}
	~D3() {
		printf("Delete D3\n");
	}
	
	D3(const D3& d) {
		printf("Copy D3\n");
	}
};

class D4 : public D3 {
public:
	void id() {
    //printf("D4 public id %d\n", baseIdPub); // ���г�Ա��D3����˽�У�D4���ܷ���
    //printf("D4 protected id %d\n", baseIdPro);
    //printf("D4 private id %d\n", baseIdPri);
	}
	D4() {
		printf("Create D4\n");
	}
	~D4() {
		printf("Delete D4\n");
	}
	
	D4(const D4& d) {
		printf("Copy D4\n");
	}
};

class D5 : public D1 {
public:
	void id() {
    printf("D5 public id %d\n", baseIdPub); // baseIdPub��D1�ǹ��У�D5���Է���
    printf("D5 protected id %d\n", baseIdPro); // baseIdPro��D1���ܱ�����D5���Է���
    //printf("D5 private id %d\n", baseIdPri); // baseIdPri��D1��˽�У�D5�����Է���
	}
	D5() {
		printf("Create D5\n");
	}
	~D5() {
		printf("Delete D5\n");
	}
	
	D5(const D5& d) {
		printf("Copy D5\n");
	}
};

int main()
{
	  Base B;
	  D1 d1;
	  D2 d2;
	  D3 d3;
	  D4 d4;
	  D5 d5;
	  
	  Base* bx;
	  D1* d1x = new D1();
	  D2* d2x = new D2();
	  D3* d3x = new D3();
	  
	  B.id();
	  d1.id();
	  d2.id();
	  d3.id();
	  d4.id();
	  d5.id();
	  
	  bx = d1x; // ����ת��
	  //bx = d2x; // ������ת������Ա����Ȩ�޲��ܸı�
	  //bx = d3x; // ������ת������Ա����Ȩ�޲��ܸı�
    return 0;
}