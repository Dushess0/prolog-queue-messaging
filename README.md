# SWI-Prolog Messaging Integration

## Overview

This repository contains a solution for integrating **SWI-Prolog** with various messaging systems such as **MQTT**, **D-Bus**, and **RabbitMQ**. The integration is achieved through C++ wrappers that facilitate communication between Prolog and these messaging protocols. The entire setup is containerized using **Docker** and orchestrated with **Docker Compose**, ensuring a seamless and scalable deployment environment.

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


