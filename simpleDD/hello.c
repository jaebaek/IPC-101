#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init( void )
{
    printk( "hello is initialized\n");
    return 0;
}

static void __exit hello_exit( void )
{
    printk( "hello is exited\n");
}

module_init( hello_init );
module_exit( hello_exit );

// device_initcall( channel_init );

MODULE_LICENSE( "GPL" );
