#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


int __init crash_module_init(void) {
	printk(KERN_INFO "crash module is starting\n");
	panic("It's panic time!");
	return 0;
}

module_init(crash_module_init);
