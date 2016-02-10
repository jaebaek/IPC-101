#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

// struct file_operations
#include <linux/fs.h>

// kmalloc
#include <linux/slab.h>

// copy_from_user, copy_to_user
#include <asm/uaccess.h>

#define MAJOR_NUMBER 250

#define DEBUG 1
#if DEBUG
#define dlog(...) \
    printk("%s, %d:", __FILE__, __LINE__); \
    printk(__VA_ARGS__)
#else
#define dlog(...)
#endif

#define BUFF_SIZE 1024
static char *buf  = NULL;

static int msg_open( struct inode *inode, struct file *filp )
{
    dlog( "[msg] opened\n" );
    return 0;
}

static int msg_release( struct inode *inode, struct file *filp )
{
    dlog( "[msg] released\n" );
    return 0;
}

static long msg_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int byte;

    dlog( "[msg] ioctl: %d\n", cmd );
    if (cmd == 0) {
        byte = copy_from_user(buf, (void __user *)arg, BUFF_SIZE);
        if (byte)
            dlog( "[msg] error in ioctl: cannot read %d bytes\n", byte);
    } else if (cmd == 1) {
        byte = copy_to_user((void __user *)arg, buf, BUFF_SIZE)
        if (byte)
            dlog( "[msg] error in ioctl: cannot write %d bytes\n", byte);
    }
    return 0;
}

static struct file_operations msg_fops = {
    .owner = THIS_MODULE,
    //.read = msg_read,
    //.write = msg_write,
    .open = msg_open,
    .unlocked_ioctl = msg_ioctl,
    .compat_ioctl = msg_ioctl,
    .release = msg_release
};

static int __init msg_init( void )
{
    register_chrdev( MAJOR_NUMBER, "simple_msg_dd", &msg_fops );
    buf = (char*) kmalloc( BUFF_SIZE, GFP_KERNEL );
    dlog( "msg is initialized\n" );
    return 0;
}

static void __exit msg_exit( void )
{
    unregister_chrdev( MAJOR_NUMBER, "simple_msg_dd" );
    kfree( buf );
    dlog( "msg is exited\n" );
}

module_init( msg_init );
module_exit( msg_exit );

// device_initcall( msg_init );

MODULE_LICENSE( "GPL" );
