#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int cont,sfd;
	float buffer[3];
	char result[1020];
	struct sockaddr_in my_addr;
	if ((sfd = socket(AF_INET,SOCK_STREAM,0)) > 0) 
	   printf("The Socket was created\n");
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(5003);
	inet_pton(AF_INET,argv[1],&my_addr.sin_addr);

	if (connect(sfd,(struct sockaddr *) &my_addr,  sizeof(my_addr)) == 0)
	printf("The connection was accepted with the server %s...\n",    argv[1]);

	printf("Enter the operand1  "); 
	scanf("%f",&buffer[0]);
	printf("Enter the operand2 "); 
	scanf("%f",&buffer[1]);
	printf("Enter the operator \n Enter 42 for  *,43 for  +,45 for  -, 47 for  /");
	scanf("%f",&buffer[2]);
	//scanf("%c",&operand);
	//buffer[2]=(int)operand;
	
	write(	sfd, buffer, sizeof(buffer));	
	printf("operation is %f %c %f",buffer[0],(int)buffer[2],buffer[1]);
	memset(buffer,0,sizeof(buffer));
	read(sfd, result, sizeof(result));
	printf("%s\n",result);
	
	return close(sfd);
}
