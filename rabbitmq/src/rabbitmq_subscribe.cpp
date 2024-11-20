#include "rabbitmq_wrapper.h"
#include "client.h"
#include <SWI-cpp.h>
#include <iostream>

extern "C" foreign_t pl_rabbitmq_subscribe(term_t queue) {
    char* c_queue;

    if (!PL_get_atom_chars(queue, &c_queue)) {
        std::cerr << "Invalid arguments to pl_rabbitmq_subscribe." << std::endl;
        PL_fail;
    }

    RabbitMQClient& client = RabbitMQClient::get_instance();
    client.set_queues("", c_queue);
    std::cout << "Subscribed to queue: " << c_queue << std::endl;

    PL_succeed;
}
