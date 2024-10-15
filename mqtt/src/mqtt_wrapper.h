#ifndef MQTT_WRAPPER_H
#define MQTT_WRAPPER_H

#include <mosquitto.h>
#include <SWI-cpp.h>
#include <mutex>

// Declare global variables as extern
extern struct mosquitto *mosq;
extern std::mutex mqtt_mutex;
extern predicate_t mqtt_callback_predicate;  // To store the registered Prolog callback

// Function declarations for Prolog integration
extern "C" {
    foreign_t pl_mqtt_connect(term_t broker, term_t port);
    foreign_t pl_mqtt_publish(term_t topic, term_t message);
    foreign_t pl_mqtt_subscribe(term_t topic);
    foreign_t pl_register_mqtt_callback(term_t predicate_name);
    foreign_t pl_mqtt_loop();
}

// Utility function declarations
void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
void call_prolog_mqtt_callback(const char* topic, const char* message);

#endif // MQTT_WRAPPER_H
