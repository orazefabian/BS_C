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
#define MAX_INPUT 100

MODULE_AUTHOR("Fabse Oraze");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character device");

//struct file operations:
int namedev_open(struct inode* i, struct file* f);
ssize_t namedev_read(struct file* f, char __user* buf, size_t num, loff_t* offset);
ssize_t namedev_write(struct file* f, const char __user* b, size_t num, loff_t* offset);

static int __init namedev_init(void);
static void __exit namedev_exit(void);

dev_t namedev;
struct cdev* namedev_cdev;
struct file_operations namedev_fops = {
    .owner = THIS_MODULE,
    .read = namedev_read,
    .write = namedev_write,
    .open = namedev_open,
};

int current_pos;
char author[MAX_INPUT] = "Fabian Oraze";

int namedev_open(struct inode* i, struct file* f)
{
    printk(KERN_INFO "namedev_open\n");

    current_pos = 0;
    return 0;
}

ssize_t namedev_read(struct file* f, char __user* buf, size_t num, loff_t* offset)
{
    printk(KERN_INFO "namedev_read: %lu %lld\n", (unsigned long)num, *offset);
    printk(KERN_INFO "namedev: copy positions %d of author string to user\n", current_pos);

    if (copy_to_user(buf, (author + current_pos), 1) != 0) {
        printk(KERN_INFO "namedev: copying failed\n");
        return -1;
    }

    current_pos++;
    if (current_pos >= strlen(author)) {
        current_pos = 0;
    }
    return 1;
}

ssize_t namedev_write(struct file* f, const char __user* b, size_t num, loff_t* offset)
{
    printk(KERN_INFO "namedev: write\n");
    printk(KERN_INFO "num: %ld", num);

    memset(author, 0, MAX_INPUT);
    printk(KERN_INFO "namedev: read %s\n", author);

    if (copy_from_user(author, b, num - 1) != 0) {
        printk(KERN_INFO "namedev: copying from user failed");
    }
    printk(KERN_INFO "namedev: read %s\n", author);

    return num;
}

static int __init namedev_init(void)
{
    printk(KERN_INFO "Namedev started\n");

    namedev = MKDEV(MAJOR_NUMBER, MINOR_NUMBER);
    //check if creation failed
    if (register_chrdev_region(namedev, 1, DEV_NAME) != 0) {
        return -1;
    }

    namedev_cdev = cdev_alloc();

    //add file operations to device
    namedev_cdev->ops = &namedev_fops;

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
