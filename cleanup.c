#include"header.h"
#include"declarations.h"
static void cleanup(void)
{
printk(KERN_INFO"Loading EXIT  Function\n");
cdev_del(&sculldev->c_dev);
kfree(sculldev);
//remove_proc_entry("gurpartap",NULL);
remove_proc_entry("gurpartap",NULL);
unregister_chrdev_region(dev,1);
}
module_exit(cleanup);
