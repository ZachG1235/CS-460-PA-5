// skeleton
#include "client_handler.h"

/*
 * Big switch case function. Given a message, be able to decide 
 * what to do given a MessageStruct
*/
void handleClient(MessageStruct messageToHandle, int socket, Client *headPtr)
{
    // switch case on enum in messageToHandle's struct
    char clientIP[20] = messageToHandle.senderInfo.ip;
    char clientPort[8] = messageToHandle.senderInfo.port;
    char clientName[255] = messageToHandle.senderInfo.name;
    switch (messageToHandle.msgType)
    {
        // if enum is JOIN
        case JOIN:
            /* message all current clients in server's linked list 
            /* that a new client has joined */
            messageAllClients(headPtr, messageToHandle);
            // add client to linked list of clients
            addChatNode(*headPtr, clientIP, clientPort, clientName);
        // if enum is LEAVE
        case LEAVE:
            // remove client from linked of clients
            removeChatNode(*headPtr, clientIP, clientPort);
            /* mesage all current clients in server's linked list
            /* that the client has left*/
            messageAllClients(headPtr, messageToHandle);
        // if enum is SHUTDOWN
        case SHUTDOWN:
            // check if message in MessageType == "ALL"
                // inform all clients that the server is shutting down
                // remove all clients from linked list. 
                // close all connections with all clients
                // terminate the application
            // otherwise, MessageType is not "ALL" (client is only shutting down)
                // remove client from linked of clients
                /* mesage all current clients in server's linked list
                /* that the client has left*/
                // AS A NOTE: Client will handle shutting down their application
        // if enum is NOTE
        case NOTE:
            // iterate through linked list of clients
                /* if client is NOT the one who send the note,
                /* then use send over the note to the clients. */
            messageAllClientsExcept(headPtr, messageToHandle, clientIP, clientPort);
        // otherwise, enum is invalid
        default:
            // show error in console. 
            printf("There was an error handling a message.\n");
    }
}

int countClients(Client* headPtr)
{
    int count = 0;
    Client* curPtr = headPtr;
    while (curPtr != NULL) {
        count++;
        curPtr = curPtr->nextClientPtr;
    }
    return count;
}

// messages all clients a message
void messageAllClients(Client *headPtr, MessageStruct messageToSend)
{
    Client *curPtr = headPtr;
    int threadCount = countClients(headPtr);
    pthread_t threads[threadCount];
    int curThreadIndex = 0;
    while (curPtr != NULL)
    {
        // malloc the struct (it's going to be free'd in the thread)
        MessageStruct *threadMsgArg = malloc(sizeof(MessageStruct))

        // copy over information in struct
            // TODO: Not confident here. Please look over copying.
        threadMsgArg->msgType = msgToSend.msgType;
        threadMsgArg->senderInfo = msgToSend.senderInfo;
        copyString(threadMsgArg->senderInfo.ip, msgToSend.senderInfo.ip);
        copyString(threadMsgArg->senderInfo.port, msgToSend.senderInfo.port);
        copyString(threadMsgArg->senderInfo.name, msgToSend.senderInfo.name);
        copyString(threadMsgArg->msgContent, msgToSend.msgContent)


        pthread_create(&threads[curThreadIndex], NULL, sendOnThread, &msgToSend);
        curThreadIndex += 1;
        
        curPtr = curPtr->nextClientPtr;
    }

    // wait for threads to finish
    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL)
    }
}

// messages all clients besides ip and port given in parameters
void messageAllClientsExcept(Client *headPtr, MessageStruct msgToSend, char avoidIP[20], char avoidPort[8])
{
    Client *curPtr = headPtr;
    int threadCount = countClients(headPtr);
    pthread_t threads[threadCount];
    int curThreadIndex = 0;
    while (curPtr != NULL)
    {
        if ( !(compareString(curPtr->headClient.ip, avoidIP) == 0 &&
               compareString(curPtr->headClient.port, avoidPort) == 0) )
        {
            // malloc the struct (it's going to be free'd in the thread)
            MessageStruct *threadMsgArg = malloc(sizeof(MessageStruct))

            // copy over information in struct
                // TODO: Not confident here. Please look over copying.
            threadMsgArg->msgType = msgToSend.msgType;
            threadMsgArg->senderInfo = msgToSend.senderInfo;
            copyString(threadMsgArg->senderInfo.ip, msgToSend.senderInfo.ip);
            copyString(threadMsgArg->senderInfo.port, msgToSend.senderInfo.port);
            copyString(threadMsgArg->senderInfo.name, msgToSend.senderInfo.name);
            copyString(threadMsgArg->msgContent, msgToSend.msgContent)


            pthread_create(&threads[curThreadIndex], NULL, sendOnThread, &msgToSend);
            curThreadIndex += 1;
        }
        
        curPtr = curPtr->nextClientPtr;
    }

    // wait for threads to finish
    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL)
    }
}

void *sendOnThread(void* arg)
{
    MessageStruct* msgToSend = arg;

    int newChatSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (newChatSocket < 0)
    {
        perror("socket");
        return NULL;
    }
    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(atoi(msgToSend->senderInfo.port));
    inet_pton(AF_INET, msgToSend->senderInfo.ip, &clientAddr.sin_addr);

    if (connect(newChatSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) < 0)
    {
        perror("connect");
        close(newChatSocket);
        return NULL;
    }

    sendMessage(newChatSocket, msgToSend, sizeof(MessageStruct));

    close(newChatSocket);

    free(msgToSend);

    return NULL;

}