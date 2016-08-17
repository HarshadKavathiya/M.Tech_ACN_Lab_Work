#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

int main()
 {
  int sd,con,port,i;
  char content[30];
  struct sockaddr_in cli;

  if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
   {
    printf("\n Socket problem");
    return 0;
   }

  

  
  printf("Enter Port No.:-");
  scanf("%d",&port);
  
  cli.sin_family = AF_INET;
  cli.sin_port=htons(port);
  cli.sin_addr.s_addr=htonl(INADDR_ANY);
  
  con=connect(sd,(struct sockaddr*)&cli,sizeof(cli));
  if(con==-1)
   {
    printf("\n connection error");
    return 0;
   }

  if(fork())
   {
    printf("\nEnter the 'exit' to stop Chat\n");
    scanf("%s",content);
    while(strcmp(content,"exit")!=0)
      {
       send(sd,content,30,0);
       scanf("%s",content);
      }
     send(sd,"exit",5,0);
   }

  else
   {
     i=recv(sd,content,30,0);
      while(strcmp(content,"exit")!=0)
       { 
        printf("Received from Server: %s\n",content);
        i=recv(sd,content,30,0);
       }
   send(sd,"exit",5,0);
   }

  close(sd);
  return 0;
}
