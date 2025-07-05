#include "devghev.hpp"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstring>

// Always use CUSTOM type and a common key-value format for the payload
void send_command(const std::string& cmd, const std::string& value = "") {
    devghev::Message msg;
    msg.id = 1;
    msg.type = devghev::MessageType::CUSTOM;
    msg.timestamp = 0;
    msg.sender_pid = getpid();

    std::string payload = "cmd=" + cmd;
    if (!value.empty()) payload += ";value=" + value;

    msg.payload_size = payload.size();
    strncpy(msg.payload, payload.c_str(), devghev::MAX_PAYLOAD);
    devghev::send("cmd", msg);
}

int main() {
    devghev::init("cmd");
    devghev::init("ack");

    std::thread([] {
        devghev::receive_loop("ack", [](const devghev::Message& msg) {
            std::cout << "ACK: " << msg.payload << std::endl;
        });
    }).detach();

    int volume = 10;
    std::string input;
    std::cout << "Enter command (play, pause, next, prev, volup, voldown, quit):\n";
    while (true) {
        std::cout << "> ";
        std::cin >> input;
        if (input == "play" || input == "pause" || input == "next" || input == "prev") {
            send_command(input);
        } else if (input == "volup") {
            volume++;
            send_command("volume", std::to_string(volume));
        } else if (input == "voldown") {
            volume--;
            send_command("volume", std::to_string(volume));
        } else if (input == "quit") {
            break;
        } else {
            std::cout << "Unknown command.\n";
        }
    }
    return 0;
}