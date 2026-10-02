# Rules for the V1 contract protocol between the client and the server.

REGISTER 
    client_id
    timeout
HEARTBEAT (always a simple binary ping that the client send to the server to alert that is alive)

The HEARTBEAT allow to update `last_seen`and `state` variables calculating with the registered `timeout`