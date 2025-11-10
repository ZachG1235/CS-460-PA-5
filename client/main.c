// full code
#include "client.h"

/* client main file requirements:
detailed code that is kicking off a client.
    reading properties
    then starting the two threads
    that implement both the sending and the receiving side
    with respect to the server
should be fully functional,
only need a little tweaking as a result of debugging.
*/

static pthread_t senderThread;
static pthread_t receiverThread;

extern void *sender_main_loop(void *arg);
extern void *receiver_main_loop(void *arg);

// connect client to server
int connectToServer(const char *ip, int port) {
    // variables
    int sockfd;
    struct sockaddr_in serverAddr;

    // create tpc cocket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket"); // print error if cannot
        return -1;
    }

    // configure server addrtess structure
    // IPv4
    serverAddr.sin_family = AF_INET; 
    //cinvert port
    serverAddr.sin_port = htons(port);

    // convert ip into binary format
    if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sockfd);
        return -1;
    }

    // connect :)
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }

    // return socket if successful
    return sockfd;
}

// 
void *senderFunc(void *arg) {
    int serverFd = *(int *)arg;   // get socket file descriptor
    char buffer[1024];            // message buffer

    while (1) {
        // Read user input (line-based)
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;

        // If user types "/quit", close the connection
        if (strncmp(buffer, "/quit", 5) == 0)
            break;

        // Send the message to the server
        send(serverFd, buffer, strlen(buffer), 0);
    }

    // Gracefully shut down sending side of the socket
    shutdown(serverFd, SHUT_WR);
    return NULL;
}