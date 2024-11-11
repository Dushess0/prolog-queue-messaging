# SWI-Prolog MQTT Integration

## Overview

This module provides integration of **SWI-Prolog** with the **MQTT** messaging protocol using C++ wrappers for seamless communication. The solution is containerized with **Docker**, and services are managed using **Docker Compose**. It allows both subscribing to MQTT topics and publishing messages directly from Prolog, using defined predicates for efficient message handling.

## Available Predicates

This section describes the main predicates defined in `mqtt_prolog.pl` for MQTT integration with SWI-Prolog. Example usage is demonstrated in the `reader.pl` and `writer.pl` scripts.

### mqtt_connect/2
**Description**: Establishes a connection with the MQTT broker.

**Arguments**:
- **Broker**: Atom representing the address of the MQTT broker (e.g., `'mqtt-server'`).
- **Port**: Integer specifying the port on which the broker is listening (e.g., `1883`).

**Usage**:
?- mqtt_connect('mqtt-server', 1883).

### mqtt_subscribe/1
**Description**: Subscribes to a specified MQTT topic.

**Arguments**:
- **Topic**: Atom representing the topic to subscribe to (e.g., `'test/topic'`).

**Usage**:
?- mqtt_subscribe('test/topic').

### register_mqtt_callback/1
**Description**: Registers a Prolog predicate as a callback for incoming MQTT messages.

**Arguments**:
- **PredicateName**: Name of the Prolog predicate to handle received messages (e.g., `mqtt_message_handler`).

**Usage**:
?- register_mqtt_callback(mqtt_message_handler).

### mqtt_loop/0
**Description**: Starts the message processing loop, listening for incoming MQTT messages asynchronously.

**Usage**:
?- mqtt_loop.

## Project Structure

- **`mqtt/mosquitto/config/mosquitto.conf`**: Configuration file for the Mosquitto MQTT broker.
- **`mqtt/docker-compose.yml`**: Docker Compose file for managing MQTT services.
- **`mqtt/Dockerfile.mqtt`**: Dockerfile for building the MQTT service image.
- **`mqtt/Makefile`**: Instructions for compiling C++ code and integrating with SWI-Prolog.
- **`mqtt/mqtt_prolog.pl`**: Defines Prolog predicates for MQTT communication.
- **`mqtt/reader.pl`**: Prolog script for subscribing to MQTT topics and receiving messages.
- **`mqtt/writer.pl`**: Prolog script for publishing messages to MQTT topics.
- **`mqtt/src/`**: Contains C++ source code for implementing the MQTT predicates used by SWI-Prolog.

## Usage Instructions

### Starting the MQTT Service

To start the MQTT broker along with the SWI-Prolog containers, run the following command from the `mqtt/` directory:

```bash
docker-compose up
```
