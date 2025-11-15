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

// messages all clients a message
void messageAllClients(Client *headPtr, MessageStruct messageToSend)
{
    Client *curPtr = headPtr;

    while (curPtr != NULL)
    {
        int currentSocket = curPtr.socket // need to hold socket in client list
        sendMessage(currentSocket, &messageToSend, sizeof(messageToSend));
        curPtr = curPtr->nextClientPtr;
    }
}

// messages all clients besides ip and port given in parameters
void messageAllClientsExcept(Client *headPtr, MessageStruct msgToSend, char avoidIP[20], char avoidPort[8])
{
    Client *curPtr = headPtr;

    while (curPtr != NULL)
    {
        int currentSocket = curPtr.socket // need to hold socket in client list
        if ( !(compareString(curPtr->headClient.ip, avoidIP) == 0 &&
               compareString(curPtr->headClient.port, avoidPort) == 0) )
        {
            sendMessage(currentSocket, &messageToSend, sizeof(messageToSend));
        }
        
        curPtr = curPtr->nextClientPtr;
    }
}