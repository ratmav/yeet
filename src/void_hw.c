#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");

void workqueue_fn(struct work_struct *work);

DECLARE_WORK(workqueue,workqueue_fn);

void workqueue_fn(struct work_struct *work) {
        printk(KERN_INFO "YEET\n");
}

static int __init yeet_init(void) {
 printk(KERN_INFO "preparing to yeet.\n");
 return 0;
}

static void __exit yeet_exit(void) {
 printk(KERN_INFO "yeeting complete.\n");
}

module_init(yeet_init);
module_exit(yeet_exit);
