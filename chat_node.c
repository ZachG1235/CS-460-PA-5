// skeleton
// header files
#include "chat_node.h"  



// have code in place that implements linked lists for chat nodes. 

// add chat node
int addChatNode(Client **ClientList, char ip[], char port[], char name[])
{

    // Create and fill chat node struct
    Client *newNode = malloc(sizeof(Client));
    if (!newNode) return 0; // malloc failed
    // add chat node struct
    
    snprintf(newNode->chatNode.ip, sizeof(newNode->chatNode.ip), "%s", ip);
    snprintf(newNode->chatNode.port, sizeof(newNode->chatNode.port), "%s", port);
    snprintf(newNode->chatNode.name, sizeof(newNode->chatNode.name), "%s", name);
    newNode->nextClientPtr = NULL;

    // check if theres no list
    if (*ClientList == NULL) {
        *ClientList = newNode;
        return 1;
    }

    // if theres a list, iterate to the last node
    Client *curClient = *ClientList;
    while (curClient->nextClientPtr != NULL) {
        curClient = curClient->nextClientPtr;
    }

    // Append new node
    curClient->nextClientPtr = newNode;

    return 1;
}
// remove chat node
int removeChatNode(Client **ClientList, char ip[], char port[])
{
    // check if theres no list
    if (*ClientList == NULL) return 0;

    // useful vars :)
    Client *curClient = *ClientList;
    Client *prev = NULL;

    // iterate through client until ip and port are same
    while (curClient != NULL &&
           (strcmp(curClient->chatNode.ip, ip) != 0 ||
            strcmp(curClient->chatNode.port, port) != 0))
    {
        prev = curClient;
        curClient = curClient->nextClientPtr;
    }

    if (curClient == NULL){
        return 0;
    }

    // check if theres only one element (no next node)
    if (prev == NULL) {
        // get rid of head
        *ClientList = curClient->nextClientPtr;
    }
    else{
        // get rid of client
        prev->nextClientPtr = curClient->nextClientPtr;
    }  

    // free current
    free(curClient);
    return 1;

}