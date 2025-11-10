// full code

/* server main file requirements:
detailed code, won't need any more work.
reads properties, then
implements the server loop.
*/

#include "properties.h"
#include "main.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern void *talk_to_client(void *arg);

int main() {
    // Load server properties
    Properties* props = property_read_properties("server.properties");

    char* portVal = property_get_property(props, "PORT");
    int port = atoi(portVal);

    initializeGlobalState();

    int listenFd = createListeningSocket(port);
    acceptLoop(listenFd);

    close(listenFd);
    return 0;
}

// prepare server data structures
void initializeGlobalState() {
    // initialize data structs
}

// create the listening socket
int createListeningSocket(int port) {
    // creates tcp socket, binds, and listens
}

// server accept loop
void acceptLoop(int listenFd) {
    //
}

// shutdown handling
void initiateShutdown() {
    // close listening socket
}