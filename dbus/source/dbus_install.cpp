#include <SWI-cpp.h>
#include "dbus_wrapper.h"

// Install function to register the foreign predicates with Prolog
extern "C" install_t install_dbus() {
    PL_register_foreign("pl_dbus_connect", 0, (pl_function_t)pl_dbus_connect, 0);
    PL_register_foreign("pl_dbus_send_message", 4, (pl_function_t)pl_dbus_send_message, 0);
    PL_register_foreign("pl_dbus_receive", 0, (pl_function_t)pl_dbus_receive, 0);
    PL_register_foreign("pl_dbus_send_signal", 4, (pl_function_t)pl_dbus_send_signal, 0);
    PL_register_foreign("pl_register_callback", 1, (pl_function_t)pl_register_callback, 0);
}
