#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");


static int __init yeet_init(void) {
 printk(KERN_INFO "preparing to yeet.\n");
 return 0;
}

static void __exit yeet_exit(void) {
 printk(KERN_INFO "yeeting complete.\n");
}

module_init(yeet_init);
module_exit(yeet_exit);
