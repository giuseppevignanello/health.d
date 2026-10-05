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

#define COMMAND_CAPACITY 3 //the number of tokens passable as CLI param

#if defined(__APPLE__)
    #define SOCKET_PATH "/tmp/healthd.sock" 
#else 
    #define SOCKET_PATH "/run/healthd.sock" 
#endif

/* A simple string split with space as delimeter  */
char** parse_command(char *command) {
   int capacity = COMMAND_CAPACITY;  
   int n_tokens = 1; 
   char **tokens = malloc(capacity * sizeof(char*));   
   
   char *token = strtok(command, " ");
   tokens[0] = token;    

   while(command != NULL) {       
      char *token = strtok(NULL, " ");
      tokens[n_tokens] = token;  
   }
   
   return tokens;  
}

int open_socket(void) {
  //open the test client connection
  //TODO: check if a connection isn't already opened
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


int register_socket(char* message_type) {
        
}


int main(int argc, char **argv) {

    if(argc < 2) {
       printf("Right use: %s <file_name>\n", argv[0]);
       return 1; 
    }

    if(strcmp(argv[1], "OPEN SOCKET") == 0) { 
      return open_socket();
    } 
    
    char** parsed_commands = parse_command(argv[1]);

    printf("%s", parsed_commands[0]); 
    printf("%s", parsed_commands[1]);       
}


