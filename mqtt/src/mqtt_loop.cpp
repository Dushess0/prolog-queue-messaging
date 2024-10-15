#include <iostream>
#include <mosquitto.h>
#include <SWI-cpp.h>
#include "mqtt_wrapper.h"

extern "C" foreign_t pl_mqtt_loop() {
    if (!mosq) {
        std::cerr << "Cannot start MQTT loop: Not connected to MQTT broker." << std::endl;
        PL_fail;
    }

    std::lock_guard<std::mutex> lock(mqtt_mutex);
    int rc = mosquitto_loop_forever(mosq, -1, 1);  // Blocking loop
    if (rc != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error in MQTT loop: " << mosquitto_strerror(rc) << std::endl;
        PL_fail;
    }

    PL_succeed;
}
