#include <linux/cdev.h>
#include <linux/export.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define DEV_NAME "namedev"
#define MAJOR_NUMBER 120
#define MINOR_NUMBER 100

MODULE_AUTHOR("Fabse");
MODULE_LICENSE("GLP");
MODULE_DESCRIPTION("Info for module");

dev_t namedev;
struct cdev* namedev_cdev;

static int __init namedev_init(void)
{
    printk(KERN_INFO "Namedev started\n");

    namedev = MKDEV(MAJOR_NUMBER, MINOR_NUMBER);
    //check if creation failed
    if (register_chrdev_region(namedev, 1, DEV_NAME) != 0) {
        return -1;
    }

    namedev_cdev = cdev_alloc();

    cdev_add(namedev_cdev, namedev, 1);

    return 0;
}

static void __exit namedev_exit(void)
{
    printk(KERN_INFO "Namedev ended\n");

    unregister_chrdev_region(namedev, 1);

    cdev_del(namedev_cdev);
}

module_init(namedev_init);
module_exit(namedev_exit);
