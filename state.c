#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"

// Initialize the client structure with the register default values;.
Client *register_client(const char *id, int timeout){
    Client *client = malloc(sizeof(Client));
    
    if(!client) return NULL; 

    strncpy(client->id, id, sizeof(client->id) - 1);
    client->id[sizeof(client->id) - 1] = '\0';

    client->health_state = STATE_UNKNOWN;
    client->last_seen = time(NULL);
    client->timeout = timeout;
    return client;
}

// Set the last seen time to the current time.
void heartbeat(Client *client){
    client->last_seen = time(NULL);
}

// Check if the client has timed out and update its health state accordingly.
void check_timeout(Client *client) {
    if(difftime(time(NULL), client->last_seen) > client->timeout) {
        client->health_state = STATE_UNHEALTHY; 
    }
}

// Unregister the client deleting its resources from memory
void unregister_client(Client *client) {
    free(client);
    // TODO: we should remove the client also from any persistent storage 
}

// Find the client by client_id 
// TODO: implement this
Client *find_client (const char *id) {
   //implement the logic to find the object in memory. Actually this should be an optimized search algorithm
   return NULL;       
}
