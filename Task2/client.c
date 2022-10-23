// Client side implementation of UDP client-server model
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

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE]="hello";
	
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	//memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
	int des=0,qty=0,price=0,country=0,custid=0;
	
	while(strcmp(buffer, "EXIT")!=0)
	{
	
	
	printf("\nPress 1/0 to see/not-see desciption : ");
	scanf("%d",&des); 
	printf("\nPress 1/0 to see/not-see Quantity   : ");
	scanf("%d",&qty); 
	printf("\nPress 1/0 to see/not-see Price      : ");
	scanf("%d",&price); 
	printf("\nPress 1/0 to see/not-see Customer ID: ");
	scanf("%d",&custid); 
	printf("\nPress 1/0 to see/not-see Country    : ");
	scanf("%d",&country); 
	
	printf("Enter Invoice Number to request or EXIT to terminate : ");
	scanf("%s",buffer);
	
	
	sendto(sockfd, (const char *)buffer, strlen(buffer),0, (const struct sockaddr *) &servaddr,sizeof(servaddr));
	
	
	while(strcmp(buffer, "Enough")!=0)
	{
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,0, (struct sockaddr *) &servaddr,&len);
	buffer[n] = '\0';
	if(strcmp(buffer, "EXIT")!=0)
	
	{
	
	
	//printf("%s\n",buffer);
	    char *token = strtok(buffer, " \t");
	    int i = 0;
	    while (token) 
	    {
	    	if(i==1 && des==1)
	    	printf("\nDescription: %s",token);
	    	if(i==2&& qty==1)
	    	printf("\nQuantity   : %s",token);
	    	if(i==3&& price==1)
	    	printf("\nPrice in $ : %s",token);
	    	if(i==4&& custid==1)
	    	printf("\nCustomer ID: %s",token);
	    	if(i==5&& country==1)
	    	printf("\nCountry    : %s",token);
		i++;
		token = strtok(NULL, "\t");
	    }
	
	}
	
	}
	
	}
	
	
	//printf("Hello message sent.\n");
		
	
	//printf("Server : %s\n", buffer);

	close(sockfd);
	return 0;
}
