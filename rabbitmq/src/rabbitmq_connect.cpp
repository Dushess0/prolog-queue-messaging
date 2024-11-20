#include "rabbitmq_wrapper.h"
#include "client.h"
#include <SWI-cpp.h>
#include <iostream>

extern "C" foreign_t pl_rabbitmq_connect(term_t host, term_t port) {
    char* c_host;
    int c_port;

    if (!PL_get_atom_chars(host, &c_host) || !PL_get_integer(port, &c_port)) {
        std::cerr << "Invalid arguments to pl_rabbitmq_connect." << std::endl;
        PL_fail;
    }

    RabbitMQClient& client = RabbitMQClient::get_instance();
    client.set_url(c_host, c_port);
    std::cout << "RabbitMQ URL set to: amqp://" << c_host << ":" << c_port << std::endl;
    PL_succeed;
}
