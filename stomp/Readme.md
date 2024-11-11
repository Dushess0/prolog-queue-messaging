# SWI-Prolog STOMP Example

## Overview

This project provides an example of using **SWI-Prolog** with the **STOMP** (Simple Text Oriented Messaging Protocol) messaging broker. SWI-Prolog has native support for the STOMP protocol, which simplifies communication. This example is containerized with **Docker**, and the services are orchestrated using **Docker Compose**. For more details about the STOMP predicates, please refer to the official SWI-Prolog documentation: [SWI-Prolog STOMP](https://ww1.swi-prolog.org/pldoc/man?section=stomp).

## Available Predicates

This section briefly describes the main STOMP predicates used in **SWI-Prolog**. Example usage can be found in the `reader.pl` and `writer.pl` scripts.

### stomp_connect/2
**Description**: Establishes a connection with the STOMP broker.

**Arguments**:
- **Host**: Address of the STOMP broker (e.g., `'stomp-broker'`).
- **Port**: Port number on which the broker is listening (default is `61613`).

**Usage**:
?- stomp_connect('stomp-broker', 61613).

### stomp_subscribe/1
**Description**: Subscribes to a specified STOMP destination (queue or topic).

**Arguments**:
- **Destination**: Name of the STOMP destination (e.g., `'/queue/test'`).

**Usage**:
?- stomp_subscribe('/queue/test').

### stomp_send/2
**Description**: Sends a message to a specified STOMP destination.

**Arguments**:
- **Destination**: Name of the STOMP destination (e.g., `'/queue/test'`).
- **Message**: Content of the message to send.

**Usage**:
?- stomp_send('/queue/test', 'Hello from Prolog').

### stomp_listen/0
**Description**: Starts listening for incoming messages on subscribed destinations.

**Usage**:
?- stomp_listen.

## Project Structure

- **`stomp/docker-compose.yml`**: Defines the configuration for three Docker services: the STOMP broker, and the `reader.pl` and `writer.pl` SWI-Prolog scripts.
- **`stomp/reader.pl`**: Prolog script for receiving messages from the STOMP broker.
- **`stomp/writer.pl`**: Prolog script for sending messages to the STOMP broker.

## Usage Instructions

### Starting the STOMP Service

To start the STOMP broker along with the SWI-Prolog containers, navigate to the `stomp/` directory and run:

```bash
docker-compose up
