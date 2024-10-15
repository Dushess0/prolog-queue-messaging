#ifndef RABBITMQ_WRAPPER_H
#define RABBITMQ_WRAPPER_H

#include <SWI-cpp.h>
#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>
#include <mutex>

// Declare global variables as extern
extern amqp_connection_state_t connection;
extern std::mutex rabbitmq_mutex;
extern predicate_t rabbitmq_callback_predicate;  // To store the registered Prolog callback

// Function declarations for Prolog integration
extern "C" {
    foreign_t pl_rabbitmq_connect(term_t host, term_t port);
    foreign_t pl_rabbitmq_publish(term_t queue, term_t message);
    foreign_t pl_rabbitmq_subscribe(term_t queue);
    foreign_t pl_register_rabbitmq_callback(term_t predicate_name);
    foreign_t pl_rabbitmq_receive();
    foreign_t pl_rabbitmq_loop();
}

// Declare the callback function as extern
extern void call_prolog_rabbitmq_callback(const char* queue, const char* message);

#endif // RABBITMQ_WRAPPER_H
