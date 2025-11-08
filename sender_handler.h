#ifndef SENDER_HANDLER_H
#define SENDER_HANDLER_H

/*
 * Header file for message sender module.
 * Defines interface for handling outgoing user messages in separate thread.
 * Manages user input processing and chat protocol formatting.
 */

// Function to start the sending handler thread
void *sender_handler(void *arg);

#endif
