#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <devghev.hpp>

// Utility to send audio player commands via devghev
class AMDevghevClient {
public:
    AMDevghevClient(const std::string& topic = "ahal_cmd") {
        devghev::init(topic.c_str());
        this->topic = topic;
    }

    void sendCommand(const std::string& cmd, const std::string& value = "") {
        devghev::Message msg;
        msg.id = 1;
        msg.type = devghev::MessageType::CUSTOM;
        msg.timestamp = 0;
        msg.sender_pid = getpid();

        std::string payload = "ahal_cmd=" + cmd;
        if (!value.empty())
            payload += ";value=" + value;

        msg.payload_size = payload.size();
        strncpy(msg.payload, payload.c_str(), devghev::MAX_PAYLOAD);

        devghev::send(topic.c_str(), msg);
    }

private:
    std::string topic;
};
