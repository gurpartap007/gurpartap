#include"header.h"
 struct timespec value;
   unsigned long b,c;
ssize_t scull_read(struct file *filep,char __user *buffer1,size_t count,loff_t *lseek)
{
   unsigned long end,result;
	struct sculldev *lsculldev;
	struct scullqset *lscullqset;
	int flag=0,i,nocsw=0,nocr=0,total_size=0,quantum_size,noctr=0;
	lsculldev=filep->private_data;
			wait_for_completion(&lsculldev->sem);
	total_size=nocr=lsculldev->data_size;
	lscullqset=lsculldev->scullqset;
	quantum_size=lsculldev->quantum_size;
//	printk(KERN_INFO"Address = %p\n",lscullqset);
	for(i=0;i<8;i++)
	{
		if(lsculldev->scullqset)
		{
		if(flag==1&&nocr==0)
		{
		//	printk(KERN_INFO"inside break\n");
			break;
		}
		if(nocr>=8)
		{
			noctr=quantum_size;
		copy_to_user(buffer1+nocsw,(char *)lscullqset->data[i],noctr);
	//	printk(KERN_INFO"Address of [%d]= %p\n",i,lscullqset->data[i]);
		nocr=total_size-nocsw;
		nocsw=nocsw+noctr;
			//printk(KERN_INFO"value of ncr = %d\n",nocr);
		flag=1;
		}
		else
		{
			copy_to_user(buffer1+nocsw,(char *)lscullqset->data[i],noctr);
		//	printk(KERN_INFO"Address of [%d]= %p\n",i,lscullqset->data[i]);
		}
		if(i==7)
		{
			lscullqset=lscullqset->next;
			i=0-1;
		}
		}
		else
		   break;
	}
	b=jiffies;
	c=time_before(t,b);
	jiffies_to_timespec(c,&value);

		//	printk(KERN_INFO"time in jiffies = %ld\n",c);
		//	printk(KERN_INFO"time in seconds = %ld\n",value.tv_sec);
		//	printk(KERN_INFO"time in nano-seconds = %ld\n",value.tv_nsec);
			rdtscl(end);
			result=end-start;
		printk(KERN_INFO"::::::::::VALUE OF COUNTER = %lu::::::::::\n",result);
	return 0;
}

