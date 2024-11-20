#include "rabbitmq_wrapper.h"
#include "client.h"
#include <SWI-cpp.h>
#include <iostream>

extern "C" foreign_t pl_rabbitmq_publish(term_t queue, term_t message) {
    char* c_queue;
    char* c_message;

    if (!PL_get_atom_chars(queue, &c_queue) || !PL_get_atom_chars(message, &c_message)) {
        std::cerr << "Invalid arguments to pl_rabbitmq_publish." << std::endl;
        PL_fail;
    }

    try {
        RabbitMQClient& client = RabbitMQClient::get_instance();

        // Set the send queue dynamically
        client.set_queues(c_queue, "");

        // Initialize the container (if not already initialized)
        if (client.get_url().empty()) {
            std::cerr << "RabbitMQ connection not established. Call pl_rabbitmq_connect first." << std::endl;
            PL_fail;
        }

        // Run the container to ensure sender is initialized
        proton::container(client).run();

        // Send the message
        client.send_message(c_message);

        std::cout << "Message successfully sent to queue: " << c_queue << std::endl;
        PL_succeed;
    } catch (const std::exception& e) {
        std::cerr << "Error in pl_rabbitmq_publish: " << e.what() << std::endl;
        PL_fail;
    }
}
