#ifndef RECEIVER_HANDLER_H
#define RECEIVER_HANDLER_H

/*
 * Header file for message receiver module.
 * Defines interface for handling incoming server messages in separate thread.
 * Manages real-time message display and server command processing.
 */

// Function to start the receiving handler thread
void *receiver_handler(void *arg);

#endif
