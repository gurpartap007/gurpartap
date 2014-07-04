#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
   int fd,ret,count;
   char *buffer;
   buffer=malloc((sizeof(char))*180);
   fd=open("node",O_RDONLY);
   if(fd<0)
	  perror("reading file\n");
   read(fd,buffer,211);
   printf("characters read from the buffer %s\n",buffer);
return 0;
}

