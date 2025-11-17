#ifndef SENDER_HANDLER_H
#define SENDER_HANDLER_H

/*
 * PSEUDOCODE:
 * 
 * HEADER FILE: sender_handler.h
 * PURPOSE: Define interface for sending handler
 * 
 * IFNDEF SENDER_HANDLER_H
 * DEFINE SENDER_HANDLER_H
 * 
 * DECLARE:
 *     FUNCTION sender_handler(void *arg) RETURNS void*
 *     // Function to start the sending handler thread
 * 
 * ENDIF
 */

// Function to start the sending handler thread
void *sender_handler(void *arg);

#endif
