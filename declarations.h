extern dev_t dev;
extern struct file_operations fops;
extern struct sculldev *sculldev;
extern struct proc_dir_entry *child, *parent;
extern int read_proc(char *page, char **start, off_t off,int count, int *eof, void *data);
