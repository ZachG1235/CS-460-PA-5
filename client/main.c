// full code

/* client main file requirements:
detailed code that is kicking off a client.
    reading properties
    then starting the two threads
    that implement both the sending and the receiving side
    with respect to the server
should be fully functional,
only need a little tweaking as a result of debugging.
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

    initialize_global_state();

    int listen_fd = create_listening_socket(port);
    accept_loop(listen_fd);

    close(listen_fd);
    return 0;
}

// aaaaa

int main() {
    loadClientProperties();
}

// connect to server
int connectToServer(const char ip, int port) {
    // creates tcp socket and connects to server
    // returns server socket fd
}

// initialize global state
void initializeClientState() {
    // sets up
        // joined = false
        // shutting_down = false
}

// start the sending thread
startSenderThread(int serverFd) {
    // 
}

// start the receiving thread
startReceiverThread(int serverFd) {
    // 
}

// wait for threads
void waitForThreads() {
    // join sender and receiver threads
}