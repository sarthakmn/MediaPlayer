#include "devghev.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <cstring>

// Simple parser for key-value pairs: "cmd=play;value=10"
std::string get_value(const std::string& payload, const std::string& key) {
    auto pos = payload.find(key + "=");
    if (pos == std::string::npos) return "";
    auto start = pos + key.size() + 1;
    auto end = payload.find(';', start);
    if (end == std::string::npos) end = payload.size();
    return payload.substr(start, end - start);
}

void handle_command(const devghev::Message& msg) {
    std::string payload(msg.payload, msg.payload_size);
    std::string cmd = get_value(payload, "cmd");
    std::string value = get_value(payload, "value");

    std::cout << "🎧 CMD Received: " << cmd;
    if (!value.empty()) std::cout << " value=" << value;
    std::cout << std::endl;

    std::string ack_msg = "ACK for cmd=" + cmd;
    if (!value.empty()) ack_msg += " value=" + value;

    devghev::Message ack;
    ack.id = msg.id;
    ack.type = devghev::MessageType::ACK;
    ack.timestamp = 0;
    ack.sender_pid = getpid();
    ack.payload_size = ack_msg.size();
    strncpy(ack.payload, ack_msg.c_str(), devghev::MAX_PAYLOAD);
    devghev::send("ack", ack);

    // Optionally, act on the command here
}

int main() {
    devghev::init("cmd");
    devghev::init("ack");

    devghev::receive_loop("cmd", handle_command);

    // No need for a busy loop; receive_loop blocks
    while(1){}
    return 0;
}