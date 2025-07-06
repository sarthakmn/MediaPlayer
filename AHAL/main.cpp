#include <iostream>
#include <unistd.h>
#include <devghev.hpp>
#include "include/ahal.h"

ahal* g_ahal = nullptr;

// This is called for each UDP packet received (contains raw PCM audio)
void audio_data_callback(uint32_t client_id, const char* audio_data, int audio_len) {
    std::cout << "[AUDIO] Packet received, size: " << audio_len << std::endl;
    g_ahal->alsa_write((uint8_t*)audio_data, audio_len / 4);
}

int main() {
    devghev::init("ahal_cmd");
    std::cout << "AHAL service started. Waiting for audio commands..." << std::endl;

    ahal audioHal;
    g_ahal = &audioHal;

    // Start the UDP server on port 5000 and begin receiving audio
    audio_server_start(5000, audio_data_callback);

    // Listen for control commands from AudioManager (e.g., init, pause, drain)
    devghev::receive_loop("ahal_cmd", [&audioHal](const devghev::Message& msg) {
        std::string payload(msg.payload, msg.payload_size);
        std::cout << "AHAL received: " << payload << std::endl;

        if (payload.find("cmd=alsa_init") != std::string::npos) {
            audioHal.alsa_init();
        }
        else if (payload.find("cmd=alsa_pause") != std::string::npos) {
            if (payload.find("1") != std::string::npos)
                audioHal.alsa_pause(1);  // pause
            else
                audioHal.alsa_pause(0);  // resume
        }
        else if (payload.find("cmd=alsa_drop") != std::string::npos) {
            audioHal.alsa_drop();
        }
        else if (payload.find("cmd=alsa_drain") != std::string::npos) {
            audioHal.alsa_drain();
        }
    });

    // Keep the service alive forever
    while (true) {
        sleep(1);
    }

    return 0;
}
