#include"header.h"
#include"declarations.h"
static void cleanup(void)
{
printk(KERN_INFO"Loading EXIT  Function\n");
cdev_del(&sculldev->c_dev);
kfree(sculldev);
unregister_chrdev_region(dev,1);
}
module_exit(cleanup);
