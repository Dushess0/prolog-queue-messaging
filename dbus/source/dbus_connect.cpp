#include "dbus_wrapper.h"
#include <iostream>
// Define the global variable here
DBusConnection *connection = nullptr;  // This should be defined in exactly one .cpp file


extern "C" foreign_t pl_dbus_connect() {
    DBusError error;
    dbus_error_init(&error);

    const char *dbus_address = getenv("DBUS_SESSION_BUS_ADDRESS");
    if (!dbus_address) {
        dbus_address = "unix:path=/tmp/session_bus_socket";  // Default to Unix socket if not set
    }

    connection = dbus_connection_open(dbus_address, &error);
    if (dbus_error_is_set(&error)) {
        std::cerr << "Failed to connect to the D-Bus daemon: " << error.message << std::endl;
        dbus_error_free(&error);
        PL_fail;
    }

    if (!connection) {
        std::cerr << "Connection to D-Bus via address " << dbus_address << " failed." << std::endl;
        PL_fail;
    }

    if (!dbus_bus_register(connection, &error)) {
        std::cerr << "Failed to register with the D-Bus daemon: " << error.message << std::endl;
        dbus_error_free(&error);
        dbus_connection_unref(connection);
        PL_fail;
    }

    dbus_bus_add_match(connection, "type='signal'", &error);
    if (dbus_error_is_set(&error)) {
        std::cerr << "Failed to add match rule: " << error.message << std::endl;
        dbus_error_free(&error);
        PL_fail;
    }

    dbus_connection_flush(connection);

    std::cout << "Connected to D-Bus via address: " << dbus_address << std::endl;

    PL_succeed;
}
