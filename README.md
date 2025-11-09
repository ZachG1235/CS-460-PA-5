# CS-460 Programming Assignment 5.2 — Chat Outline

A simple multi-client **Chat Application** written in **C** using **POSIX sockets** and **pthreads**.  
The system includes both a **server** and multiple **clients** that communicate via TCP sockets.

**Team Members:**  
Risa • Avnish • Zach • Sage

---

## 📘 Project Overview

This assignment implements a **networked chat system** from scratch.  
It demonstrates understanding of **client-server communication**, **message protocols**, and **multithreading** in C.

The **Server** acts as a central hub.  
The **Clients** can:
- **JOIN** the chat.
- **LEAVE** the chat.
- Send **NOTEs** (messages) to all other connected clients.
- **SHUTDOWN** their own session.
- **SHUTDOWN ALL** clients and the server.

---

## 🧩 Features

### Server
- Handles multiple clients using threads.
- Maintains a list of active chat participants.
- Forwards NOTES, JOIN, and LEAVE messages appropriately.
- Responds to SHUTDOWN and SHUTDOWN ALL commands.

### Client
- Reads server information (IP & Port) from a `.properties` file.
- Runs two threads:
  - **Sender Thread** → processes user commands and sends messages.
  - **Receiver Thread** → receives and displays messages from the server.
