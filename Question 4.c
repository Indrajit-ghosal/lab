#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
void main()
{
int fd1,fd2,fd3,n,m=0;
char buff[50],cpy1[50],cp2[50];
fd1=open("file1.txt",O_CREAT|O_RDWR,770);
printf("Enter The Text\n");
n=read(0,buff,50);
write(fd1,buff,n);
fd1=open("file1.txt",O_RDWR);
read(fd1,cpy1,n);
for(int i=6,j=0;i<=n;i++,j++)
{ cp2[j]=cpy1[i];
m++;
}
fd3=open("New File.txt",O_CREAT|O_RDWR,770);
write(fd3,cp2,m);
fd3=open("New File.txt",O_RDWR);
read(fd3,buff,m);
write(1,buff,m);
}
