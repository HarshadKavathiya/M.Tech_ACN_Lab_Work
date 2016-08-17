#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

main()
  {
   int sd,i,len,bi,nsd,port;
   char content[30];
   struct sockaddr_in ser,cli;
   
   if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
     {
        printf("\n Socket problem");
        return 0;
     }

   printf("\n Socket created\n");

   bzero((char*)&ser,sizeof(ser));

   printf("\nEnter the Port No.:");
   scanf("%d",&port);


   printf("\nPort Number is: %d\n",port);

   ser.sin_family=AF_INET;
   ser.sin_port=htons(port);
   ser.sin_addr.s_addr=htonl(INADDR_ANY);


   bi=bind(sd,(struct sockaddr *)&ser,sizeof(ser));

   if(bi==-1)
     {
      printf("\n bind error, port busy, plz change port in client and server");
      return 0;
     }

   i=sizeof(cli);
   listen(sd,5);

   nsd = accept(sd,((struct sockaddr *)&cli),&i);

   if(nsd==-1)
    {
      printf("\ncheck the description parameter\n");
      return 0;
    }

   printf("\nConnection accepted\n");

   if(fork())
    {
      printf("\nEnter the 'exit' to stop Chat\n");
      scanf("%s",content);
      
      while(strcmp(content,"exit")!=0)
        {
         send(nsd,content,30,0);
         scanf("%s",content);
        }
     send(nsd,"exit",5,0);
    
    }

   else
    { 
     i = recv(nsd,content,30,0);

     while(strcmp(content,"exit")!=0)
     {
      printf("Received from Client: %s\n",content);
      i=recv(nsd,content,30,0);
     }
    }
  close(sd);
  close(nsd);
  return 0;
}


