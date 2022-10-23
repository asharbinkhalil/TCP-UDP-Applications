// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024



struct sockaddr_in servaddr, cliaddr;
int sockfd;

void nizaam(char *IV)
{
	int len = sizeof(cliaddr);
	
	FILE* filePointer;
	int bufferLength = 255;
	char buffer[bufferLength];

	filePointer = fopen("dataset.txt", "r");
	char en[]="Enough";
	while(fgets(buffer, bufferLength, filePointer)) 
	{
	
		if(strncmp(buffer,IV,6)==0)
			sendto(sockfd, (const char *)buffer, strlen(buffer),0, (const struct sockaddr *) &cliaddr,len);
	}
	sendto(sockfd, (const char *)en, strlen(en),0, (const struct sockaddr *) &cliaddr,len);

	fclose(filePointer);

}

// Driver code
int main() {
	
	char buffer[MAXLINE];
	
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;

	len = sizeof(cliaddr); //len is value/resuslt


	while(strcmp(buffer, "EXIT")!=0)
	{
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,0, ( struct sockaddr *) &cliaddr,&len);
	buffer[n] = '\0';
	if(strcmp(buffer, "EXIT")!=0)
		nizaam(buffer);
	}
	
			
//	printf("Hello message sent.\n");
	
	return 0;
}
