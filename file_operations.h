
struct file_operations fops=
{
	open:scull_open,
	release:scull_release,
	write:scull_write,
	read:scull_read,
	llseek:scull_lseek
};
