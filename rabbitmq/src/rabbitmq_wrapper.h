#ifndef RABBITMQ_WRAPPER_H
#define RABBITMQ_WRAPPER_H

#include <proton/container.hpp>
#include <SWI-cpp.h>
#include <string>
#include <mutex>

// Global mutex for thread safety
extern std::mutex rabbitmq_mutex;

// Callback predicate for Prolog
extern predicate_t rabbitmq_callback_predicate;

// Function declarations for Prolog integration
extern "C" {
    foreign_t pl_rabbitmq_connect(term_t host, term_t port);
    foreign_t pl_rabbitmq_publish(term_t queue, term_t message);
    foreign_t pl_rabbitmq_subscribe(term_t queue);
    foreign_t pl_register_rabbitmq_callback(term_t predicate_name);
    foreign_t pl_rabbitmq_loop();
}

// Utility function declarations
void call_prolog_rabbitmq_callback(const std::string& queue, const std::string& message);

#endif // RABBITMQ_WRAPPER_H
