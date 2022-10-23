#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
	char buff[MAX],reply[MAX];
	int n;
	
	    time_t t;   // not a primitive datatype
	    time(&t);
			
		for(int j=0; j<5; j++)
		{
		
		for(int i=0; i<6; i++)
		{
		
			bzero(buff, sizeof(buff));
			if(i==0)
			printf("Enter your Name : ");
			if(i==1)
			printf("Enter your Age : ");
			if(i==2)
			printf("Enter your Weight : ");
			if(i==3)
			printf("Enter your Height : ");
			if(i==4)
			printf("Enter your Join Start Day : ");
			if(i==5)
			printf("Enter your Package Name : ");
			n = 0;
			while ((buff[n++] = getchar()) != '\n');
			buff[n-1]='\0';
			write(sockfd, buff, sizeof(buff));
		}
	
		read(sockfd, reply, sizeof(reply));
		
		printf("/n Registration Date and Time   %s    You will join on %s",reply,ctime(&t));
		}
		
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
