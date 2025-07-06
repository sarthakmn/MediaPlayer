#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include "audio.h"

#define HEADER_SIZE 8
#define BUFFER_SIZE 4096

AudioNetworkClient::AudioNetworkClient() : port_(0), client_id_(0), sockfd_(-1) {}

AudioNetworkClient::~AudioNetworkClient() {
    close();
}

void AudioNetworkClient::init(const std::string& server_ip, int port, uint32_t client_id) {
    server_ip_ = server_ip;
    port_ = port;
    client_id_ = client_id;
}

bool AudioNetworkClient::connect() {
    // For UDP, we create a socket here
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        perror("[CLIENT] socket creation failed");
        return false;
    }
    std::cout << "[CLIENT] UDP socket created\n";
    return true;
}

bool AudioNetworkClient::send(const char* pcm_data, int length) {
    if (sockfd_ < 0) {
        std::cerr << "[CLIENT] Socket not initialized. Call connect() first.\n";
        return false;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_);
    if (inet_pton(AF_INET, server_ip_.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cerr << "[CLIENT] Invalid server IP: " << server_ip_ << std::endl;
        return false;
    }

    int sent = sendto(sockfd_, pcm_data, length, 0,
                      (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if (sent < 0) {
        perror("[CLIENT] sendto failed");
        return false;
    }

    std::cout << "[CLIENT] Sent " << sent << " bytes to " << server_ip_ << ":" << port_ << std::endl;
    return true;
}

void AudioNetworkClient::close() {
    if (sockfd_ >= 0) {
        ::close(sockfd_);
        sockfd_ = -1;
        std::cout << "[CLIENT] UDP socket closed\n";
    }
}
