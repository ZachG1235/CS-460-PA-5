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

extern void *sender_main_loop(void *arg);
extern void *receiver_main_loop(void *arg);

int main()
{
    // Load client properties
    Properties* props = property_read_properties("client.properties");

    char* ipVal   = property_get_property(props, "SERVER_IP");
    char* portVal = property_get_property(props, "SERVER_PORT");
    char* nameVal = property_get_property(props, "CLIENT_NAME");

    int port = atoi(portVal);

    initializeClientState(nameVal);

    int serverFd = connectToServer(ipVal, port);

    startSenderThread(serverFd);
    startReceiverThread(serverFd);

    waitForThreads();
    cleanup(serverFd);

    return 0;
}

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
void startSenderThread(int serverFd) {
}

// start the receiving thread
void startReceiverThread(int serverFd) {
}

// wait for threads
void waitForThreads() {
    // join sender and receiver threads
}