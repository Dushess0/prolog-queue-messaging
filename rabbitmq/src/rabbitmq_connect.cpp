#include <iostream>
#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <SWI-cpp.h>
#include "rabbitmq_wrapper.h"

amqp_connection_state_t connection;

extern "C" foreign_t pl_rabbitmq_connect(term_t host, term_t port) {
    char *c_host;
    int c_port;

    if (!PL_get_atom_chars(host, &c_host) || !PL_get_integer(port, &c_port)) {
        std::cerr << "Invalid arguments to pl_rabbitmq_connect." << std::endl;
        PL_fail;
    }

    connection = amqp_new_connection();
    amqp_socket_t *socket = amqp_tcp_socket_new(connection);
    if (!socket) {
        std::cerr << "Failed to create TCP socket." << std::endl;
        PL_fail;
    }

    if (amqp_socket_open(socket, c_host, c_port)) {
        std::cerr << "Failed to connect to RabbitMQ broker at " << c_host << ":" << c_port << std::endl;
        PL_fail;
    }

    std::cout << "Connected to RabbitMQ broker at " << c_host << ":" << c_port << std::endl;
    PL_succeed;
}
