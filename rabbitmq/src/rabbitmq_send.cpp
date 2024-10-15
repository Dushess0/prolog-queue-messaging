#include <iostream>
#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <SWI-cpp.h>
#include "rabbitmq_wrapper.h"

extern amqp_connection_state_t connection;

extern "C" foreign_t pl_rabbitmq_publish(term_t queue, term_t message) {
    if (!connection) {
        std::cerr << "Cannot send message: Not connected to RabbitMQ." << std::endl;
        PL_fail;
    }

    char *c_queue, *c_message;
    if (!PL_get_atom_chars(queue, &c_queue) || !PL_get_atom_chars(message, &c_message)) {
        std::cerr << "Invalid arguments to pl_rabbitmq_publish." << std::endl;
        PL_fail;
    }

    // Publish the message to the specified queue
    // ...

    std::cout << "Published message to queue " << c_queue << ": " << c_message << std::endl;
    PL_succeed;
}
