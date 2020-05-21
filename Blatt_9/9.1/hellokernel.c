/*
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/init.h>
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/module.h> /* Needed by all modules */

MODULE_LICENSE("GPL");

static char* name = "Kernel";
module_param(name, charp, 0444);
MODULE_PARM_DESC(name, "Name to greet");

static int hello_start(void)

{
    printk(KERN_INFO "Hello %s\n", name);

    /*
	 * A non 0 return means init_module failed; module can't be loaded.
	 */
    return 0;
}

static void hello_end(void)
{
    printk(KERN_INFO "Goodbye %s\n", name);
}

module_init(hello_start);
module_exit(hello_end);
