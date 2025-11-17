// skeleton
#ifndef CHAT_NODE_H
#define CHAT_NODE_H

#include <stdio.h>


//IP, port and logical name

typedef struct chatNodeStruct{
    char ip[20];
    char port[8];
    char name[255];
} ChatNode;

// Struct *client (linked list)
// client: head_client
// *client: next_client_ptr
typedef struct clientStruct{
    ChatNode chatNode;
    Client *nextClientPtr;
} Client;

// have code in place that implements linked lists for chat nodes. 

// add chat node
int addChatNode(Client **ClientList, char ip[], char port[], char name[]);

// remove chat node
int removeChatNode(Client **ClientList, char ip[], char port[]);



#endif