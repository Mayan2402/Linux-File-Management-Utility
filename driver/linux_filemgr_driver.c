#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "linux_filemgr"

static char driver_message[100] = "Linux File Manager Driver\n";

/* Called when device is opened */
static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "linux_filemgr: device opened\n");
    return 0;
}

/* Called when data is read from device */
static ssize_t device_read(struct file *file,
                           char __user *buffer,
                           size_t length,
                           loff_t *offset)
{
    int message_length;

    message_length = strlen(driver_message);

    if (*offset >= message_length)
        return 0;

    if (copy_to_user(buffer, driver_message, message_length))
        return -EFAULT;

    *offset = message_length;

    printk(KERN_INFO "linux_filemgr: read operation\n");

    return message_length;
}

/* Called when data is written to device */
static ssize_t device_write(struct file *file,
                            const char __user *buffer,
                            size_t length,
                            loff_t *offset)
{
    size_t copy_length;

    copy_length = min(length, sizeof(driver_message) - 1);

    if (copy_from_user(driver_message, buffer, copy_length))
        return -EFAULT;

    driver_message[copy_length] = '\0';

    printk(KERN_INFO "linux_filemgr: write operation\n");

    return copy_length;
}

/* Called when device is closed */
static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "linux_filemgr: device closed\n");
    return 0;
}

/* File operations */
static const struct file_operations file_ops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .release = device_release,
};

/* Misc device */
static struct miscdevice linux_filemgr_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &file_ops,
    .mode = 0666,
};

/* Module initialization */
static int __init linux_filemgr_init(void)
{
    int result;

    result = misc_register(&linux_filemgr_device);

    if (result != 0) {
        printk(KERN_ERR "linux_filemgr: registration failed\n");
        return result;
    }

    printk(KERN_INFO "linux_filemgr: driver loaded successfully\n");

    return 0;
}

/* Module cleanup */
static void __exit linux_filemgr_exit(void)
{
    misc_deregister(&linux_filemgr_device);

    printk(KERN_INFO "linux_filemgr: driver unloaded\n");
}

module_init(linux_filemgr_init);
module_exit(linux_filemgr_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux File Manager Project");
MODULE_DESCRIPTION("Simple Linux character device driver for File Management Utility");
MODULE_VERSION("1.0");
