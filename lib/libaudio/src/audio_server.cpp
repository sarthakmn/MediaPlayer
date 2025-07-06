#include "audio.h"
#include <iostream>
#include <thread>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>

#define BUFFER_SIZE 4096

static std::thread server_thread;

int audio_server_start(int port, audio_callback_t callback) {
    server_thread = std::thread([port, callback]() {
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            perror("[SERVER] Failed to create socket");
            return;
        }

        sockaddr_in serv_addr{};
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("[SERVER] Bind failed");
            close(sockfd);
            return;
        }

        std::cout << "[SERVER] Listening on UDP port " << port << std::endl;

        while (true) {
            char buffer[BUFFER_SIZE];
            sockaddr_in client_addr{};
            socklen_t client_len = sizeof(client_addr);

            int len = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                               (sockaddr*)&client_addr, &client_len);

            if (len < 0) {
                perror("[SERVER] recvfrom failed");
                continue;
            }

            uint32_t client_id = ntohl(client_addr.sin_addr.s_addr);

            std::cout << "[SERVER] Received " << len << " bytes from "
                      << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port)
                      << " (client_id=" << client_id << ")\n";

            // Call the user-provided callback
            callback(client_id, buffer, len);
        }

        close(sockfd);
    });

    server_thread.detach();
    return 0;
}
