#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

static struct task_struct *task;

static int yeet(void *arg) {
  while(!kthread_should_stop()) {
    set_current_state(TASK_RUNNING);
    set_current_state(TASK_INTERRUPTIBLE);

    printk(KERN_INFO "(╯°□°）╯︵ ┻━┻\n");

    msleep(3000);
  }
}

static int __init yeet_init(void) {
 printk(KERN_INFO "preparing to yeet.\n");
 task = kthread_run(yeet, NULL, "yeet_thread");
 return 0;
}

static void __exit yeet_exit(void) {
 printk(KERN_INFO "yeeting complete.\n");
}

module_init(yeet_init);
module_exit(yeet_exit);
