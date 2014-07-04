#include"header.h"
int scull_release(struct inode *inodep,struct file *filep)
{
printk(KERN_INFO"CLOSE CALLED\n");
return 0;

}
