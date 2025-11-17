// skeleton
#ifndef clienthandler_h
#define clienthandler_h

#include "../message.h" // import message.h
#include "../StringUtils.c"
#include <pthread.h>
#include <arpa/inet.h>

/*
 * Big switch case function. Given a message, be able to decide 
 * what to do given a MessageStruct
*/
void handleClient(MessageStruct messageToHandle, int socket, Client *headPtr);

// counts how many clients are in the linked list
int countClients(Client* headPtr)

// messages all clients a message
void messageAllClients(Client *headPtr, MessageStruct messageToSend);

// messages all clients besides ip and port given in parameters
void messageAllClientsExcept(Client *headPtr, MessageStruct msgToSend, char avoidIP[20], char avoidPort[8]);

// threaded function to send to client
void *sendOnThread(void* arg);

#endif /* clienthandler_h */
