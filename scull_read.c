#include"header.h"
ssize_t scull_read(struct file *filep,char __user *buffer1,size_t count,loff_t *lseek)
{
	struct sculldev *lsculldev;
	struct scullqset *lscullqset;
	int flag=0,i,nocsw=0,nocr=0,noctw=0,quantum_size,noctr=0;
	lsculldev=filep->private_data;
	noctw=noctr=lsculldev->data_size;
	lscullqset=lsculldev->scullqset;
	quantum_size=lsculldev->quantum_size;
	printk(KERN_INFO"Address = %p\n",lscullqset);
	for(i=0;i<8;i++)
	{
		if(flag==1&&nocr==0)
			break;
		if(noctr>=8)
		{
			noctr=quantum_size;
		}
		else
		{
			copy_to_user(buffer1+nocsw,(char *)lscullqset->data[i],noctr);
			printk(KERN_INFO"Address of [%d]= %p\n",i,lscullqset->data[i]);
		}
		copy_to_user(buffer1+nocsw,(char *)lscullqset->data[i],noctr);
		printk(KERN_INFO"Address of [%d]= %p\n",i,lscullqset->data[i]);
		nocsw=nocsw+noctr;
		nocr=noctw-nocsw;
		flag=1;
		if(i==7)
		{
			lscullqset=lscullqset->next;
			i=0-1;
		}
	}

	return 0;
}

