// def
#ifndef client_main_h
#define client_main_h

/* additional libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define BACKLOG 10

pthread_t senderThread, receiverThread;
/* ===== function prototypes ===== */
// connect to server
int connectToServer(const char ip, int port);

// start the sending thread
void startSenderThread(int serverFd);

// start the receiving thread
void startReceiverThread(int serverFd);

// wait for threads
void waitForThreads();

#endif // client_main_h