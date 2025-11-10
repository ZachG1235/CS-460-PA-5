// full code

/* server main file requirements:
detailed code, won't need any more work.
reads properties, then
implements the server loop.
*/
#include "main.h"


static int globalListenFileDesc = -1;
static volatile sig_atomic_t shutdownRequested = 0;

static ChatNode* clientListHead = NULL;

int main()
{
    // Load server properties
    Properties* props = property_read_properties("server.properties");

    char* portVal = property_get_property(props, "PORT");
    int port = atoi(portVal);

    initializeGlobalState();

    int listenFd = createListeningSocket(port);
    globalListenFileDesc = listenFd;

    acceptLoop(listenFd);

    close(listenFd);
    return 0;
}

// prepare server data structures
void initializeGlobalState()
{
    // initialize data structs
    clientListHead = NULL;
}

// create the listening socket
int createListeningSocket(int port)
{
    // creates tcp socket, binds, and listens
    int socketFileDesc;

    socketFileDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDesc < 0)
    { 
        perror("socket"); 
        exit(EXIT_FAILURE); 
    }

    int opt = 1;
    setsockopt(socketFileDesc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serveraddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(socketFileDesc, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        close(socketFileDesc);
        exit(EXIT_FAILURE);
    }

    if (listen(socketFileDesc, BACKLOG) < 0)
    {
        perror("listen");
        close(socketFileDesc);
        exit(EXIT_FAILURE);
    }

    return socketFileDesc;
}

// server accept loop
void acceptLoop(int listenSocketFileDesc)
{
    while (!shutdownRequested)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        int clientFileDesc = accept(listenSocketFileDesc, 
                                          (struct sockaddr*)&clientAddr, 
                                                                    &clientLen);
        if (clientFileDesc < 0)
        {
            if (errno == EINTR && shutdownRequested)
            {
                break;
            }
            perror("accept");
            continue;
        }

        printf("Accepted connection from %s:%d\n",
                    inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        pthread_t tid;
        int* arg = malloc(seizeof(int));
        *arg = clientFileDesc;
        pthread_create(&tid, NULL, (void* (*)(void*))handleIncomingMessage, arg);
        pthread_detach(tid);

        close(clientFileDesc);
    }
}

void handleIncomingMessage(int clientFileDesc)
{
    int clientFileDesc = *clientFdPtr;
    // clears thread mem
    free(clientFdPr); 

    MessageStruct msg;
    ssize_t bytesRead;

    // Keep receiving messages until the client disconnects
    while ((bytesRead = receiveMessage(clientFileDesc, 
                                              &msg, sizeof(MessageStruct))) > 0)
    {
        // Hand off message to the big switch-case handler
        handleClient(msg, clientFileDesc);
    }

    printf("Client on socket %d disconnected.\n", clientFileDesc);
    removeClient(clientFileDesc);
    close(clientFileDesc);
}

// shutdown handling
void initiateShutdown()
{
    // close listening socket
    shutdownRequested = 1;
    if (globalListenFileDesc != -1)
    {
        close(globalListenFileDesc);
        globalListenFileDesc = -1;
    }

    // Close all client sockets
    ChatNode* curr = clientListHead;
    while (curr)
    {
        close(curr->socket);
        curr = curr->next;
    }

    clientListHead = NULL;
}

