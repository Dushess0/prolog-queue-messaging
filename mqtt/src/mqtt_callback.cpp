#include <iostream>
#include <mosquitto.h>
#include <SWI-cpp.h>
#include "mqtt_wrapper.h"

predicate_t mqtt_callback_predicate = nullptr;

void call_prolog_mqtt_callback(const char* topic, const char* message) {
    if (!mqtt_callback_predicate) {
        return;  // No callback registered
    }

    PlTermv args(2);
    args[0] = PlTerm(topic ? topic : "Unknown");
    args[1] = PlTerm(message ? message : "Unknown");

    PlQuery query(mqtt_callback_predicate, args);
    if (!query.next_solution()) {
        std::cerr << "Failed to invoke Prolog MQTT callback." << std::endl;
    }
}

extern "C" foreign_t pl_register_mqtt_callback(term_t predicate_name) {
    char* pred_name;
    if (!PL_get_atom_chars(predicate_name, &pred_name)) {
        std::cerr << "Invalid predicate name for callback registration." << std::endl;
        PL_fail;
    }

    mqtt_callback_predicate = PL_predicate(pred_name, 2, nullptr);  // Assume arity 2 for topic and message
    std::cout << "Prolog MQTT callback registered: " << pred_name << std::endl;
    PL_succeed;
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    call_prolog_mqtt_callback(message->topic, (char*)message->payload);
}
