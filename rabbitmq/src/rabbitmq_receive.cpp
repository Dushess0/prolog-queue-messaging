#include <iostream>
#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <SWI-cpp.h>
#include "rabbitmq_wrapper.h"

extern amqp_connection_state_t connection;
extern predicate_t rabbitmq_callback_predicate;

extern "C" foreign_t pl_rabbitmq_receive() {
    if (!connection) {
        std::cerr << "Not connected to RabbitMQ. Call pl_rabbitmq_connect first." << std::endl;
        PL_fail;
    }

    // Implement receiving logic here, calling call_prolog_rabbitmq_callback as needed.
    // ...
    
    PL_succeed;
}
