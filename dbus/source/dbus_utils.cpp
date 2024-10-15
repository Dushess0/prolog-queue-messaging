#include <iostream>
#include <dbus/dbus.h>
#include "dbus_wrapper.h"

void print_dbus_message_arguments(DBusMessageIter *args) {
    do {
        int arg_type = dbus_message_iter_get_arg_type(args);
        if (arg_type == DBUS_TYPE_STRING) {
            char *str;
            dbus_message_iter_get_basic(args, &str);
            std::cout << "    String: " << str << std::endl;
        } else if (arg_type == DBUS_TYPE_INT32) {
            int32_t value;
            dbus_message_iter_get_basic(args, &value);
            std::cout << "    Int32: " << value << std::endl;
        } else {
            std::cout << "    Unhandled argument type: " << arg_type << std::endl;
        }
    } while (dbus_message_iter_next(args));
}

const char* dbus_message_type_to_string(int type) {
    switch (type) {
        case DBUS_MESSAGE_TYPE_METHOD_CALL:
            return "Method Call";
        case DBUS_MESSAGE_TYPE_METHOD_RETURN:
            return "Method Return";
        case DBUS_MESSAGE_TYPE_ERROR:
            return "Error";
        case DBUS_MESSAGE_TYPE_SIGNAL:
            return "Signal";
        default:
            return "Unknown";
    }
}
