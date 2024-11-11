# SWI-Prolog Messaging Integration

## Overview

This repository contains a solution for integrating **SWI-Prolog** with various messaging systems such as **MQTT**, **D-Bus**, and **RabbitMQ**. The integration is achieved through C++ wrappers that facilitate communication between Prolog and these messaging protocols. The entire setup is containerized using **Docker** and orchestrated with **Docker Compose**, ensuring a seamless and scalable deployment environment.

## Usage
Each messaging protocol is organized in its own directory: `stomp/`, `mqtt/`, `dbus/`, and `rabbitmq/`. Each of these directories includes two example Prolog scripts:

- **`writer.pl`**: Demonstrates how to publish messages using the respective messaging protocol.
- **`reader.pl`**: Demonstrates how to subscribe and receive messages.

These scripts can be used as templates for developing your own Prolog-based messaging applications.


### Additional Documentation
Each messaging protocol directory (mqtt/, dbus/, rabbitmq/, stomp/) includes a README.md file with detailed descriptions of the available methods, configuration options, and example usage scenarios.

For more information, refer to the `README.md` files in each protocol's directory.

## Features

- **MQTT Integration**: Publish and subscribe to MQTT topics directly from SWI-Prolog.
- **D-Bus Integration**: Communicate with system services using D-Bus from SWI-Prolog.
- **RabbitMQ Integration**: Manage message queues and handle messaging workflows with RabbitMQ.
- **Modular Architecture**: Each messaging protocol is encapsulated within its own Docker container, promoting separation of concerns and ease of maintenance.
- **Asynchronous Processing**: Efficient handling of incoming and outgoing messages without blocking the main Prolog thread.

## Dependencies

- **Docker**: Containerization platform to run and manage containers.
- **Docker Compose**: Tool for defining and running multi-container Docker applications.
- **SWI-Prolog**: A versatile Prolog environment for logic programming.
- **C++**: Used to create wrappers that interface SWI-Prolog with messaging protocols.
- **Mosquitto**: MQTT broker for handling MQTT messages.
- **D-Bus**: Inter-process communication system for Unix-like operating systems.
- **RabbitMQ**: Advanced Message Queuing Protocol (AMQP) broker for managing message queues.

## Installation

### Prerequisites

- **Docker**: Ensure Docker is installed on your machine. [Download Docker](https://www.docker.com/get-started)
- **Docker Compose**: Ensure Docker Compose is installed. [Install Docker Compose](https://docs.docker.com/compose/install/)
- **Git**: To clone the repository. [Download Git](https://git-scm.com/downloads)

