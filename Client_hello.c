// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "Dynamic_library.h"
#define PORT 8080 


void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) 
	{
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}


int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char buffer[1024] = {0}; 
	char *full_message;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address / Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{   
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

	// get message
    printf("Enter message:\n");
	fgets(full_message, 1024, stdin);
	//printf("Message: %s\n", full_message);
	printf("\n");

	removeChar(full_message, '\n');

	// send to server
	send(sock , full_message , strlen(full_message) , 0 ); 

	// reciving from server
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer); 
	return 0;
	 
} 
