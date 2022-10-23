#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void filewrite(char* arr,char *pkginfo)
{

	
	    time_t t;   // not a primitive datatype
	    time(&t);
	    FILE *fptr;
	    fptr = fopen(pkginfo, "a");
	      
	    fprintf(fptr, "%s", "01");
	    fprintf(fptr, "%s", "       ");
	    fprintf(fptr, "%s", pkginfo);
	    fprintf(fptr, "%s", "       ");
		char time[80];
	    strcat(time,ctime(&t));
	    
	    
	    char temp[5]="2022";
	    int count =0;
	    int i=0;
	    for(;i<80;i++)
	    {
	    	if(count==4)
	    		break;
	    	if(time[i]==temp[count])
		    	count++;
		else
			count = 0;
		    	
	    }
	    time[i]='\0';
	    strcat(time,"    ");
	    strcat(time,arr);
	    fprintf(fptr, "%s", time);

	    
	  
	    // exiting program 
	    if (fptr == NULL) 
	    {
		printf("Error!");
		exit(1);
	    }
	    fprintf(fptr, "%s", "\n");
	    //fprintf(fptr, "%s", arr);
	    fclose(fptr);
		
}
void func(int connfd)
{
	char buffmain[MAX],bufftemp[MAX];
	char reply[MAX]="Registration By ";
	int n;
	for(int j=0; j<5; j++)
	{
	reply[0]='\0',buffmain[0]='\0',bufftemp[0]='\0';

		for(int i=0; i<6; i++)
		{
		bzero(bufftemp, MAX);
		// read the message from client and copy it in buffer
		read(connfd, bufftemp, sizeof(bufftemp));
		if(i>1 && i<3)
		strcat(buffmain,"-");
		else
		strcat(buffmain,"       ");
		strcat(buffmain,bufftemp);
		}
		// print buffer which contains the client contents
		printf("\nServer Recieved: %s\t: ", buffmain);
		
		filewrite(buffmain,bufftemp);
		
		strcat(reply,buffmain);
		write(connfd, reply, sizeof(reply));
		
	}
	
}

// Driver function
int main()
{
	int sockfd, connfd, len;
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
