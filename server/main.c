// full code

/* server main file requirements:
detailed code, won't need any more work.
reads properties, then
implements the server loop.
*/
#include "main.h"

// initialize variables
    // file descriptor for listening socket 
static int globalListenFileDesc = -1;
    // variable to store if a shutdown is requested
static volatile sig_atomic_t shutdownRequested = 0;
    // head ptr for linked list of connected clients
static Client* clientListHead = NULL;

int main()
{
    // load server properties
    Properties* props = property_read_properties("server.properties");

    // get the port number property from the property file
    char* portVal = property_get_property(props, "PORT");
    int port = atoi(portVal);

    // prepare server-wide variables
    initializeGlobalState();

    // create a listening tcp socket 
    int listenFd = createListeningSocket(port);
    globalListenFileDesc = listenFd;

    // main server loop; accepts and handles clients
    acceptLoop(listenFd);

    // close the listening socket before exiting
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

    // create a tcp socket
    socketFileDesc = socket(AF_INET, SOCK_STREAM, 0);
        // error handle
    if (socketFileDesc < 0)
    { 
        perror("socket"); 
        exit(EXIT_FAILURE); 
    }

    // allow the socket to reuse the address after closing
    int opt = 1;
    setsockopt(socketFileDesc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // prepare the server address struct
    struct sockaddr_in serveraddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
        // accept connections from any interface 
    servaddr.sin_addr.s_addr = INADDR_ANY;
        // convert port to network byte order
    servaddr.sin_port = htons(port);

    // bind socket to specified address and port.
    if (bind(socketFileDesc, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        close(socketFileDesc);
        exit(EXIT_FAILURE);
    }

    // start listening to incoming connections
    if (listen(socketFileDesc, BACKLOG) < 0)
    {
        perror("listen");
        close(socketFileDesc);
        exit(EXIT_FAILURE);
    }

    // return the file descriptor of listening socket
    return socketFileDesc;
}

// server accept loop
void acceptLoop(int listenSocketFileDesc)
{
    while (!shutdownRequested)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        // block until a new client connects
        int clientFileDesc = accept(listenSocketFileDesc, 
                                          (struct sockaddr*)&clientAddr, 
                                                                    &clientLen);
        // error handling
        if (clientFileDesc < 0)
        {
            if (errno == EINTR && shutdownRequested)
            {
                break;
            }
            perror("accept");
            continue;
        }

        // log the connection details 
        printf("Accepted connection from %s:%d\n",
                    inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        
        // create a thread to handle the new client
        pthread_t tid;
        int* arg = malloc(sizeof(int));
        *arg = clientFileDesc;

        // create the actual thread 
        pthread_create(&tid, NULL, (void* (*)(void*))handleIncomingMessage, 
                                                                           arg);
        pthread_detach(tid);
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
        // send message to big switch-case handler
        handleClient(msg, clientFileDesc);
    }

    // client disconnected or error
    printf("Client on socket %d disconnected.\n", clientFileDesc);
    
    // remove client from client list 
    removeChatNode(clientFileDesc);
    close(clientFileDesc);
}

// shutdown handling
void initiateShutdown()
{
    // notify server to stop accepting clients
    shutdownRequested = 1;

    // close the listening socket 
    if (globalListenFileDesc != -1)
    {
        close(globalListenFileDesc);
        globalListenFileDesc = -1;
    }

    // close all client sockets
    ChatNode* curr = clientListHead;
    while (curr)
    {
        close(curr->socket);
        curr = curr->next;
    }

    // clear client list to reset state
    clientListHead = NULL;
}

// add client to linked list (linked list lives in this file)
void addClient(ChatNode clientChatNode)
{
    // add to linked list with aux function in chat_node.c
    addChatNode(clientListHead, clientChatNode.ip, 
                                      clientChatNode.port, clientChatNode.name);
}