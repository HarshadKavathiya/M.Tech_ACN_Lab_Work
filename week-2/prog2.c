#include<stdio.h>
void main()
{
	int buff[10];
	int checksum=0, i, a,b;

	printf("Kindly Enter IP Header in group of 16-bit in Hexadecimal Form");
	for(i=0;i<10;i++)
	{	
		printf("\nKindly Enter %d set = ",i+1); 
		scanf("%x",&buff[i]);
	}

	a = buff[5];
	buff[5]= 0x0000;

	for(i=0;i<10;i++)
	{
		checksum = checksum + buff[i];		
	}
	
	printf("Checksum = %x \n",checksum);
	checksum = (checksum>>16) + (checksum & 0xffff);
	checksum = checksum + (checksum>>16);
	checksum = 0xffff - checksum;
	printf("\nChecksum = %04x \n",checksum);

	if(checksum==a)
	{
		printf("\nChecksum is Correct\n");
	}
	else
	{
		printf("\nChecksum is Wrong");	
	}

}
