#include"header.h"
#include"declarations.h"
#include"file_operations.h"//IF NOT INCLUDED THEN YOUR FUNCTIONS DESCRIBED IN FILE OPERATIONS ARE NOT CALLED BY KERNEL
 dev_t dev;
int ret,major_no,minor_no,nod=1;
struct sculldev *sculldev;
#define CHAR_DRIVER "gurpartap";
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
   sculldev->c_dev.owner= THIS_MODULE;
   ret=cdev_add(&sculldev->c_dev,dev,nod);
   return 0;
}
module_init(initial);
