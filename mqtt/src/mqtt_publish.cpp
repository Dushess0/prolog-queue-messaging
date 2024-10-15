#include <iostream>
#include <mosquitto.h>
#include <SWI-cpp.h>
#include "mqtt_wrapper.h"

extern "C" foreign_t pl_mqtt_publish(term_t topic, term_t message) {
    if (!mosq) {
        std::cerr << "Cannot publish message: Not connected to MQTT broker." << std::endl;
        PL_fail;
    }

    char *c_topic, *c_message;
    if (!PL_get_atom_chars(topic, &c_topic) || !PL_get_atom_chars(message, &c_message)) {
        std::cerr << "Invalid arguments to pl_mqtt_publish." << std::endl;
        PL_fail;
    }

    std::lock_guard<std::mutex> lock(mqtt_mutex);
    if (mosquitto_publish(mosq, nullptr, c_topic, strlen(c_message), c_message, 0, false) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to publish message to topic: " << c_topic << std::endl;
        PL_fail;
    }

    std::cout << "Published message to topic " << c_topic << ": " << c_message << std::endl;
    PL_succeed;
}
