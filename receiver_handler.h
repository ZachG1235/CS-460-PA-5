#ifndef RECEIVER_HANDLER_H
#define RECEIVER_HANDLER_H

/*
 * PSEUDOCODE:
 * 
 * HEADER FILE: receiver_handler.h
 * PURPOSE: Define interface for receiving handler
 * 
 * IFNDEF RECEIVER_HANDLER_H
 * DEFINE RECEIVER_HANDLER_H
 * 
 * DECLARE:
 *     FUNCTION receiver_handler(void *arg) RETURNS void*
 *     // Function to start the receiving handler thread
 * 
 * ENDIF
 */

// Function to start the receiving handler thread
void *receiver_handler(void *arg);

#endif
