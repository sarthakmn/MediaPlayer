#include "devghev.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>   // ✅ Required for getpid()
#include <cstring>    // ✅ Required for strncpy()

int main() {
    devghev::init("audio");

    for (int i = 0; i < 5; ++i) {
        devghev::Message msg;
        msg.id = i;
        msg.type = devghev::MessageType::VOLUME;
        msg.timestamp = std::chrono::system_clock::now().time_since_epoch().count();
        msg.sender_pid = getpid();
        std::string data = "volume=" + std::to_string(50 + i * 5);
        msg.payload_size = data.size();
        strncpy(msg.payload, data.c_str(), devghev::MAX_PAYLOAD);

        if (devghev::send("audio", msg)) {
            std::cout << "✅ Sent: " << data << std::endl;
        } else {
            std::cout << "❌ Failed to send" << std::endl;
        }
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}