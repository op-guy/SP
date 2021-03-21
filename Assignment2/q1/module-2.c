#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int __init crash_module_init(void) {
	printk(KERN_INFO "crash module starting:\n");
	int a = 1/0;
	printk("%d\n", a);
	return 0;
}

module_init(crash_module_init);
