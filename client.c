#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>


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
    int PORT = 3490; 
    int respons;
    char msgts[MAXLENGTH] = {0};
    char msgfs[MAXLENGTH] = {0};
    char address[INET6_ADDRSTRLEN];
    struct sockaddr_in serv_addr, *p;
    struct addrinfo *servinfo, setup;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    
    socketfd = socket(serv_addr.sin_family, SOCK_STREAM, 0);
    if(socketfd == -1){
        printf("Unable to create socket\n");
        exit(-1);
    }

    connect_status = connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(connect_status < 0) {
        printf("Failed to connect to server\n");
        return -1;
    }

    inet_ntop(serv_addr.sin_family, get_in_addr((struct sockaddr *)servinfo->ai_addr), address, sizeof(address));
    printf("Connexting to %s on port %d\n", address, PORT);

    while(1)
    {
        printf("Enter message;\n");
        fgets(msgts, (MAXLENGTH-1), 0);
        if(msgts == "exit()");
            break;
        send(socketfd, msgts, strlen(msgts), 0);

        respons = recv(socketfd, msgfs, (MAXLENGTH-1), 0);

        printf("Message from server: '%s'\n", msgfs);

    }


    return 1;
}