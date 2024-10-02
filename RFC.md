# RFC: R-Type Protocol

## Status: Draft

**RFC Number:** 6969  
**Title:** R-Type Protocol
**Author:** ETIB Corporatiion  
**Version:** 1.0

## Abstract

This RFC specifies a network protocol for R-Type to ensure efficient, real-time communication between a server and multiple clients. The protocol supports player movement, interactions, game events, and state synchronization in a low-latency environment.

## Table of Contents

1. Introduction
2. Requirements
3. Message Structure
4. Protocol Design
    1. Connection Establishment
    2. Game State Synchronization
    3. Player Actions
    4. Server-to-Client Messages
    5. Client-to-Server Messages
5. Error Handling
6. Security Considerations
7. References

## 1. Introduction

Multiplayer games require real-time communication between players through a central server. This document defines the protocol used for sending and receiving messages between clients and the server, ensuring the game state is synchronized and that latency is minimized.

## 2. Requirements

- Support for TCP/UDP connections.
- Low-latency message delivery.
- Player state synchronization between all clients.
- Error handling and reconnection strategies.
- Security features to prevent tampering and cheating.

## 3. Request Structure

Each Request in the protocol is defined by a fixed structure:

```text
Request: [Header Body]
```

```text
Header: [EmitterID U32, ReceiverID U32, Action U8, BodySize U32]
```

```text
Body: [Payload U8[1024]]
```

- **Action**: A byte indicating the type of message (e.g., player action, state update).
- **BodySize**: The length of the body in bytes.
- **Body**: The actual data to be processed (e.g., player position, game event).

### Action Types

| Type | Description | Example |
| ---- | ----------- | ------- |
| 0x01 | UP          | UP      |
| 0x02 | DOWN        | DOWN    |
| 0x03 | LEFT        | LEFT    |
| 0x04 | RIGHT       | RIGHT   |
| 0x05 | SHOOT       | SHOOT   |

## 4. Protocol Design

### 4.1. Connection Establishment

The client initiates a connection to the server using TCP for reliable communication or UDP for low-latency, depending on the game’s needs.

- **Handshake**: The server responds with an acknowledgment of the connection, and the game session begins.

### 4.2. Game State Synchronization

The server sends periodic state updates to clients to synchronize game elements like player positions, environment changes, and game events.

- **SYNC Message**: Every second, the server sends a game state update to all clients.
- **ACK Message**: Clients must acknowledge state syncs to prevent desynchronization.

### 4.3. Player Actions

Clients send player action messages to the server to reflect changes such as movement, item use, or attacks.

```text
[0x01] MOVE x=10 y=20 z=5
```

The server processes these actions and updates the game state accordingly.

### 4.4. Server-to-Client Messages

- **State Sync**: The server sends updated game states to clients.
- **Game Events**: The server notifies clients about specific events, such as enemy spawns or objective changes.
- **Kick**: The server can remove a client from the session due to disconnection, cheating, or inactivity.

### 4.5. Client-to-Server Messages

- **Player Movement**: Clients send movement updates to the server.
- **Action Request**: Clients send action requests (e.g., attacks, item usage).
- **Chat**: Clients send chat messages to other players.

## 5. Error Handling

If a message is not acknowledged within a certain timeout (e.g., 2 seconds), the server resends the message or requests that the client reconnect. If desynchronization occurs, the server can force a full game state sync.

- **Reconnection Protocol**: The client can attempt to reconnect to the server within a grace period to rejoin the session.
- **Desync Detection**: The server compares client game state checksums with its own.

## 6. Security Considerations

To prevent tampering or cheating, the protocol should include:

- **Encryption**: Messages can be encrypted to prevent eavesdropping.
- **Authentication**: Players should authenticate with the server using unique session tokens.
- **Data Validation**: All incoming messages must be validated on the server to prevent invalid game actions or buffer overflow attacks.

## 8. References

- RFC 768: User Datagram Protocol
- RFC 793: Transmission Control Protocol