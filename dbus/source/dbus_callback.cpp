#include <iostream>
#include <dbus/dbus.h>
#include <SWI-cpp.h>
#include "dbus_wrapper.h"

predicate_t callback_predicate = nullptr;

void call_prolog_callback(const char* interface, const char* member, const char* path) {
    PlTermv args(3);
    args[0] = PlTerm(interface ? interface : "Unknown");
    args[1] = PlTerm(member ? member : "Unknown");
    args[2] = PlTerm(path ? path : "Unknown");

    PlQuery query(callback_predicate, args);
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

    callback_predicate = PL_predicate(pred_name, 3, NULL);  // Assume arity 3 for interface, member, path
    std::cout << "Prolog callback registered: " << pred_name << std::endl;
    PL_succeed;
}
