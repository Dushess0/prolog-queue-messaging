#include <iostream>
#include <dbus/dbus.h>
#include <SWI-cpp.h>
#include "dbus_wrapper.h"
#include <vector>

extern DBusConnection *connection;
extern predicate_t callback_predicate;

// Utility function to extract D-Bus arguments as a Prolog list
PlTerm extract_dbus_arguments(DBusMessageIter *iter) {
    PlTerm list;  // Initial empty term
    PlTail tail(list);  // Prolog list builder

    do {
        int arg_type = dbus_message_iter_get_arg_type(iter);

        if (arg_type == DBUS_TYPE_STRING) {
            const char *value;
            dbus_message_iter_get_basic(iter, &value);
            tail.append(PlTerm(value));  // Add string argument
        } 
        // Add additional cases for other types if needed
    } while (dbus_message_iter_next(iter));

    tail.close();  // Finalize the list
    return list;
}

// Main function for receiving D-Bus messages
extern "C" foreign_t pl_dbus_receive() {
    if (!connection) {
        std::cerr << "Not connected to D-Bus. Call pl_dbus_connect first." << std::endl;
        PL_fail;
    }

    DBusMessage *msg;

    while (true) {
        dbus_connection_read_write(connection, 1000);  // 1 second timeout
        msg = dbus_connection_pop_message(connection);

        if (msg == nullptr) {
            continue;
        }

        if (dbus_message_get_type(msg) == DBUS_MESSAGE_TYPE_SIGNAL) {
            const char *interface = dbus_message_get_interface(msg);
            const char *member = dbus_message_get_member(msg);
            const char *path = dbus_message_get_path(msg);

            std::cout << "Received a signal:" << std::endl;
            std::cout << "  Interface: " << (interface ? interface : "Unknown") << std::endl;
            std::cout << "  Member: " << (member ? member : "Unknown") << std::endl;
            std::cout << "  Path: " << (path ? path : "Unknown") << std::endl;

            PlTerm args;  // Prolog term to hold arguments
            DBusMessageIter iter;
            if (dbus_message_iter_init(msg, &iter)) {
                args = extract_dbus_arguments(&iter);  // Extract D-Bus arguments into a Prolog list
            } else {
                args = PlCompound("[]");  // Empty list if no arguments are present
            }

            if (callback_predicate) {
                call_prolog_callback(interface, member, path, args);
            }
        } else {
            std::cout << "Received an unknown message type: "
                      << dbus_message_type_to_string(dbus_message_get_type(msg)) << std::endl;
        }

        dbus_message_unref(msg);
    }

    PL_succeed;
}
