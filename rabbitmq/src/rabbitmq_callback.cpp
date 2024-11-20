#include "rabbitmq_wrapper.h"
#include "client.h"
#include <SWI-cpp.h>
#include <iostream>

// Store the Prolog callback predicate
predicate_t rabbitmq_callback_predicate = nullptr;

void call_prolog_rabbitmq_callback(const std::string& queue, const std::string& message) {
    if (!rabbitmq_callback_predicate) {
        return; // No callback registered
    }

    PlTermv args(2);
    args[0] = PlTerm(queue.c_str());
    args[1] = PlTerm(message.c_str());

    PlQuery query(rabbitmq_callback_predicate, args);
    if (!query.next_solution()) {
        std::cerr << "Failed to invoke Prolog RabbitMQ callback." << std::endl;
    }
}

extern "C" foreign_t pl_register_rabbitmq_callback(term_t predicate_name) {
    char* pred_name;
    if (!PL_get_atom_chars(predicate_name, &pred_name)) {
        std::cerr << "Invalid predicate name for callback registration." << std::endl;
        PL_fail;
    }

    rabbitmq_callback_predicate = PL_predicate(pred_name, 2, NULL);
    std::cout << "Prolog RabbitMQ callback registered: " << pred_name << std::endl;
    PL_succeed;
}
