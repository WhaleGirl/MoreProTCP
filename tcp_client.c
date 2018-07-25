#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("Usage %s [ip] [port]\n",argv[0]);
		return 1;
	}

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		return 2;
	}

	struct sockaddr_in server_socket;
	server_socket.sin_family = AF_INET;
	server_socket.sin_addr.s_addr = inet_addr( argv[1]);
	server_socket.sin_port = htons(atoi(argv[2]));

	if(connect(sock,(struct sockaddr*)&server_socket,sizeof(server_socket))<0)
	{
		perror("connect");
		return 3;
	}
	printf("connect success\n");

	while(1)
	{
		char buf[1024];
		printf("client# ");
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		write(sock,buf,sizeof(buf));

		read(sock,buf,sizeof(buf));
		printf("server# %s\n",buf);
	}
	close(sock);
	return 0;
}
