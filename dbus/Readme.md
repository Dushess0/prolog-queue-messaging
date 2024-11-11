# SWI-Prolog D-Bus Integration

## Overview

This module provides integration of **SWI-Prolog** with the **D-Bus** inter-process communication system, using C++ wrappers for seamless communication. The solution is containerized using **Docker**, with services orchestrated via **Docker Compose**. It enables both sending and receiving messages on D-Bus directly from Prolog, utilizing Prolog predicates for efficient interaction.
## Available Predicates

This section describes the main predicates defined in `dbus_prolog.pl` for D-Bus integration with SWI-Prolog. Example usage of these predicates is shown in the `reader.pl` and `writer.pl` scripts.

### dbus_connect/0
**Description**: Establishes a connection with the D-Bus session. Must be called first before any communication.

**Usage**:
?- dbus_connect.

### dbus_send_signal/4
**Description**: Sends a D-Bus signal to a specified path, interface, and member (signal name) with a message.

**Arguments**:
- **Path**: D-Bus object path (e.g., `/org/example/TestPath`)
- **Interface**: D-Bus interface name (e.g., `org.example.TestInterface`)
- **Member**: Signal name (e.g., `TestSignal`)
- **Message**: Content of the message

**Usage**:
?- dbus_send_signal('/org/example/TestPath', 'org.example.TestInterface', 'TestSignal', 'Hello from Prolog').

### register_dbus_callback/1
**Description**: Registers a Prolog predicate as a callback for incoming D-Bus messages. The callback predicate should accept three arguments: Interface, Member, and Path.

**Arguments**:
- **PredicateName**: Name of the callback predicate (e.g., `on_dbus_message`)

**Usage**:
?- register_dbus_callback(on_dbus_message).

### dbus_receive/0
**Description**: Starts listening for incoming D-Bus messages and processes them asynchronously. Should be called after registering a callback function.

**Usage**:
?- dbus_receive.


## Project Structure

- **`dbus/source/`**: Contains C++ source code for D-Bus communication.
- **`dbus/dbus_prolog.pl`**: Defines Prolog predicates for interacting with D-Bus.
- **`dbus/dbus-session.conf`**: User session configuration for D-Bus.
- **`dbus/dbus-system.conf`**: System-wide configuration for D-Bus.
- **`dbus/docker-compose.yml`**: Defines the Docker configuration for D-Bus service orchestration.
- **`dbus/Dockerfile.dbus`**: Dockerfile for building the D-Bus service image.
- **`dbus/entrypoint.sh`**: Entry point script for initializing the D-Bus container.
- **`dbus/Makefile`**: Compilation instructions for C++ code and integration with SWI-Prolog.
- **`dbus/reader.pl`**: Prolog script for receiving messages from D-Bus.
- **`dbus/writer.pl`**: Prolog script for sending messages over D-Bus.

## Usage Instructions

### Starting the D-Bus Service

To start the D-Bus service along with the SWI-Prolog container, run the following command from the `dbus/` directory:

```bash
docker-compose up
```
