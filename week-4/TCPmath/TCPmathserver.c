#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int cont,sfd,cfd,addrlen,fd;
	float buffer[4],n;
	char result[1020];
	struct sockaddr_in my_addr;
	if ((sfd = socket(AF_INET,SOCK_STREAM,0)) > 0) 
		   printf("The socket was created\n");
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(5003);
	if (bind(sfd,(struct sockaddr *)&my_addr,sizeof(my_addr)) ==0 )   
		 printf("Binding Socket\n");
	listen(sfd,3);
	while(1)
	{  
		
		addrlen = sizeof(struct sockaddr_in);
		cfd = accept(sfd,(struct sockaddr *)&my_addr,&addrlen);
		if (cfd > 0)   
		{  	printf("The Client  is Connected...\n");
			recv(cfd,buffer, sizeof(buffer),0);
			printf("Data recieved Operation is %f %c %f\n",buffer[0],(int)buffer[2],buffer[1]);
			
			switch((int)buffer[2])
			{
				case '+': buffer[0]+=buffer[1];	
					  sprintf(result,"\nresult is %f",buffer[0]);break;
				case '-': buffer[0]-=buffer[1];sprintf(result,"\nresult is %f",buffer[0]);break;
				case '*': buffer[0]*=buffer[1];sprintf(result,"\nresult is %f",buffer[0]);break;
				case '/': buffer[0]/=buffer[1];	sprintf(result,"\nresult is %f",buffer[0]);break;
				default : strcpy(result,"Invalid operator");
			}
			
			write(cfd,result,sizeof(result));

		
		}		
		else
			perror("Failure to connect");
		close(cfd);
	}

	return close(sfd);
}
