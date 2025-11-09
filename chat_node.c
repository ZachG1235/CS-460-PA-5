// skeleton
// header files
#include "chat_node.h"  



// have code in place that implements linked lists for chat nodes. 



// add chat node
int addChatNode(Client *headClient, char ip[], int port, char name[]){
    // set info into variables
    // add chat node struct
    // check if theres a list
        // set current client as head
            // iterate through list until next client is null
            // add struct as thge next client
    // if theres no elements
        // set struct as head
}
// remove chat node
int removeChatNode(Client *headClient, char ip[], int port){
    // iterate through client until ip and port are same
    // check if theres only one element (no next node)
        // remove head node
    // if there is a next node
        // set prev node's next node as current's next node
    // free current


}