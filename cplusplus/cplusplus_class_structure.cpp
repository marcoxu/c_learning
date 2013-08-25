/*
 * C++类在内存中的存储结构
 * 1. 单个类
 * 2. 单继承子类
 * 3. 多继承子类(Y型继承)
 * 4. 多继承子类(菱形继承)
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h> //整数限制
#include <float.h>  //浮点数限制

// 单个类
class singleClass {
public:
	virtual void single_func_a() {printf("singleClass::single_func_a()\n");}
	virtual void single_func_b() {printf("singleClass::single_func_b()\n");}
	void single_func_c() {printf("singleClass::single_func_c()\n");}
	singleClass():data_mem(10) {printf("singleClass::singleClass()\n");}
	~singleClass() {printf("singleClass::~singleClass()\n");}
private:
	void single_func_d() {printf("singleClass::single_func_d()\n");}
	int data_mem;
};

// 单继承子类
class singleParentClass {
public:
	virtual void single_parent_func_a() {printf("singleParentClass::single_parent_func_a()\n");}
	virtual void single_parent_func_b() {printf("singleParentClass::single_parent_func_b()\n");}
	void single_parent_func_c(int a);
	singleParentClass():data_parent(12) {printf("singleParentClass::singleParentClass()\n");}
	~singleParentClass() {printf("singleParentClass::~singleParentClass()\n");}
private:
	void single_parent_func_d();
	int data_parent;
};

class childClass: public singleParentClass {
public:
	virtual void single_parent_func_a() {printf("childClass::single_parent_func_a()\n");}
	virtual void single_parent_func_c() {printf("childClass::single_parent_func_c()\n");}
	void single_parent_func_c1(int a);
	childClass():data_child(100) {printf("childClass::childClass()\n");}
	~childClass() {printf("childClass::~childClass()\n");}
private:
	void single_parent_func_d1();
	int data_child;
};

// 多继承子类
class singleParentAClass {
public:
	virtual void single_parentA_func_a() {printf("singleParentAClass::single_parentA_func_a()\n");}
	virtual void single_parentA_func_b() {printf("singleParentAClass::single_parentA_func_b()\n");}
	virtual void single_parentA_func_c() {printf("singleParentAClass::single_parentA_func_c()\n");}
	virtual void single_parentA_func_d() {printf("singleParentAClass::single_parentA_func_d()\n");}
	void single_parentA_func_c(int a);
	singleParentAClass():data_parentA(115) {printf("singleParentAClass::singleParentAClass()\n");}
	~singleParentAClass() {printf("singleParentAClass::~singleParentAClass()\n");}
private:
	void single_parentA_func_e();
	int data_parentA;
};

class singleParentBClass {
public:
	virtual void single_parentB_func_a() {printf("singleParentBClass::single_parentB_func_a()\n");}
	virtual void single_parentB_func_b() {printf("singleParentBClass::single_parentB_func_b()\n");}
	virtual void single_parentB_func_c() {printf("singleParentBClass::single_parentB_func_c()\n");}
	void single_parentB_func_c(int a);
	singleParentBClass():data_parentB(112) {printf("singleParentBClass::singleParentBClass()\n");}
	~singleParentBClass() {printf("singleParentBClass::~singleParentBClass()\n");}
private:
	void single_parentB_func_d();
	int data_parentB;
};

class childClassAB: public singleParentAClass, public singleParentBClass {
public:
	virtual void single_parentA_func_a() {printf("childClassAB::single_parentA_func_a()\n");}
	virtual void single_parentB_func_b() {printf("childClassAB::single_parentB_func_b()\n");}
	virtual void single_parent_func_c() {printf("childClassAB::single_parent_func_c()\n");}
	void single_parent_func_c1(int a);
	childClassAB():data_child(100) {printf("childClassAB::childClassAB()\n");}
	~childClassAB() {printf("childClassAB::~childClassAB()\n");}
private:
	void single_parent_func_d1();
	int data_child;
};

// Y型多继承子类
class singleParentXClass {
public:
	virtual void single_parentX_func_a() {printf("singleParentXClass::single_parentX_func_a()\n");}
	virtual void single_parentX_func_b() {printf("singleParentXClass::single_parentX_func_b()\n");}
	virtual void single_parentX_func_c() {printf("singleParentXClass::single_parentX_func_c()\n");}
	virtual void single_parentX_func_d() {printf("singleParentXClass::single_parentX_func_d()\n");}
	void single_parentX_func_c(int a);
	singleParentXClass():data_parentX(115) {printf("singleParentXClass::singleParentXClass()\n");}
	~singleParentXClass() {printf("singleParentXClass::~singleParentXClass()\n");}
private:
	void single_parentX_func_e();
	int data_parentX;
};

class singleParentXAClass : public singleParentXClass {
public:
	virtual void single_parentX_func_a() {printf("singleParentXAClass::single_parentX_func_a()\n");}
	virtual void single_parentXA_func_a() {printf("singleParentXAClass::single_parentXA_func_a()\n");}
	virtual void single_parentX_func_c() {printf("singleParentXAClass::single_parentX_func_c()\n");}
	virtual void single_parentXA_func_b() {printf("singleParentXAClass::single_parentXA_func_b()\n");}
	void single_parentXA_func_c(int a);
	singleParentXAClass():data_parentXA(117) {printf("singleParentXAClass::singleParentXAClass()\n");}
	~singleParentXAClass() {printf("singleParentXAClass::~singleParentXAClass()\n");}
private:
	void single_parentXA_func_e();
	int data_parentXA;
};

class singleParentXBClass : public singleParentXClass {
public:
	virtual void single_parentXB_func_a() {printf("singleParentXBClass::single_parentXB_func_a()\n");}
	virtual void single_parentX_func_b() {printf("singleParentXBClass::single_parentX_func_b()\n");}
	virtual void single_parentXB_func_b() {printf("singleParentXBClass::single_parentXB_func_b()\n");}
	void single_parentXB_func_c(int a);
	singleParentXBClass():data_parentXB(119) {printf("singleParentXBClass::singleParentXBClass()\n");}
	~singleParentXBClass() {printf("singleParentXBClass::~singleParentXBClass()\n");}
private:
	void single_parentXB_func_d();
	int data_parentXB;
};

class childClassXAB: public singleParentXAClass, public singleParentXBClass {
public:
	virtual void single_parentX_func_a() {printf("childClassXAB::single_parentX_func_a()\n");}
	virtual void single_parentXA_func_a() {printf("childClassXAB::single_parentXA_func_a()\n");}
	virtual void single_parentXB_func_a() {printf("childClassXAB::single_parentXB_func_a()\n");}
	virtual void single_childClassXAB_func_x() {printf("childClassXAB::single_childClassXAB_func_x()\n");}
	childClassXAB():data_child(100) {printf("childClassXAB::childClassXAB()\n");}
	~childClassXAB() {printf("childClassXAB::~childClassXAB()\n");}
private:
	void single_parent_func_d1();
	int data_child;
};

// 菱形多继承子类 （虚继承）
class singleParentVXClass {
public:
	virtual void single_parentVX_func_a() {printf("singleParentVXClass::single_parentVX_func_a()\n");}
	virtual void single_parentVX_func_b() {printf("singleParentVXClass::single_parentVX_func_b()\n");}
	virtual void single_parentVX_func_c() {printf("singleParentVXClass::single_parentVX_func_c()\n");}
	virtual void single_parentVX_func_d() {printf("singleParentVXClass::single_parentVX_func_d()\n");}
	void single_parentVX_func_c(int a);
	singleParentVXClass():data_parentVX(0xab) {printf("singleParentVXClass::singleParentVXClass()\n");}
	~singleParentVXClass() {printf("singleParentVXClass::~singleParentVXClass()\n");}
private:
	void single_parentVX_func_e();
	int data_parentVX;
};

class singleParentVXAClass : virtual public singleParentVXClass {
public:
	virtual void single_parentVX_func_a() {printf("singleParentVXAClass::single_parentVX_func_a()\n");}
	virtual void single_parentVXA_func_a() {printf("singleParentVXAClass::single_parentVXA_func_a()\n");}
	virtual void single_parentVX_func_c() {printf("singleParentVXAClass::single_parentVX_func_c()\n");}
	virtual void single_parentVXA_func_b() {printf("singleParentVXAClass::single_parentVXA_func_b()\n");}
	void single_parentVXA_func_c(int a);
	singleParentVXAClass():data_parentVXA(117) {printf("singleParentVXAClass::singleParentVXAClass()\n");}
	~singleParentVXAClass() {printf("singleParentVXAClass::~singleParentVXAClass()\n");}
private:
	void single_parentXA_func_e();
	int data_parentVXA;
};

class singleParentVXBClass : virtual public singleParentVXClass {
public:
	virtual void single_parentVXB_func_a() {printf("singleParentVXBClass::single_parentVXB_func_a()\n");}
	virtual void single_parentVX_func_b() {printf("singleParentVXBClass::single_parentVX_func_b()\n");}
	virtual void single_parentVXB_func_b() {printf("singleParentVXBClass::single_parentVXB_func_b()\n");}
	void single_parentVXB_func_c(int a);
	singleParentVXBClass():data_parentVXB(119) {printf("singleParentVXBClass::singleParentVXBClass()\n");}
	~singleParentVXBClass() {printf("singleParentVXBClass::~singleParentVXBClass()\n");}
private:
	void single_parentVXB_func_d();
	int data_parentVXB;
};

class childClassVXAB: public singleParentVXAClass, public singleParentVXBClass {
public:
	virtual void single_parentVX_func_a() {printf("childClassVXAB::single_parentVX_func_a()\n");}
	virtual void single_parentVXA_func_a() {printf("childClassVXAB::single_parentVXA_func_a()\n");}
	virtual void single_parentVXB_func_a() {printf("childClassVXAB::single_parentVXB_func_a()\n");}
	virtual void single_childClassVXAB_func_x() {printf("childClassVXAB::single_childClassVXAB_func_x()\n");}
	childClassVXAB():data_childV(100) {printf("childClassVXAB::childClassVXAB()\n");}
	~childClassVXAB() {printf("childClassVXAB::~childClassVXAB()\n");}
private:
	void single_parent_func_d1();
	int data_childV;
};

typedef void(*Fun)(void);

int main()
{
    singleClass sigClass;
    childClass chldClass;
    childClassAB chldClassAB;
    childClassXAB chldClassXAB;
    childClassVXAB chldClassVXAB;
    Fun pFun = NULL;
    unsigned long** pVtab = (unsigned long**)&sigClass;

    // 单个类
    printf("\n=============================== singleClass ===============================\n");
    printf("vtable[0]: %p, %lu\n", &pVtab[0], sizeof(sigClass));
    for (int i=0; (Fun)pVtab[0][i]!=NULL, i<2; i++){
        pFun = (Fun)pVtab[0][i];
        //printf("vtable[0][%d]: %p -> %p ", i, &pVtab[0][i], (void *)pVtab[0][i]);
        printf("vtable[0][%d]", i);
        printf(" %p", &pVtab[0][i]);
        printf(" -> %p ", (void *)pVtab[0][i]);
        pFun();
        pFun = (Fun)pVtab[0][i+1];
        //printf("Call vtable[%d] done!\n", i);
    }
    
    printf("vtable[0] done!\n");
    printf("vtable[1]: %p -> singleClass:data_mem = %lu\n", &pVtab[1], (unsigned long)pVtab[1]);


    // 单继承子类
    pVtab = (unsigned long**)&chldClass;
    printf("\n=============================== childClass ===============================\n");
    printf("vtable[0]: %p\n", &pVtab[0]);
    for (int i=0; (Fun)pVtab[0][i]!=NULL; i++){
        pFun = (Fun)pVtab[0][i];
        printf("vtable[0][%d]: %p -> %p ", i, &pVtab[0][i], (void *)pVtab[0][i]);
        pFun();
        pFun = (Fun)pVtab[0][i+1];
        //printf("Call vtable[%d] done!\n", i);
    }
    
    printf("vtable[0] done!\n");
    printf("vtable[1]: %p -> singleParentClass:data_parent = %lu\n", &pVtab[1], (unsigned long)pVtab[1] & 0xffffffff);
    printf("vtable[2]: %p -> childClass:data_child = %lu\n", &pVtab[2], (unsigned long)pVtab[1] >> 32);

    // 多继承子类
    pVtab = (unsigned long**)&chldClassAB;
    printf("\n=============================== childClassAB ===============================\n");
    printf("****************** singleParentXAClass ******************\n");
    printf("vtable[0]: %p\n", &pVtab[0]);
    for (int i=0; (Fun)pVtab[0][i]!=NULL, i<6; i++){
        pFun = (Fun)pVtab[0][i];
        printf("vtable[0][%d]: %p -> %p ", i, &pVtab[0][i], (void *)pVtab[0][i]);
        pFun();
        pFun = (Fun)pVtab[0][i+1];
        //printf("Call vtable[%d] done!\n", i);
    }
    
    printf("vtable[0] done!\n");
    printf("vtable[1]: %p -> singleParentXAClass:data_parentXA = %lu\n", &pVtab[1], (unsigned long)pVtab[1] & 0xffffffff);
    printf("****************** singleParentBClass ******************\n");
    
    int s = sizeof(singleParentAClass)/8;
    printf("vtable[%d]: %p\n", s, &pVtab[s]);
    for (int i=0; (Fun)pVtab[s][i]!=NULL, i<3; i++){
        pFun = (Fun)pVtab[s][i];
        printf("vtable[%d][%d]: %p -> %p ", s, i, &pVtab[s][i], (void *)pVtab[s][i]);
        pFun();
        pFun = (Fun)pVtab[s][i+1];
        //printf("Call vtable[%d][%d] done!\n", s, i);
    }
    printf("vtable[%d]: %p -> singleParentBClass:data_parentB = %lu\n", s, &pVtab[s+1], (unsigned long)pVtab[s+1] & 0xffffffff);
    printf("****************** childClassAB ******************\n");
    printf("vtable[%d]: %p -> childClassAB:data_child = %lu\n", s+1, &pVtab[s+1], (unsigned long)pVtab[s+1] >> 32);

    // Y型多继承子类
    pVtab = (unsigned long**)&chldClassXAB;
    printf("\n=============================== childClassXAB ===============================\n");
    printf("****************** singleParentXAClass ******************\n");
    printf("vtable[0]: %p\n", &pVtab[0]);
    for (int i=0; (Fun)pVtab[0][i]!=NULL, i<8; i++){
        pFun = (Fun)pVtab[0][i];
        printf("vtable[0][%d]: %p -> %p ", i, &pVtab[0][i], (void *)pVtab[0][i]);
        pFun();
        pFun = (Fun)pVtab[0][i+1];
        //printf("Call vtable[%d] done!\n", i);
    }
    
    printf("vtable[0] done!\n");
    printf("vtable[1]: %p -> singleParentXClass:data_parentX = %lu\n", &pVtab[1], (unsigned long)pVtab[1] & 0xffffffff);
    printf("vtable[1]: %p -> singleParentXAClass:data_parentXA = %lu\n", &pVtab[1], (unsigned long)pVtab[1] >> 32);
    printf("****************** singleParentXBClass ******************\n");
    
    s = sizeof(singleParentXAClass)/8;
    printf("vtable[%d]: %p\n", s, &pVtab[s]);
    for (int i=0; (Fun)pVtab[s][i]!=NULL, i<6; i++){
        pFun = (Fun)pVtab[s][i];
        printf("vtable[%d][%d]: %p -> %p ", s, i, &pVtab[s][i], (void *)pVtab[s][i]);
        pFun();
        pFun = (Fun)pVtab[s][i+1];
        //printf("Call vtable[%d][%d] done!\n", s, i);
    }
    printf("vtable[1]: %p -> singleParentXClass:data_parentX = %lu\n", &pVtab[s+1], (unsigned long)pVtab[s+1] & 0xffffffff);
    printf("vtable[1]: %p -> singleParentXBClass:data_parentXB = %lu\n", &pVtab[s+1], (unsigned long)pVtab[s+1] >> 32);
    printf("****************** childClassXAB ******************\n");
    printf("vtable[%d]: %p -> childClassXAB:data_child = %lu\n", s+2, &pVtab[s+2], (unsigned long)pVtab[s+2] & 0xffffffff);

    // 菱形多继承子类 （虚继承）
    pVtab = (unsigned long**)&chldClassVXAB;
    printf("\n=============================== chldClassVXAB ===============================\n");
    printf("****************** singleParentVXAClass ******************\n");
    printf("vtable[0]: %p\n", &pVtab[0]);
    for (int i=0; (Fun)pVtab[0][i]!=NULL, i<6; i++){
        pFun = (Fun)pVtab[0][i];
        printf("vtable[0][%d]: %p -> %p ", i, &pVtab[0][i], (void *)pVtab[0][i]);
        pFun();
        pFun = (Fun)pVtab[0][i+1];
        //printf("Call vtable[%d] done!\n", i);
    }
    
    printf("vtable[0] done!\n");
    printf("vtable[1]: %p -> singleParentVXAClass:data_parentVXA = %lu\n", &pVtab[1], (unsigned long)pVtab[1] & 0xffffffff);
    printf("****************** singleParentVXBClass ******************\n");
    
    s = sizeof(singleParentXAClass)/8;
    printf("vtable[%d]: %p\n", s, &pVtab[s]);
    for (int i=0; (Fun)pVtab[s][i]!=NULL, i<3; i++){
        pFun = (Fun)pVtab[s][i];
        printf("vtable[%d][%d]: %p -> %p ", s, i, &pVtab[s][i], (void *)pVtab[s][i]);
        pFun();
        pFun = (Fun)pVtab[s][i+1];
        //printf("Call vtable[%d][%d] done!\n", s, i);
    }
    printf("vtable[%d]: %p -> singleParentVXBClass:data_parentXB = %lu\n", s+1,  &pVtab[s+1], (unsigned long)pVtab[s+1] & 0xffffffff);
    printf("****************** childClassVXAB ******************\n");
    printf("vtable[%d]: %p -> childClassVXAB:data_childV = %lu\n", s+1, &pVtab[s+1], (unsigned long)pVtab[s+1] >> 32);

    printf("****************** singleParentVXClass ******************\n");
    s = s+ sizeof(singleParentXBClass)/8;
    printf("vtable[%d]: %p 0x%08x%08x\n", s,   &pVtab[s],   (unsigned long)pVtab[s]>>32,   (unsigned long)pVtab[s]   & 0xffffffff);
    printf("vtable[%d]: %p 0x%08x%08x\n", s+1, &pVtab[s+1], (unsigned long)pVtab[s+1]>>32, (unsigned long)pVtab[s+1] & 0xffffffff);
    printf("vtable[%d]: %p 0x%08x%08x\n", s+2, &pVtab[s+2], (unsigned long)pVtab[s+2]>>32, (unsigned long)pVtab[s+2] & 0xffffffff);
    printf("vtable[%d]: %p 0x%08x%08x\n", s+3, &pVtab[s+3], (unsigned long)pVtab[s+3]>>32, (unsigned long)pVtab[s+3] & 0xffffffff);
    printf("vtable[%d]: %p 0x%08x%08x\n", s+4, &pVtab[s+4], (unsigned long)pVtab[s+4]>>32, (unsigned long)pVtab[s+4] & 0xffffffff);
    printf("vtable[%d]: %p 0x%08x%08x\n", s+5, &pVtab[s+5], (unsigned long)pVtab[s+5]>>32, (unsigned long)pVtab[s+5] & 0xffffffff);
    for (int i=0; (Fun)pVtab[s][i]!=NULL, i<4; i++){
        pFun = (Fun)pVtab[s][i];
        printf("vtable[%d][%d]: %p -> %p ", s, i, &pVtab[s][i], (void *)pVtab[s][i]);
        if(i==3)
           pFun();
        pFun = (Fun)pVtab[s][i+1];
        printf("Call vtable[%d][%d] done!\n", s, i);
    }
    printf("vtable[1]: %p -> singleParentVXClass:data_parentVX = %lu\n", &pVtab[s+1], (unsigned long)pVtab[s+1] & 0xffffffff);
    chldClassVXAB.single_parentVX_func_d();
    return 0;
}