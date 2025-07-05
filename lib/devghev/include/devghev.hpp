#pragma once

#include <string>
#include <functional>
#include <cstdint>

namespace devghev {

enum class MessageType : uint32_t {
    CUSTOM = 5,
    ACK = 6
};

constexpr int QUEUE_SIZE = 256;
constexpr int MAX_PAYLOAD = 240;

struct Message {
    uint32_t id;
    MessageType type;
    uint64_t timestamp;
    uint32_t sender_pid;
    uint32_t payload_size;
    char payload[MAX_PAYLOAD];
};

struct MessageQueue {
    pthread_mutex_t lock;
    volatile int head;
    volatile int tail;
    Message messages[QUEUE_SIZE];
};

bool init(const std::string& topic);
bool send(const std::string& topic, const Message& msg);
bool receive_loop(const std::string& topic, std::function<void(const Message&)> callback);
bool shutdown(const std::string& topic);

} // namespace devghev