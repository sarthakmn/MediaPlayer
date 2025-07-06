#pragma once

#include <string>
#include <cstdint>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdint.h>

// Define the callback function type
typedef void (*audio_callback_t)(uint32_t client_id, const char* audio_data, int audio_len);

// Declaration of the audio server start function
int audio_server_start(int port, audio_callback_t callback);

class AudioNetworkClient {
public:
    AudioNetworkClient();
    ~AudioNetworkClient();

    // Initialize client (set server IP/port/client_id)
    void init(const std::string& server_ip, int port, uint32_t client_id);

    // Connect to server (for TCP, optional for UDP)
    bool connect();

    // Send PCM data buffer
    bool send(const char* pcm_data, int length);

    // Optional: close connection (for TCP)
    void close();

private:
    std::string server_ip_;
    int port_;
    uint32_t client_id_;
    int sockfd_; // For TCP, or can be recreated for UDP
};
