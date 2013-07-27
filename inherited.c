/*
 * 该例演示C++类继承的用法
 *   public继承：父类的public对子类public，protect对子类protect，private对子类private，子类的子类只能访问public和protecteed
 *   protect继承：父类的public和protect对子类protect，private对子类private, 子类的子类只能访问public和protecteed
 *   private继承：父类的public和protect，private对子类都为private, 子类的子类不能访问
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
    //printf("D4 public id %d\n", baseIdPub); // 所有成员在D3都是私有，D4不能访问
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
    printf("D5 public id %d\n", baseIdPub); // baseIdPub在D1是公有，D5可以访问
    printf("D5 protected id %d\n", baseIdPro); // baseIdPro在D1是受保护，D5可以访问
    //printf("D5 private id %d\n", baseIdPri); // baseIdPri在D1是私有，D5不可以访问
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
	  
	  bx = d1x; // 可以转换
	  //bx = d2x; // 不可以转换，成员访问权限不能改变
	  //bx = d3x; // 不可以转换，成员访问权限不能改变
    return 0;
}