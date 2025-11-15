// skeleton
#ifndef clienthandler_h
#define clienthandler_h

#include "../message.h" // import message.h
#include "../StringUtils.c"

/*
 * Big switch case function. Given a message, be able to decide 
 * what to do given a MessageStruct
*/
void handleClient(MessageStruct messageToHandle, int socket, Client *headPtr);

// messages all clients a message
void messageAllClients(Client *headPtr, MessageStruct messageToSend);

// messages all clients besides ip and port given in parameters
void messageAllClientsExcept(Client *headPtr, MessageStruct msgToSend, char avoidIP[20], char avoidPort[8]);

#endif /* clienthandler_h */
