#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main()
{
	int serversockfd,portno,connfd;
	char buf[256];
	struct sockaddr_in serveraddr,clientaddr;
	serversockfd = socket(AF_INET,SOCK_STREAM,0);
	if(serversockfd < 0)
	{
		printf("Opening socket failed : socket");
		exit(0);
	}
	printf("Enter port no for server:" );
	scanf("%d",&portno);
	memset(&serveraddr,'\0',sizeof(serveraddr));	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	serveraddr.sin_port=htons(portno);
	
	if(bind(serversockfd,(struct sockaddr *) &serveraddr,sizeof(serveraddr))<0)
	{
		printf("bind failed");
		exit(0);
	}

	if(listen(serversockfd,5)>0)
	{
		printf("Listening failed");
		exit(0);
	}

	printf("waiting for request from client....\n");
	socklen_t clientlen = sizeof(clientaddr);
	connfd = accept(serversockfd,(struct sockaddr *)&clientaddr,&clientlen);
	if(connfd < 0)
	{
		printf("accept failed");
		exit(0);
	}

	printf("received request from client : Hurrah!!\n");

	while(1)
	{
		
		if(recv(connfd,buf,sizeof(buf),0) < 0)
		{
			printf("Error in Receiving Data From client");
			exit(1);
		}
		puts(buf);
	}
	return 0;
}
