#include <iostream>
#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <SWI-cpp.h>
#include "rabbitmq_wrapper.h"

extern amqp_connection_state_t connection;

// Implementation of pl_rabbitmq_subscribe
extern "C" foreign_t pl_rabbitmq_subscribe(term_t queue) {
    if (!connection) {
        std::cerr << "Not connected to RabbitMQ. Call pl_rabbitmq_connect first." << std::endl;
        PL_fail;
    }

    char *c_queue;
    if (!PL_get_atom_chars(queue, &c_queue)) {
        std::cerr << "Invalid argument to pl_rabbitmq_subscribe." << std::endl;
        PL_fail;
    }

    // Example subscription logic (replace with actual RabbitMQ subscription code)
    std::cout << "Subscribed to queue " << c_queue << std::endl;

    PL_succeed;
}
