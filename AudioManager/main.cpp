#include <iostream>
#include <cstring>
#include <devghev.hpp>
#include <thread>
#include <chrono>

#include "include/AudioManager.h"
#include "../AHAL/include/ahal.h"

int main() {
    // Initialize devghev for "cmd" topic
    devghev::init("cmd");

    std::cout << "AudioManager reader started. Waiting for commands..." << std::endl;

    // Setup AudioManager
    AudioState *st = new AudioState();
    AudioManager *am = new AudioManager(st);
    am->init();

    // Start IPC command listener in a separate thread
    std::thread ipcThread([st](AudioManager *am) {
        devghev::receive_loop("cmd", [st](const devghev::Message& msg) {
            std::string payload(msg.payload, msg.payload_size);
            std::cout << "Received command: " << payload << std::endl;

            if (payload.find("cmd=play") != std::string::npos) {
                std::cout << "AudioManager: Play command received." << std::endl;
                st->setState(Playing);
            } else if (payload.find("cmd=pause") != std::string::npos) {
                std::cout << "AudioManager: Pause command received." << std::endl;
                st->setState(Paused);
            } else if (payload.find("cmd=next") != std::string::npos) {
                std::cout << "AudioManager: Next command received." << std::endl;
                st->setState(Next);
            } else if (payload.find("cmd=prev") != std::string::npos) {
                std::cout << "AudioManager: Previous command received." << std::endl;
                st->setState(Prev);
            } else {
                std::cout << "AudioManager: Unknown command." << std::endl;
            }
        });
    }, am);

    // Main playback loop (polling state)
    State lastState = Stopped;
    while (true) {
        State currState = st->getState();
        if (currState != lastState) {
            switch (currState) {
                case Playing:
                    am->play();
                    break;
                case Paused:
                    am->pause(1);
                    break;
                case Next:
                    am->next();
                    break;
                case Prev:
                    am->previous();
                    break;
                default:
                    break;
            }
            lastState = currState;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ipcThread.join();
    return 0;
}
