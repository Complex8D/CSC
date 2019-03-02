#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 8080
#define MAXLENGTH 2001

void *get_in_addr(struct sockaddr *sa)
{
    if(sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int socketfd;
    int connect_status;
    int respons;
    int binding;
    int listening;
    int n_socketfd;
    int recvi;
    int opt;

    struct sockaddr_in serv_addr, *p;
    struct addrinfo *servinfo;

    char* msgtc;
    char address[INET6_ADDRSTRLEN];

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    opt = 1;
    p=&serv_addr;

    socketfd = socket(p->sin_family, SOCK_STREAM, 0);
    if(socketfd == 0){
        printf("Unable to create socket\n");
        return -1;}




    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
        perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 



    if(bind(socketfd, (struct sockaddr *) p, sizeof(serv_addr)) < 0)
        {    
            printf("Unable to bind socket\n");
            return -1;
        }

      
    if (listen(socketfd, 3) < 0){
        printf("Listen error occured\n");
        return -1;}

    n_socketfd = accept(socketfd, (struct sockaddr *) p, (socklen_t*)p);
    /*if(n_socketfd < 0){
        printf("accept error occured\n");
        return -1;}
        */


    inet_ntop(serv_addr.sin_family, get_in_addr((struct sockaddr *)p), address, sizeof(address));

    recvi = recv(n_socketfd, msgtc, (MAXLENGTH -1), 0);
    printf("recived '%s' from %s\n", msgtc, address);

    return 1;
}