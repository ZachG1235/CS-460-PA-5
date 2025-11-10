// def
#ifndef client_main_h
#define client_main_h

/* additional libraries */
#include "properties.h"
#include "sender_handler.h"
#include "receiver_handler.h"
#include "message.h"
#include "chat_node.h"

#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BACKLOG 10

/* ===== function prototypes ===== */

// Establishes TCP connection to the chat server (called by sender_handler.c)
static int connectToServer(const char *ip, int port);

// Launches the sender thread (user command processing)
static void startSenderThread(int serverFileDesc);

// Launches the receiver thread (server message handling)
static void startReceiverThread(int serverFileDesc);

// Waits for both threads to complete
static void waitForThreads();

#endif // client_main_h