#ifndef DBUS_WRAPPER_H
#define DBUS_WRAPPER_H

#include <SWI-cpp.h>
#include <dbus/dbus.h>

// Declare the global variable as extern to avoid multiple definitions
extern DBusConnection *connection;

// Declare function interfaces for Prolog integration
extern "C" {
    foreign_t pl_dbus_connect();
    foreign_t pl_dbus_send_message(term_t service, term_t path, term_t interface, term_t method);
    foreign_t pl_dbus_receive();
    foreign_t pl_dbus_send_signal(term_t path, term_t interface, term_t member, term_t message);
    foreign_t pl_register_callback(term_t predicate_name);
}

// Utility functions
void print_dbus_message_arguments(DBusMessageIter *args);
const char* dbus_message_type_to_string(int type);
void call_prolog_callback(const char* interface, const char* member, const char* path);

#endif // DBUS_WRAPPER_H
