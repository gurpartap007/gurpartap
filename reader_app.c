#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
   int fd,ret,count;
   char *buffer;
   buffer=malloc((sizeof(char))*288);
   fd=open("node",O_RDONLY);
   if(fd<0)
	  perror("reading file\n");
   read(fd,buffer,288);
   printf("characters read from the buffer %s\n",buffer);
return 0;
}

