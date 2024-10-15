#include <iostream>
#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>
#include <SWI-cpp.h>
#include "rabbitmq_wrapper.h"

// Global variables
std::mutex rabbitmq_mutex;
predicate_t rabbitmq_callback_predicate = nullptr;  // To store the registered Prolog callback

// Function to call the Prolog callback with the queue and message
void call_prolog_rabbitmq_callback(const char* queue, const char* message) {
    if (!rabbitmq_callback_predicate) {
        std::cerr << "No Prolog callback registered." << std::endl;
        return;  // Exit if no callback is registered
    }

    PlTermv args(2);
    args[0] = PlTerm(queue ? queue : "Unknown");
    args[1] = PlTerm(message ? message : "Unknown");

    PlQuery query(rabbitmq_callback_predicate, args);
    if (!query.next_solution()) {
        std::cerr << "Failed to invoke Prolog RabbitMQ callback." << std::endl;
    }
}

// Function to register the Prolog callback
extern "C" foreign_t pl_register_rabbitmq_callback(term_t predicate_name) {
    char* pred_name;
    if (!PL_get_atom_chars(predicate_name, &pred_name)) {
        std::cerr << "Invalid predicate name for callback registration." << std::endl;
        PL_fail;
    }

    rabbitmq_callback_predicate = PL_predicate(pred_name, 2, nullptr);  // Expecting arity 2 for queue and message
    std::cout << "Prolog RabbitMQ callback registered: " << pred_name << std::endl;
    PL_succeed;
}

// Function to start the RabbitMQ message loop
extern "C" foreign_t pl_rabbitmq_loop() {
    if (!connection) {
        std::cerr << "Cannot start RabbitMQ loop: Not connected to RabbitMQ broker." << std::endl;
        PL_fail;
    }

    // Ensure queue subscription
    amqp_basic_consume(connection, 1, amqp_cstring_bytes("test_queue"),
                       amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
    amqp_rpc_reply_t res;
    amqp_envelope_t envelope;

    while (true) {
        amqp_maybe_release_buffers(connection);
        res = amqp_consume_message(connection, &envelope, NULL, 0);

        if (res.reply_type == AMQP_RESPONSE_NORMAL) {
            std::cout << "Received message on queue " << (char*)envelope.exchange.bytes 
                      << ": " << (char*)envelope.message.body.bytes << std::endl;

            // Invoke the registered Prolog callback with the message
            call_prolog_rabbitmq_callback((char*)envelope.routing_key.bytes,
                                          (char*)envelope.message.body.bytes);

            amqp_destroy_envelope(&envelope);
        } else if (res.reply_type == AMQP_RESPONSE_LIBRARY_EXCEPTION &&
                   res.library_error == AMQP_STATUS_TIMEOUT) {
            // Timeout reached, continue waiting for messages
            continue;
        } else {
            // Log the error and attempt to reconnect or handle as needed
            std::cerr << "Error consuming message: " << res.library_error << std::endl;
            if (res.reply_type == AMQP_RESPONSE_LIBRARY_EXCEPTION) {
                // Handle specific errors, potentially adding reconnection logic
            }
            break;  // Exit loop on critical error
        }
    }

    PL_succeed;
}
