#include"header.h"
loff_t scull_lseek (struct file *filep, loff_t position, int type)
{
printk(KERN_INFO"position = %d\n",(int)position);
printk(KERN_INFO"type = %d\n",type);
  printk(KERN_INFO"file pointer stored in filep = %d\n" ,(int)filep->f_pos);
switch(type)
{
   case 0:
   printk(KERN_INFO"file position is %d away from begining\n",(int)position);
   filep->f_pos=position;
   break;
   case 1:
   printk(KERN_INFO"current position of filepointer is %d\n",(int)position);
   filep->f_pos=position;
   break;
}
return 0;
}
