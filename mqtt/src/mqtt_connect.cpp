#include <iostream>
#include <mosquitto.h>
#include <SWI-cpp.h>
#include "mqtt_wrapper.h"

// Declare the global variables
struct mosquitto *mosq = nullptr;
std::mutex mqtt_mutex;

extern "C" foreign_t pl_mqtt_connect(term_t broker, term_t port) {
    char *c_broker;
    int c_port;

    if (!PL_get_atom_chars(broker, &c_broker) || !PL_get_integer(port, &c_port)) {
        std::cerr << "Invalid arguments to pl_mqtt_connect." << std::endl;
        PL_fail;
    }

    mosquitto_lib_init();

    std::lock_guard<std::mutex> lock(mqtt_mutex);
    mosq = mosquitto_new(nullptr, true, nullptr);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client." << std::endl;
        PL_fail;
    }

    if (mosquitto_connect(mosq, c_broker, c_port, 60) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to broker: " << c_broker << ":" << c_port << std::endl;
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        PL_fail;
    }

    mosquitto_message_callback_set(mosq, on_message);
    std::cout << "Connected to MQTT broker at " << c_broker << ":" << c_port << std::endl;

    PL_succeed;
}
