/*hello.c a module programm*/ 
/* the program runing under kernel mod and it is a module*/ 
#include "linux/kernel.h" 
#include "linux/module.h" 

/* pross the CONFIG_MODVERSIONS*/ 
#if CONFIG_MODVERSIONS==1 
  #define MODVERSIONS 
  #include "config/modversions.h" 
#endif 

MODULE_LICENSE("GPL");

/* the init function*/ 
static int init_mod()
{
   printk(" hello world !\n"); 
   printk(" I have runing in a kernel"); 
   return 0; 
} 

/* the distory function*/ 
static void cleanup_mod()
{ 
   printk("I will shut down myself in kernerl mod /n"); 
} 

module_init(init_mod);
module_exit(cleanup_mod);
