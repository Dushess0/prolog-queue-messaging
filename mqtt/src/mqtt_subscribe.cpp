#include <iostream>
#include <mosquitto.h>
#include <SWI-cpp.h>
#include "mqtt_wrapper.h"

extern "C" foreign_t pl_mqtt_subscribe(term_t topic) {
    if (!mosq) {
        std::cerr << "Cannot subscribe: Not connected to MQTT broker." << std::endl;
        PL_fail;
    }

    char *c_topic;
    if (!PL_get_atom_chars(topic, &c_topic)) {
        std::cerr << "Invalid argument to pl_mqtt_subscribe." << std::endl;
        PL_fail;
    }

    std::lock_guard<std::mutex> lock(mqtt_mutex);
    if (mosquitto_subscribe(mosq, nullptr, c_topic, 0) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to subscribe to topic: " << c_topic << std::endl;
        PL_fail;
    }

    std::cout << "Subscribed to topic " << c_topic << std::endl;
    PL_succeed;
}
