#include <SWI-cpp.h>
#include <mosquitto.h>
#include "mqtt_wrapper.h"

// Example of registration function
extern "C" install_t install_mqtt() {
    PL_register_foreign("pl_mqtt_connect", 2, (pl_function_t)pl_mqtt_connect, 0);
    PL_register_foreign("pl_mqtt_publish", 2, (pl_function_t)pl_mqtt_publish, 0);
    PL_register_foreign("pl_mqtt_subscribe", 1, (pl_function_t)pl_mqtt_subscribe, 0);
    PL_register_foreign("pl_register_mqtt_callback", 1, (pl_function_t)pl_register_mqtt_callback, 0);
    PL_register_foreign("pl_mqtt_loop", 0, (pl_function_t)pl_mqtt_loop, 0);  // Register the missing loop function
}
