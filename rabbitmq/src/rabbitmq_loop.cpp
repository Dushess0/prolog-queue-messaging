#include "rabbitmq_wrapper.h"
#include "client.h"
#include <SWI-cpp.h>
#include <iostream>
#include <thread>
#include <atomic>

// Global state for managing the loop
std::atomic<bool> is_rabbitmq_loop_running{false};
std::thread rabbitmq_loop_thread;

extern "C" foreign_t pl_rabbitmq_loop() {
    try {
        RabbitMQClient& client = RabbitMQClient::get_instance();

        // Check if the loop is already running
        if (is_rabbitmq_loop_running.load()) {
            std::cerr << "RabbitMQ loop is already running." << std::endl;
            PL_fail;
        }

        is_rabbitmq_loop_running.store(true);

        rabbitmq_loop_thread = std::thread([&]() {
            try {
                proton::container(client).run();
            } catch (const std::exception& e) {
                std::cerr << "Error in RabbitMQ loop: " << e.what() << std::endl;
            }
            is_rabbitmq_loop_running.store(false);
        });

        rabbitmq_loop_thread.detach();
        std::cout << "RabbitMQ loop started." << std::endl;
        PL_succeed;
    } catch (const std::exception& e) {
        std::cerr << "Error in pl_rabbitmq_loop: " << e.what() << std::endl;
        PL_fail;
    }
}
