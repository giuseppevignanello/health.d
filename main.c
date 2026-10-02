#include <stdlib.h> 
#include <stdio.h>
#include <sys/socket.h>
#include "server.h"
#include "state.h"


int main(void) {
    // init the server and get the file descriptor
    int server_fd = server_init(); 
    printf("Server initialized: %d\n", server_fd);
    return 0; 
}
