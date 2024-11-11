# SWI-Prolog RabbitMQ Integration

## Overview

This module integrates **SWI-Prolog** with the **RabbitMQ** messaging broker, enabling seamless communication using C++ wrappers. The solution is containerized with **Docker**, and services are orchestrated using **Docker Compose**. It supports both message publishing and subscription directly from Prolog using defined predicates.

## Available Predicates

This section describes the main predicates defined in `rabbitmq_prolog.pl` for RabbitMQ integration with SWI-Prolog. Example usage is demonstrated in the `reader.pl` and `writer.pl` scripts.

### rabbitmq_connect/2
**Description**: Establishes a connection with the RabbitMQ broker.

**Arguments**:
- **Host**: Address of the RabbitMQ broker (e.g., `'rabbitmq'`).
- **Port**: Port number on which the broker is listening (default is `5672`).

**Usage**:
?- rabbitmq_connect('rabbitmq', 5672).

### rabbitmq_publish/2
**Description**: Publishes a message to a specified RabbitMQ queue.

**Arguments**:
- **Queue**: Name of the queue (e.g., `'test_queue'`).
- **Message**: Content of the message to publish.

**Usage**:
?- rabbitmq_publish('test_queue', 'Hello from Prolog').

### rabbitmq_subscribe/1
**Description**: Subscribes to a specified RabbitMQ queue to receive messages.

**Arguments**:
- **Queue**: Name of the queue to subscribe to (e.g., `'test_queue'`).

**Usage**:
?- rabbitmq_subscribe('test_queue').

### register_rabbitmq_callback/1
**Description**: Registers a Prolog predicate as a callback for handling incoming RabbitMQ messages.

**Arguments**:
- **PredicateName**: Name of the Prolog predicate to be called when a message is received.

**Usage**:
?- register_rabbitmq_callback(rabbitmq_message_handler).

### rabbitmq_loop/0
**Description**: Starts the message processing loop, listening for incoming RabbitMQ messages asynchronously.

**Usage**:
?- rabbitmq_loop.

## Project Structure

- **`rabbitmq/docker-compose.yml`**: Configuration for RabbitMQ services and SWI-Prolog integration.
- **`rabbitmq/Dockerfile.rabbitmq`**: Dockerfile for building the RabbitMQ service image.
- **`rabbitmq/Makefile`**: Compilation instructions for C++ code and integration with SWI-Prolog.
- **`rabbitmq/rabbitmq_prolog.pl`**: Defines Prolog predicates for managing RabbitMQ connections and messages.
- **`rabbitmq/reader.pl`**: Prolog script for subscribing to RabbitMQ queues and handling received messages.
- **`rabbitmq/writer.pl`**: Prolog script for publishing messages to RabbitMQ queues.
- **`rabbitmq/src/`**: Contains C++ source code for RabbitMQ integration used by SWI-Prolog.

## Usage Instructions

### Starting the RabbitMQ Service

To start the RabbitMQ broker along with the SWI-Prolog container, run the following command from the `rabbitmq/` directory:

```bash
docker-compose up
```
