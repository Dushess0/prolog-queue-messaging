#ifndef CLIENT_H
#define CLIENT_H

#include <proton/container.hpp>
#include <proton/message.hpp>
#include <proton/sender.hpp>
#include <proton/receiver.hpp>
#include <proton/connection.hpp>
#include <proton/messaging_handler.hpp>
#include <string>
#include <functional>
#include <mutex>
#include <iostream>

class RabbitMQClient : public proton::messaging_handler {
private:
    std::string url;
    std::string send_queue;
    std::string receive_queue;
    proton::sender sender;
    proton::receiver receiver;
    proton::container* container;
    std::mutex client_mutex;

    RabbitMQClient() : url("amqp://rabbitmq:5672"), container(nullptr) {} // Default URL

    RabbitMQClient(const RabbitMQClient&) = delete;
    RabbitMQClient& operator=(const RabbitMQClient&) = delete;

public:
    static RabbitMQClient& get_instance() {
        static RabbitMQClient instance;
        return instance;
    }

    void set_url(const std::string& host, int port) {
        url = "amqp://" + host + ":" + std::to_string(port);
    }

    std::string get_url() const { return url; }

    void set_queues(const std::string& send_q, const std::string& recv_q) {
        send_queue = send_q;
        receive_queue = recv_q;
    }

    void on_container_start(proton::container& c) override {
        container = &c;

        try {
            // Open connection
            proton::connection conn = c.connect(url);
            std::cout << "Connected to RabbitMQ: " << url << std::endl;

            // Open sender if send_queue is set
            if (!send_queue.empty()) {
                sender = conn.open_sender(send_queue);
                std::cout << "Sender initialized for queue: " << send_queue << std::endl;
            }

            // Open receiver if receive_queue is set
            if (!receive_queue.empty()) {
                receiver = conn.open_receiver(receive_queue);
                std::cout << "Receiver initialized for queue: " << receive_queue << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Failed to start container: " << e.what() << std::endl;
        }
    }

    void send_message(const std::string& message_body) {
        if (!sender) {
            std::cerr << "Sender not initialized. Please ensure the queue is correctly set." << std::endl;
            throw std::runtime_error("Sender not initialized");
        }

        try {
            std::lock_guard<std::mutex> lock(client_mutex);
            proton::message msg;
            msg.body(message_body);
            sender.send(msg);
            std::cout << "Message sent: " << message_body << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Failed to send message: " << e.what() << std::endl;
        }
    }
};

#endif // CLIENT_H
