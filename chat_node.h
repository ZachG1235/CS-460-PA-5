// skeleton
#ifndef CHAT_NODE_H
#define CHAT_NODE_H


//IP, port and logical name

struct ChatNode{
    char ip[16];
    int port;
    char name[255];
};
// Struct *client (linked list)
// client: head_client
// *client: next_client_ptr
struct Client{
    ChatNode headClient;
    Client *nextClientPtr;
};

// have code in place that implements linked lists for chat nodes. 

// add chat node
int addChatNode(Client headClient, char ip[], int port, char name[]);

// remove chat node
int removeChatNode(Client headClient, char ip[], int port);



#endif