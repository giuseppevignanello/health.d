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
#define MAX_C_P_N 50 // The max chars for the process name

#if defined(__APPLE__)
    #define SOCKET_PATH "/tmp/healthd.sock" 
#else 
    #define SOCKET_PATH "/run/healthd.sock" 
#endif

 int open_socket(void) {
  //open the test client connection
  //TODO: check if a connection isn't already opened
    int fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(fd < 0) {
       perror("socket"); 
       return -1; 
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX; //copy the family
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", SOCKET_PATH); //copy the path    

    if(connect(fd,(struct sockaddr *)&addr, sizeof(addr)) < 0) {
       perror("connect");
       close(fd);
       return -1;  
    };
    
    printf("Connection opened\n");

    return fd;
}


//Write the message for the server
int send_message(int fd, const char* command) {
   ssize_t bytes_sent = write(fd, command, strlen(command));
  
   if(bytes_sent < 0) {
      perror("write");
      return -1;
   }
}

int read_message(void) {
    return 0; 
}

int validate_name(const char* name) {
    if(name == NULL || name[0] == '\0') {
       printf("%s", "Error: The process name is null or empty\n");
       return -1;
    }

    if(strlen(name) > MAX_C_P_N ) {
       printf("%s", "Error: The name is too long ");
       return -1;
    }

    //To do: check for special chars

    return 0;
}


int main(int argc, char **argv) {

    if(argc > 3) {
       printf("Right use: %s <file_name>\n", argv[1]);
       return 2; 
    }

    int fd = open_socket();

    if(fd < 0) {
       return 1;
    }

    int val_res = 0; 
   
    if(strcmp(argv[1], "REGISTER") == 0 || strcmp(argv[1], "HEARTBEAT") == 0) {
      
      val_res = validate_name(argv[2]);
      
      if (val_res < 0 ) {
       	 return val_res;   
      };

      //build the message for the server
      char message[100]; 
      snprintf(message, sizeof(message), "%s %s", argv[1], argv[2]);

      int sm_resp = send_message(fd, message);
      if(sm_resp < 0) {
         return sm_resp;
      }
      int rm_resp = read_message();
    } else {
      printf("%s","Command not found"); 
    }    
}


