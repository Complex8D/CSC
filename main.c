#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <poll.h>



int main(int argc, char *argv[])
{
    int main_socket;
    uint16_t PORT;
    int i;
    int binds;
    int queue;
    int listens;
    int new_socket;

    struct sockaddr_in server, *p; 

    i = 1;
    PORT = 8080;
    memset(&server, '0', sizeof(server)); 
    p=&server;
    p->sin_family = AF_INET;
    p->sin_port = htons(PORT);
    p->sin_addr.s_addr = INADDR_ANY;
    queue = 5;
    
    
    
    main_socket = socket(p->sin_family, SOCK_STREAM, 0);
    if(main_socket < 0)
    {
        fprintf(stderr, "unable to create socket, returned %d\n", main_socket);
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "socket created\n");

    if (setsockopt(main_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &i, sizeof(i))) 
	{ 
        fprintf(stderr, "setsockopt caused a crash\n");
	    exit(EXIT_FAILURE); 
	} 

   

    if(bind(main_socket, (struct sockaddr *)p, sizeof(server)) < 0)
        {    
            fprintf(stderr, "Unable to bind socket to port %d, returned %d\n", PORT, binds);
            exit(EXIT_FAILURE);
        }

    fprintf(stderr, "socket bound on port %d\n", PORT);
    
    if(listens = listen(main_socket, queue) < 0)
    {
        fprintf("listen error, returned %d\n", listens);
        exit(EXIT_FAILURE);
    }

    // while(1)


    if(new_socket = accept(main_socket, (struct sockaddr_in *)p, (socklen_t *)p))
    {
        fprintf(stderr, "accept error, retuned %d\n");
        exit(EXIT_FAILURE);
    }









    return 1;
}