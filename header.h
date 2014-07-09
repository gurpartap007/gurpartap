#include<linux/init.h>
#include<asm-generic/uaccess.h>
#include<linux/decompress/mm.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/string.h>
#include<linux/semaphore.h>
#include<linux/proc_fs.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module for Character Driver");
MODULE_AUTHOR("GURPARTAP_SINGH");
struct sculldev
{
struct cdev c_dev;
struct scullqset *scullqset;
unsigned int quantum_size;
unsigned int qsetsize;
unsigned int device_size;
unsigned int data_size;
};
struct scullqset
{
struct scullqset *next;
unsigned int **data;
};
int scull_open(struct inode *,struct file *);
ssize_t scull_write(struct file *,const char __user *,size_t,loff_t *);
ssize_t scull_read(struct file *, char __user *,size_t,loff_t *);
int scull_release(struct inode *,struct file *);
loff_t scull_lseek(struct file *, loff_t, int);

