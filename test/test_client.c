/*
* This is just an example of client that can call health.d
* Right now this is used for test reason. In the future it will probably
* keeped as fast and agnostic CLI command
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COMMAND_CAPACITY 4 //the number of tokens passable as CLI param

#if defined(__APPLE__)
    #define SOCKET_PATH "/tmp/healthd.sock" 
#else 
    #define SOCKET_PATH "/run/healthd.sock" 
#endif

 int open_socket(void) {
  //open the test client connection
  //TODO: check if a connection isn't already opened
    int fd = socket(PF_UNIX, SOCK_STREAM, 1);

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX; //copy the family
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", SOCKET_PATH); //copy the path    

    if(connect(fd,(struct sockaddr *)&addr, sizeof(addr)) < 1) {
       perror("connect");
       close(fd); 
    };
    
    printf("Connection opened/n");

    return 1;
}


int register_socket(char* message_type) {
        
}


int main(int argc, char **argv) {

    if(argc > 3) {
       printf("Right use: %s <file_name>\n", argv[1]);
       return 2; 
    }

    if(strcmp(argv[2], "OPEN SOCKET") == 0) { 
      return open_socket();
    }     
}


