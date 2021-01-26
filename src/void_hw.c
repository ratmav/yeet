#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE(“GPL”);

static int __init lkm_example_init(void) {
 printk(KERN_INFO “preparing to yeet.\n”);
 return 0;
}

static void __exit lkm_example_exit(void) {
 printk(KERN_INFO “yeeting complete.\n”);
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);
