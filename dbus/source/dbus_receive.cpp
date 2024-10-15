#include <iostream>
#include <dbus/dbus.h>
#include <SWI-cpp.h>
#include "dbus_wrapper.h"

extern DBusConnection *connection;
extern predicate_t callback_predicate;

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

            if (callback_predicate) {
                call_prolog_callback(interface, member, path);
            }

            DBusMessageIter args;
            if (dbus_message_iter_init(msg, &args)) {
                std::cout << "  Arguments:" << std::endl;
                print_dbus_message_arguments(&args);
            } else {
                std::cout << "  No arguments." << std::endl;
            }
        } else {
            std::cout << "Received an unknown message type: "
                      << dbus_message_type_to_string(dbus_message_get_type(msg)) << std::endl;
        }

        dbus_message_unref(msg);
    }

    PL_succeed;
}
