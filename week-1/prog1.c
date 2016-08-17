#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>

int main(int argc, char *argv[])
{
	struct addrinfo hint, *res = NULL;
	int ret;

	memset(&hint, '\0', sizeof hint);
	hint.ai_family = PF_UNSPEC;
	hint.ai_flags = AI_NUMERICHOST;

	ret = getaddrinfo(argv[1], NULL, &hint, &res);
	if(ret)
	{
		puts("Invalid Address");
		puts(gai_strerror(ret));
		return 1;
	}

	if(res->ai_family == AF_INET)
	{
		printf("%s is an ipv4 address\n",argv[1]);
	}
	else if(res->ai_family == AF_INET6)
	{
		printf("%s is an ipv6 address\n",argv[1]);
	}
	else
	{
		printf("%s is unknown address format %d\n",argv[1],res->ai_family);
	}

	freeaddrinfo(res);
	return 0;
}
