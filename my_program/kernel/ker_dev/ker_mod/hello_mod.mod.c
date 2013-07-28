#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x580b5dbe, "module_layout" },
	{ 0x4bb541bc, "cdev_del" },
	{ 0x3e1b919c, "kmalloc_caches" },
	{ 0x47fab92d, "cdev_init" },
	{ 0xb85f3bbe, "pv_lock_ops" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x4aabc7c4, "__tracepoint_kmalloc" },
	{ 0x670c0597, "down_interruptible" },
	{ 0x70aecb65, "device_destroy" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x97c5ab56, "kmem_cache_alloc_notrace" },
	{ 0xb72397d5, "printk" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0xb4390f9a, "mcount" },
	{ 0x352da304, "device_create" },
	{ 0x28210843, "cdev_add" },
	{ 0x6443d74d, "_raw_spin_lock" },
	{ 0x37a0cba, "kfree" },
	{ 0x57b09822, "up" },
	{ 0x7caddf16, "class_destroy" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x405fac01, "__class_create" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C0FF98B1DBEBA8333955454");
