// skeleton
#include "client_handler.h"

/*
 * Big switch case function. Given a message, be able to decide 
 * what to do given a MessageStruct
*/
void handleClient(MessageStruct messageToHandle, int socket)
{
    // switch case on enum in messageToHandle's struct
    // if enum is JOIN
        /* message all current clients in server's linked list 
        /* that a new client has joined */
        // add client to linked list of clients
    // if enum is LEAVE
        // remove client from linked of clients
        /* mesage all current clients in server's linked list
        /* that the client has left*/
    // if enum is SHUTDOWN
        // check if message in MessageType == "ALL"
            // inform all clients that the server is shutting down
            // remove all clients from linked list. 
            // close all connections with all clients
            // terminate the application
        // otherwise, MessageType is not "ALL" (client is only shutting down)
            // remove client from linked of clients
            /* mesage all current clients in server's linked list
            /* that the client has left*/
            // AS A NOTE: Client will handle shutting down their application
    // if enum is NOTE
        // iterate through linked list of clients
            /* if client is NOT the one who send the note,
            /* then use send over the note to the clients. */
    // otherwise, enum is invalid
        // show error in console. 
}