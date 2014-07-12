#include"header.h"
#include"declarations.h"
#include"file_operations.h"//IF NOT INCLUDED THEN YOUR FUNCTIONS DESCRIBED IN FILE OPERATIONS ARE NOT CALLED BY KERNEL
dev_t dev;
int ret,major_no,minor_no,nod=1;
struct sculldev *sculldev;
struct proc_dir_entry *child; //*parent;
int read_proc(char *page, char **start, off_t off,int count, int *eof, void *data)
{
   count=sprintf(page,"qsetz_size = %d\n""device_size = %d\n""time difference in jiffies(nano-seconds)= %ld\n""time differencein jiffies(seconds)= %ld\n",sculldev->qsetsize,sculldev->device_size,value.tv_sec,value.tv_nsec) ;
   printk(KERN_INFO"page-------%s\n",page);
   return count;
}

#define CHAR_DRIVER "ch_driver";
static int  __init initial(void)
{
   printk(KERN_INFO"Loading Initial Function\n");
   alloc_chrdev_region(&dev,0,nod,"char_driver");
   sculldev=(struct sculldev *)kmalloc (sizeof(struct sculldev),GFP_KERNEL);
   memset(sculldev,'\0',sizeof(struct sculldev));
   major_no=MAJOR(dev);
   minor_no=MINOR(dev);
   printk(KERN_INFO"Major No=  %d\n",major_no);
   printk(KERN_INFO"Minor No= %d\n",minor_no);
   sculldev->c_dev.ops=&fops;
   cdev_init(&sculldev->c_dev,&fops);
   //  parent=proc_mkdir("ch_driver",NULL);
   //sema_init(&sculldev->sem,1);
   init_completion(&sculldev->sem);
   child=create_proc_read_entry("gurpartap",S_IRUSR,NULL,read_proc,NULL);
   sculldev->c_dev.owner= THIS_MODULE;
   ret=cdev_add(&sculldev->c_dev,dev,nod);
   return 0;
}
module_init(initial);
