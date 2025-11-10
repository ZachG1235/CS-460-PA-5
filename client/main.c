#include "main.h"

// Global thread handles
static pthread_t senderThread;
static pthread_t receiverThread;

int main()
{
    // load configuration from client.properties
    Properties* props = property_read_properties("client.properties");

    char* ipVal   = property_get_property(props, "SERVER_IP");
    char* portVal = property_get_property(props, "SERVER_PORT");
    char* nameVal = property_get_property(props, "CLIENT_NAME");
    int portInt = atoi(portVal);

    // initialize global client state
    ChatNode clientChatNode;
    clientChatNode.name = nameVal;

    // start sender and receiver threads
    startSenderThread(serverFileDesc);
    printf("You are ready to go!\n");

    // wait for both threads to complete
    waitForThreads();
    

    return 0;
}


// Establishes TCP connection to the chat server (called by sender_handler.c)
static int connectToServer(const char *ip, int port)
{
    int socketFileDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDesc < 0)
    {
        perror("error: socket()");
        return -1;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) <= 0)
    {
        perror("error: inet_pton()");
        close(socketFileDesc);
        return -1;
    }

    if (connect(socketFileDesc, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("error: connect()");
        close(socketFileDesc);
        return -1;
    }

    return socketFileDesc;
}


// Launches the sender thread (user command processing)
static void startSenderThread(int serverFileDesc)
{
    // get a ptr to serverFileDesc
    int *senServerFileDescPtr = malloc(sizeof(int));
    *senServerFileDescPtr = serverFileDesc;
    // call sender handler in thread
    if (pthread_create(&senderThread, NULL, senderHandler, senServerFileDescPtr) != 0)
    {
        perror("error: pthread_create(senderThread)");
        exit(EXIT_FAILURE);
    }
}

// Launches the receiver thread (server message handling)
static void startReceiverThread(int serverFileDesc)
{
    // get a ptr to serverFileDesc
    int *recServerFileDescPtr = malloc(sizeof(int));
    *recServerFileDescPtr = serverFileDesc;
    // make the thread
    if (pthread_create(&receiverThread, NULL, receiverHandler, &recServerFileDescPtr) != 0)
    {
        perror("error: pthread_create(receiverThread)");
        exit(EXIT_FAILURE);
    }
}

// Waits for both threads to complete
static void waitForThreads()
{
    pthread_join(senderThread, NULL);
    pthread_join(receiverThread, NULL);
}
