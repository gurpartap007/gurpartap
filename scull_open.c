#include"header.h"
#include"declarations.h"
int scull_trim(struct sculldev * lsculldev)
{
   int i;
   struct scullqset *lscullqset,*prev;
   prev=NULL;
   lscullqset=lsculldev->scullqset;
   while(lscullqset->next!=NULL)
   {
	  prev=lscullqset;
	  lscullqset=lscullqset->next;
	  printk(KERN_INFO"freed memory %p\n",lscullqset);
	  for(i=0;i<=5;i++)
	  {
		 kfree(lscullqset->data[i]);
		 printk(KERN_INFO"freed memory data[%i]%p\n",i,lscullqset->data[i]);
	  }
	  kfree(lscullqset->data);
	  printk(KERN_INFO"freed memory data %p\n",lscullqset->data);
	  kfree(lscullqset->next);
	  kfree(lscullqset);
	  prev->next=NULL;
	  lscullqset=lsculldev->scullqset;
	  printk(KERN_INFO"freed memory %p\n",lscullqset);
   }////////
   for(i=0;i<8;i++)
   {
	  kfree(prev->data[i]);
	  printk(KERN_INFO"freed memory data[%i]%p\n",i,prev->data[i]);
   }
	  kfree(prev->data);
	  printk(KERN_INFO"freed memory data %p\n",prev->data);
	  kfree(prev->next);
	  kfree(prev);
   
	  return 0;
}
   int scull_open(struct inode *inodep,struct file *filep)
   {
	  struct sculldev *lsculldev;
	  printk(KERN_INFO"open called in gill module\n");
	  printk(KERN_INFO"Begin function %s\n",__func__);
	  lsculldev=container_of(inodep->i_cdev,struct sculldev,c_dev);
	  printk(KERN_INFO"Address of device is %p\n",lsculldev);
	  filep->private_data=lsculldev;
	  printk(KERN_INFO"addresss of private data = %p\n",filep->private_data);
	  if((filep->f_flags & O_ACCMODE) == O_WRONLY)
	  {
		 printk(KERN_INFO"OPEN WITH WRITE ONLY\n");
	  if(!lsculldev->scullqset)
		 printk(KERN_INFO"Scullqset not found\n");
	  else
	  {
		 printk(KERN_INFO"Scullqset found\n");
		 scull_trim(lsculldev);
	  }
	  }
	  if((filep->f_flags & O_ACCMODE) == O_RDONLY)
		 printk(KERN_INFO"OPEN WITH READ ONLY\n");
	  if((filep->f_flags & O_ACCMODE) == O_RDWR)
		 printk(KERN_INFO"OPEN WITH READ/WRITE ONLY\n");
	  return 0;
   }

