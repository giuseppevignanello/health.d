#ifndef STATE_H 
#define STATE_H
#include <time.h>

// The possible states of health.
typedef enum {
    STATE_HEALTHY,
    STATE_UNHEALTHY,
    STATE_UNKNOWN
} State;

typedef struct {
    char id[50]; 
    State health_state; 
    time_t last_seen; 
    int timeout;

} Client;

Client *register_client(const char *id, int timeout);
void heartbeat(Client *client); 
void check_timeout(Client *client); 
void unregister_client(Client *client); 
void find_client(Client *client); 



#endif // STATE_H
