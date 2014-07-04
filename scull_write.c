#include"header.h"
/*######## Function to calculate no. of Scullqsets #################*/
int calculate_scullqsets(struct sculldev *lsculldev,int size)
{
   int noqs=0;
   printk(KERN_INFO"quantum_size=%d\n",lsculldev->quantum_size);
   printk(KERN_INFO"qset_size=%d\n",lsculldev->qsetsize);
   printk(KERN_INFO"lsculldev=%p\n",lsculldev);
   noqs=size/(lsculldev->quantum_size*lsculldev->qsetsize);
   if(size%(lsculldev->quantum_size*lsculldev->qsetsize))
	  noqs++;
   return noqs;
}

/*########## scullqsets are made according to data bytes written to device buffer ############*/
struct scullqset * create_scullqset(int noqs)
{
   int i;
   struct scullqset *first,*temp;
   printk(KERN_INFO"Current Function = %s\n",__func__);
   printk(KERN_INFO"No. of Scullqsets = %d\n",noqs);
   temp=(struct scullqset *)kmalloc(sizeof(struct scullqset),GFP_KERNEL);
   first=temp;
   printk(KERN_INFO"Address of first scullqset = %p\n",temp);
   for(i=1;i<noqs;i++)
   {
	  temp->next=(struct scullqset *)kmalloc(sizeof(struct scullqset),GFP_KERNEL);//put address into next pointer
	  printk(KERN_INFO"Address of first scullqset = %p\n",temp->next);
	  temp=temp->next;//move pointer(temp) to next memory address  
   }
   printk(KERN_INFO"Address of first scullqset = %p\n",first);
   temp->next=NULL;
   return first;
}
void create_qset(struct sculldev *lsculldev,struct scullqset *lscullqset,int noqs)
{
   int i;

   printk(KERN_INFO"Inside Function  =  %s\n",__func__);
   printk(KERN_INFO"No. of Scullqsets in create_qset function= %d\n",noqs);
   printk(KERN_INFO"address of lscullqset =  %p\n",lscullqset);
   for(i=0;i<noqs;i++)
   {
	  lscullqset->data=(void *)kmalloc((sizeof(void *)* lsculldev->qsetsize),GFP_KERNEL);
	   
	  if(!lscullqset->data)
	  {
		 printk(KERN_ERR"error in qset_array");
		 //	  goto out;
	  }
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+0);
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+1);
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+2);
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+3);
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+4);
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+5);
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+6);
	  printk(KERN_INFO"address of data =  %p\n",(void *)lscullqset->data+7);
	  lscullqset=lscullqset->next;
   }  
}
void create_quantums(struct scullqset *lscullqset,int noq)
{
   int lv,no=14;
   printk(KERN_INFO"function =  %s\n",__func__);
   for(lv=0;lv<=8;lv++)
   {
	  if(no==0)
		 break;
	  if(lv==8)
	  {
		 lscullqset=lscullqset->next;
		 lv=0;
	  }
	  lscullqset->data[lv]=(void *)kmalloc((8),GFP_KERNEL);
	  memset(lscullqset->data[lv],'\0',8);
	  printk(KERN_INFO"address of data[%d] =  %p\n",lv,lscullqset->data[lv]);
	  no--;
   }
}
ssize_t scull_write(struct file *count,const char __user *buf,size_t size,loff_t *lseek)
{
   int flag=0,i,nocr=0,noqs=0,noq=0,noctw=0,nocsw=0;
   char *buffer1;
   struct sculldev *lsculldev;
   struct scullqset *lscullqset;
   lsculldev=count->private_data;
   //lsculldev=(struct sculldev *)kmalloc((sizeof(struct sculldev)),GFP_KERNEL);
   printk(KERN_INFO"address of sculldev11= %p\n",lsculldev);
   lsculldev->quantum_size=8;
   lsculldev->qsetsize=8;
   lsculldev->device_size=0;
noctw=lsculldev->quantum_size;
   printk(KERN_INFO"Value of bytes written %d\n",lsculldev->data_size);
   /*######## buffer to hold Data recieved From Application through Inode ##########*/
   buffer1=(char*)kmalloc((sizeof(char)*212),GFP_KERNEL); 
   copy_from_user(buffer1,buf,size);
   printk(KERN_INFO"buffer data= %s\n",buffer1);

   /*######## Function to calculate REQUIRED NO OF SCULLQSETS according to bytes recieved ###########*/
   noqs=calculate_scullqsets(lsculldev,size);
   printk(KERN_INFO"NO of quantum_sets= %d\n",noqs);

   /*######## Function To create scullqsets according to NOQS calculated #################*/
   lscullqset=lsculldev->scullqset=create_scullqset(noqs);


   /*####### Function to create Qsets #############*/ 
   create_qset(lsculldev,lscullqset,noqs);

   noq=size/lsculldev->quantum_size;
   if(size%lsculldev->quantum_size)
	  noq++;
   printk(KERN_INFO"NO of quantums= %d\n",noq);

   /*####### Function to Create Quantums ###########*/
   create_quantums(lscullqset,noq);
   for(i=0;i<=7;i++)
   {
   if((flag==1)&&(nocr<8))
   {
   copy_from_user((char *)lscullqset->data[i],buf+nocsw,size%noctw);
   break;
   }
flag=1;
   copy_from_user((char *)lscullqset->data[i],buf+nocsw,8);
   nocsw=nocsw+noctw;
   printk(KERN_INFO"no. of characters successfully written %d\n",nocsw);
   nocr=size-nocsw;
   lsculldev->data_size=nocsw;
   printk(KERN_INFO"no. of characters remaining %d\n",nocr);
	  if(i==7)
	  {
	  lscullqset=lscullqset->next;
	  i=i-8;
	  }
   }
   //}
 /* lscullqset=lsculldev->scullqset; 
 strcpy((char*)lscullqset->data[0],"hello");
   strcpy((char*)lscullqset->data[1],"from");
   strcpy((char*)lscullqset->data[2],"world");
   strcpy((char*)lscullqset->data[3],"of");
   strcpy((char*)lscullqset->data[4],"emblogic");
   strcpy((char*)lscullqset->data[5],"noida");
   strcpy((char*)lscullqset->data[6],"india");
   strcpy((char*)lscullqset->data[7],"world");*/
lscullqset=lsculldev->scullqset;
   printk(KERN_INFO"Value of bytes written %d\n",lsculldev->data_size);
/*data=malloc(sizeof(char)*8);
memset(data,'\0',8);
   for(i=0;i<=7;i++)
   {
data=(char *)(lscullqset->data[i]);

   printk(KERN_INFO"data in quantum[%d]= %s\n",i,data );
   }*/
  for(i=0;i<=7;i++)
   {
   printk(KERN_INFO"data in quantum[%d]= %s\n",i, (char*)(lscullqset->data[i]));
   }
  for(i=0;i<=5;i++)
   {
   printk(KERN_INFO"data in quantum[%d]= %s\n",i, (char*)(lscullqset->next->data[i]));
   }
 /*  for(i=0;i<=7;i++)
   {
   printk(KERN_INFO"data in quantum[%d]= %s\n",i, (char*)(lscullqset->next->next->next->data[i]));
   }*/
   return 0;
}

