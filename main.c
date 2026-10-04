#include <stdlib.h> 
#include <stdio.h>
#include <sys/socket.h>
#include "server.h"
#include "state.h"


int main(void) {
    // init the server and get the file descriptor
    int server_fd = server_init(); 
    
    if(server_fd < 0) {
       return 1;  
    }

    printf("Server initialized: %d\n", server_fd);

    int client_fd = accept(server_fd, NULL, NULL); 

    if(client_fd < 0) {
       perror("accept");
       return 1; 
    }

    printf("Client connected: %d\n", client_fd);

    close(client_fd); 
    close(server_fd);  
   
    //For the moment we can close directly 'cause we are just testing
    return 0; 
}
