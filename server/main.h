// def
#ifndef server_main_h
#define server_main_h

/* additional libraries */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "../properties.h"   // for properties functions
#include "../chat_node.h"    // for ChatNode file types

#define BACKLOG 10


/* ===== function prototypes ===== */
// function to prepare global data structures
void initializeGlobalState();

// function to create a listening socket for incoming clients
int createListeningSocket(int port);

// function to create threads for clients 
void acceptLoop(int listenSocketFileDesc);

// thread to handle incoming message. calls handleClient in client_handler.c
void handleIncomingMessage(int clientFileDesc)

// handles shutdown of server
void initiateShutdown();

// adds client to linked list (needs to exist in main)
void addClient(ChatNode clientChatNode);

#endif // server_main_h