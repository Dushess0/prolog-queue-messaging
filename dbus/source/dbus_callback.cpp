#include <iostream>
#include <dbus/dbus.h>
#include <SWI-cpp.h>
#include "dbus_wrapper.h"

// Global variable to store the registered Prolog callback
predicate_t callback_predicate = nullptr;

void call_prolog_callback(const char* interface, const char* member, const char* path, const PlTerm &args) {
    PlTermv callback_args(4);  // Callback arity is now 4
    callback_args[0] = PlTerm(interface ? interface : "Unknown");
    callback_args[1] = PlTerm(member ? member : "Unknown");
    callback_args[2] = PlTerm(path ? path : "Unknown");
    callback_args[3] = args;  // Pass the extracted arguments

    PlQuery query(callback_predicate, callback_args);
    if (!query.next_solution()) {
        std::cerr << "Failed to invoke Prolog callback." << std::endl;
    }
}

extern "C" foreign_t pl_register_callback(term_t predicate_name) {
    char* pred_name;
    if (!PL_get_atom_chars(predicate_name, &pred_name)) {
        std::cerr << "Invalid predicate name for callback registration." << std::endl;
        PL_fail;
    }

    callback_predicate = PL_predicate(pred_name, 4, NULL);  // Updated arity to 4
    std::cout << "Prolog callback registered: " << pred_name << std::endl;
    PL_succeed;
}
