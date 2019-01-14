// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <fcntl.h>
#include "Dynamic_library.h"
#include <time.h>
#define PORT 8080 

char* get_time(time_t current_time)
{
	char* time_string = ctime(&current_time);
	if(current_time == ((time_t) -1))
		return "Error!";
	return time_string;
}


int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *msg = "msg from server"; 
	FILE *fp;
	time_t current_time;
    char* time_string;
	char* msg_t_c;
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE);
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 

	valread = read(new_socket , buffer, 1024); 
	printf("%s\n",buffer ); 

	//wite to file
	fp = fopen("test.txt", "a+");
	if(fp == NULL)
		printf("Error opening file\n");

	current_time = time(NULL);
	time_string = get_time(current_time);
	msg_t_c = strcat(time_string, buffer);
	fprintf(fp, "%s\n\n", msg_t_c);
	fclose(fp);


	//send message back to client
	send(new_socket , msg_t_c , strlen(msg_t_c) , 0 ); 
	printf("Message Sent\n");

	return 0; 
} 
