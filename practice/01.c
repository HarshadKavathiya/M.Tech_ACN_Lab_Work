#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int f1,f2,n;
	char ch[100];
	f1 = open("file1.txt",O_RDONLY | O_NONBLOCK);
	if(f1==-1)
	{
		printf("Source File not Found");
		return 0;
	}
	if(f2==-1)
	{
		printf("Destination File not Found");
		return 0;
	}
	
	f2 = open("file2.txt",O_RDWR | O_CREAT);
	while((n=read(f1,ch,100)) != 0)
	{
		write(f2,ch,100);
	}
	close(f1);
	close(f2);
}
