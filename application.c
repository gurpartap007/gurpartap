#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
int main()
{
int ret,fd,len;
char arr[]="00000000111111112222222233333333444444445555555566666666777777778888888899999999AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDDEEEEEEEEFFFFFFFFGGGGGGGGHHHHHHHHIIIIIIIIJJJJJJJJKKKKKKKKLLLLLLLLMMMMMMMMNNNNNNNNOOOOOOOOPPPPPPPPQQQQQQQQRRRRRRRRSSSSSSSSTTTTTTTTUUUUUUUUVVVVVVVVWWWWWWWWXXXXXXXXYYYYYYYYZZZZZZZZ";
fd=open("node",O_WRONLY);
printf("fd=%d\n",fd);
len=strlen(arr);
printf("length of string=%d\n",len);
ret=write(fd,arr,len);
printf("ret=%d\n",ret);
printf("writing data= %s\n",arr);
close(fd);
return 0;
}
