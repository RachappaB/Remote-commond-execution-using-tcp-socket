#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <sys/stat.h>
#include <arpa/inet.h>
#define MAX 800
#define PORT 8080
#define SA struct sockaddr

void some_error(char *buff)
{
	char name[]="Some error";
	int i =0;
	while(name[i]!='\0')
	{
		buff[i] =name[i];
		i++;
	}
	buff[i] = '\0';

}

void put_data_buff(char *buff)
{
	FILE *fp;
	fp = fopen("1.txt","r");

	if(fp ==NULL)
	{
		some_error(buff);
	}
	else{
		int i =0;
		 char ch;
    while ((ch = fgetc(fp)) != EOF)
	{
		*(buff+i) = ch;
		i++;
	}

	}
}
// Function designed for chat between client and server.
void func(int connfd)
{
	char buff[MAX];
	char addstring[] =" > 1.txt";
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		printf("From client: %s\t To client : ", buff);
		int i =0;
		for(i ;buff[i] != '\0';i++);
		for(int j =0;j<9;j++)
		{
			buff[i+j-1] = addstring[j];
		}
		buff[i+9-1] ='\0';
        system(buff);     
        printf(" To client : ");
		bzero(buff, MAX);
		n = 0;
		put_data_buff(buff);
		// copy server message in the buffer
		// while ((buff[n++] = getchar()) != '\n')
		// 	;

		// and send that buffer to client
		write(connfd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit > 1.txt", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
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
