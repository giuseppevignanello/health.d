#include <stdlib.h> 
#include <stdio.h>
#include <sys/socket.h>
#include "server.h"
#include "state.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>

char** split_str(char* str, int max_tokens) {
    char **params = malloc(max_tokens * sizeof(char*)); 
    char *token = strtok(str," " );
    int i = 0; 
    
    while(token != NULL && i < max_tokens) {
       params[i] = token; 
       token = strtok(NULL, " "); 
       i++; 
    } 

    return params; 
}



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
    
    char buffer[1024]; 

    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

    if(bytes_read < 0){
       perror("read"); 
       close(client_fd); 
       close(server_fd); 
       return 1;
    }

    if(bytes_read == 0) {
       printf("%s", "Client disconnected\n"); 
       close(client_fd); 
       close(server_fd); 
       return 0; 
    }
 
    //Add NULL terminator
    buffer[bytes_read] = '\0';
 
    printf("Received: %s\n", buffer); 
    
    char** params = split_str(buffer, 2);
  
  
    close(client_fd); 
    close(server_fd);  
   
    //For the moment we can close directly 'cause we are just testing
    return 0; 
}
