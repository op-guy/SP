#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

int __init crash_module_init(void) {
	printk(KERN_INFO "crash module is starting\n");
	int* a = NULL;
	*a = *a + 5;
	printk("%d\n", *a);
	return 0;
}

module_init(crash_module_init);
