#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>
#include <stdio.h>

#if defined(__APPLE__)
    #define SOCKET_PATH "/tmp/healthd.sock" 
#else 
    #define SOCKET_PATH "/run/healthd.sock" 
#endif

int main(void) {

    //open the test client connection
    int fd = socket(PF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX; //copy the family
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", SOCKET_PATH); //copy the path    

    if(connect(fd,(struct sockaddr *)&addr, sizeof(addr)) < 0) {
       perror("connect");
       close(fd); 
    };
    
     printf("Connection opened/n");

    return 0;
}
