#include"header.h"
loff_t scull_lseek (struct file *filep, loff_t position, int type)
{
printk(KERN_INFO"position = %d\n",(int)position);
printk(KERN_INFO"type = %d\n",type);









return 0;
}
