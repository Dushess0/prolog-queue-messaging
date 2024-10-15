#include <iostream>
#include <dbus/dbus.h>
#include <SWI-cpp.h>
#include "dbus_wrapper.h"

extern DBusConnection *connection;

extern "C" foreign_t pl_dbus_send_message(term_t service, term_t path, term_t interface, term_t method)
{
    if (!connection)
    {
        std::cerr << "Cannot send message: Not connected to D-Bus." << std::endl;
        PL_fail;
    }

    char *c_service, *c_path, *c_interface, *c_method;
    if (!PL_get_atom_chars(service, &c_service) ||
        !PL_get_atom_chars(path, &c_path) ||
        !PL_get_atom_chars(interface, &c_interface) ||
        !PL_get_atom_chars(method, &c_method))
    {
        std::cerr << "Invalid arguments to pl_dbus_send_message." << std::endl;
        PL_fail;
    }

    // Create and send the message
    DBusMessage *msg = dbus_message_new_method_call(
        c_service, c_path, c_interface, c_method);

    if (!msg)
    {
        std::cerr << "Failed to create D-Bus message." << std::endl;
        PL_fail;
    }

    if (!dbus_connection_send(connection, msg, nullptr))
    {
        std::cerr << "Failed to send D-Bus message." << std::endl;
        dbus_message_unref(msg);
        PL_fail;
    }

    std::cout << "D-Bus message sent: Service = " << c_service
              << ", Path = " << c_path
              << ", Interface = " << c_interface
              << ", Method = " << c_method << std::endl;

    dbus_message_unref(msg);
    PL_succeed;
}
extern "C" foreign_t pl_dbus_send_signal(term_t path, term_t interface, term_t member, term_t message)
{
    if (!connection)
    {
        std::cerr << "Cannot send signal: Not connected to D-Bus." << std::endl;
        PL_fail;
    }

    char *c_path, *c_interface, *c_member, *c_message;
    if (!PL_get_atom_chars(path, &c_path) ||
        !PL_get_atom_chars(interface, &c_interface) ||
        !PL_get_atom_chars(member, &c_member) ||
        !PL_get_atom_chars(message, &c_message))
    {
        std::cerr << "Invalid arguments to pl_dbus_send_signal." << std::endl;
        PL_fail;
    }

    // Create a new signal message
    DBusMessage *msg = dbus_message_new_signal(
        c_path,      // Object path
        c_interface, // Interface name
        c_member     // Signal name
    );

    if (!msg)
    {
        std::cerr << "Failed to create D-Bus signal message." << std::endl;
        PL_fail;
    }

    // Add a string argument to the signal
    DBusMessageIter args;
    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &c_message))
    {
        std::cerr << "Failed to add argument to D-Bus signal." << std::endl;
        dbus_message_unref(msg);
        PL_fail;
    }

    // Send the signal
    if (!dbus_connection_send(connection, msg, nullptr))
    {
        std::cerr << "Failed to send D-Bus signal." << std::endl;
        dbus_message_unref(msg);
        PL_fail;
    }

    std::cout << "D-Bus signal sent: Path = " << c_path
              << ", Interface = " << c_interface
              << ", Member = " << c_member
              << ", Message = " << c_message << std::endl;

    dbus_message_unref(msg);
    PL_succeed;
}