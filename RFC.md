# RFC: R-Type Multiplayer Game Network Protocol

## Status: Draft

**RFC Number:** 6969
**Title:** R-Type Multiplayer Game Network Protocol
**Author:** ETIB Corporation
**Version:** 1.1

## Abstract

This RFC outlines the network protocol for a multiplayer game inspired by R-Type. The protocol handles real-time communication between a server and multiple clients using TCP for initial connections and UDP for gameplay synchronization. It supports player actions, entity management, and efficient game state updates.

## Table of Contents

1. Introduction
2. Requirements
3. Message Structure
    1. Header
    2. Body
4. Protocol Design
    1. Connection Establishment
    2. Game State Synchronization
    3. Player Actions
    4. Server-to-Client Messages
    5. Client-to-Server Messages
5. Error Handling
6. Security Considerations
7. Future Work
8. References

## 1. Introduction

This document defines the multiplayer game protocol for a fast-paced side-scrolling shooter similar to R-Type. The protocol uses a hybrid of TCP and UDP to establish client-server communication, ensuring low latency during gameplay while maintaining reliability for critical messages.

## 2. Requirements

- Support for TCP for reliable initial connections and player identification.
- Support for UDP for low-latency, real-time communication during gameplay.
- Lightweight message structure to minimize network overhead.
- Entity and action synchronization across clients.
- Player identification and authentication via unique client IDs.

## 3. Message Structure

### 3.1. Header

The header contains essential information about each message, such as the client ID, the action type, and the length of the message body.

```cpp
struct Header {
    uint8_t MagicNumber;
    uint8_t EmitterID;
    uint8_t ReceiverID;
    uint8_t Action;
    uint32_t BodyLength;
};
```

- **MagicNumber**: A unique identifier to validate the message format.
- **EmitterID**: The ID of the client or server sending the message.
- **ReceiverID**: The ID of the client or server receiving the message.
- **Action**: The type of action being performed (e.g., input, entity update).
- **BodyLength**: The length of the message body in bytes.

### 3.2. Body

The body contains data specific to the action being performed, such as player inputs or entity state updates.

```cpp
#define BODY_LENGTH 1024

struct Body {
    uint8_t _buffer[BODY_LENGTH + 1];
};
```

Example message:
```cpp
header.MagicNumber = 0x77;
header.EmitterID = 0x01;
header.ReceiverID = 0x02;
header.Action = 0x01;  // NEW CONNECTION
header.BodyLength = 0;
body = NULL;
```

### Common Action Codes (0x01 -> 0x55)

| Action Code | Description    |
| ----------- | -------------- |
| 0x01        | NEW CONNECTION |
| 0x02        | INPUT          |

### Server-to-Client Action Codes (0x56 -> 0xAA)

| Action Code | Description |
| ----------- | ----------- |
| 0x56        | ROLLBACK    |
| 0x57        | UPDATE ECS  |

### Client-to-Server Action Codes (0xAA -> 0xFE)

| Action Code | Description |
| ----------- | ----------- |
| 0xAB        | USERNAME    |
| 0xAB        | USERNAME    |

### Both Magic Number (0xFF)

| Action Code | Description |
| ----------- | ----------- |
| 0xFF        | MAGIC_NUMBER|

## 4. Protocol Design

### 4.1. Connection Establishment

The client initially connects to the server via TCP to establish the connection and receive its unique ID. After that, gameplay messages are exchanged via UDP for efficiency.

#### 4.1.1 Server Sends Client ID (TCP)

Upon successful connection, the server assigns a unique client ID and sends the following message to the client:

```cpp
header.MagicNumber = 0x77;
header.EmmiterID = 0;  // Server ID
header.ReceiverID = CLIENT_ID; // New client ID
header.Action = 0x01;  // NEW CONNECTION
header.BodyLength = 0;
body = NULL;
```

#### 4.1.2 Client Acknowledges ID (UDP)

The client acknowledges the receipt of its ID by sending a message via UDP:

```cpp
header.MagicNumber = 0x77;
header.EmmiterID = CLIENT_ID; // ID assigned by the server
header.ReceiverID = 0;  // Server ID
header.Action = 0x01;  // NEW CONNECTION
header.BodyLength = 0;
body = NULL;
```

### 4.2. Common Action Codes

The protocol defines several common action codes for handling game state synchronization and player actions:

- **NEW CONNECTION (0x02)**: Sent by the client to acknowledge the receipt of its ID after connecting to the server.

- **INPUT (0x02)**: Sent when the server detects a desynchronization between clients and forces a rollback to a previous game state.

Example:
```cpp

#define INPUT_LIST_SIZE 5

struct InputData {
    bool KeyPressed[INPUT_LIST_SIZE]; // List of keys pressed by the player
};

header.MagicNumber = 0x77;
header.EmmiterID = CLIENT_ID // Client ID
header.ReceiverID = 0x0; // Server ID
header.Action = 0xAA; // Inpput action
header.BodyLength = sizeof(InputData);
body = [InputData];  // Player input data (e.g., direction, attack)
```

### 4.3. Server-to-Client Messages

The server sends messages to clients to notify them about game state changes. Common server-to-client messages include:

- **ROLLBACK (0x56)**: Sent when the server detects a desynchronization between clients and forces a rollback to a previous game state.

Example:
```cpp

struct RollbackData {
    uint64_t Timestamp; // Timestamp of the rollback event
};

header.MagicNumber = 0x77;
header.EmmiterID = 0x0; // Server ID
header.ReceiverID = CLIENT_ID; // Client ID
header.Action = 0x56; // Rollback action
header.BodyLength = sizeof(RollbackData);
body = [RollbackData];  // Rollback data (e.g., timestamp, state)
```

### 4.4. Client-to-Server Messages

Clients send messages to the server to perform actions or provide updates. Common client-to-server messages include:

- **USERNAME (0xAB)**: Sent during the initial connection to set the player’s username.

Example:
```cpp

#define USERNAME_LENGTH 32

struct UsernameData {
    char Username[USERNAME_LENGTH]; // Player's username
};

header.MagicNumber = 0x77;
header.EmitterID = CLIENT_ID; // Client ID
header.ReceiverID = 0x0; // Server ID
header.Action = 0xAB; // Username action
header.BodyLength = sizeof(UsernameData);
body = [UsernameData];  // Username data (e.g., player's username)
```

## 5. Error Handling

The protocol uses a lightweight error-handling mechanism. If a message is lost or malformed, the server or client don't process it and wait for a retransmission.

- **Timeouts**: Messages that are not acknowledged within a set timeout will be retransmitted.
- **Graceful Reconnection**: Clients can attempt to reconnect within a grace period after disconnection.

## 6. Security Considerations

The protocol includes basic security measures to ensure fair gameplay and protect against tampering:

- **Session Authentication**: Players are authenticated using unique session tokens to prevent unauthorized connections.
- **Data Validation**: All incoming messages are validated by the server to prevent malicious inputs or buffer overflow attacks.

## 7. References

- RFC 768: User Datagram Protocol
- RFC 793: Transmission Control Protocol
