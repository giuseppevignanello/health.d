#include <sys/socket.h>
#include <stdio.h>
#include "server.h"

#if defined(__APPLE__)
    #define SOCKET_PATH= "/temp/healthd.sock"; 
#else 
    #define SOCKET_PATH= "/run/healthd.sock"; 

int server_init(void) {  
    // Opening the server side socket fot the local connection
    int fd = socket(PF_UNIX, SOCK_STREAM, 0);

    if(fd < 0) {
	perror("socket"); 
	return -1;
    }

    //the socket address
    struct sockaddr_un addr; 
    
    addr.sun_family = AF_UNIX; //copy the family
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", SOCKET_PATH) //copy the path 
   
    //Removing eventually previous connection
    unlink(SOCKET_PATH);

    //During the bunding the address type is casted from sockaddr_un to sockadrr
    if(bind(fd, struct sockaddr *)&addr ,sizeof(addr) < 0) {
        perror("bind"); 
	return -1; 
    };

    return server_fd;
}

