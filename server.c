#include "server.h"
#include <sys/socket.h>


int server_init(void) {  
    // We open a socket local connection
    int server_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    return server_fd;
}

