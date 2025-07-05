#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <thread>

#include "devghev.hpp"

namespace devghev {

MessageQueue* getQueue(const std::string& topic, int& fd) {
    std::string name = "/devghev_" + topic;
    fd = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd < 0) return nullptr;
    ftruncate(fd, sizeof(MessageQueue));
    void* addr = mmap(nullptr, sizeof(MessageQueue), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) return nullptr;

    auto* queue = static_cast<MessageQueue*>(addr);
    pthread_mutex_init(&queue->lock, nullptr);
    return queue;
}

bool init(const std::string& topic) {
    int fd;
    return getQueue(topic, fd) != nullptr;
}

bool send(const std::string& topic, const Message& msg) {
    int fd;
    MessageQueue* queue = getQueue(topic, fd);
    if (!queue) return false;

    pthread_mutex_lock(&queue->lock);
    int next = (queue->head + 1) % QUEUE_SIZE;
    if (next != queue->tail) {
        queue->messages[queue->head] = msg;
        queue->head = next;
        pthread_mutex_unlock(&queue->lock);
        return true;
    }
    pthread_mutex_unlock(&queue->lock);
    return false;
}

bool receive_loop(const std::string& topic, std::function<void(const Message&)> callback) {
    int fd;
    MessageQueue* queue = getQueue(topic, fd);
    if (!queue) return false;

    std::thread([queue, callback]() {
        while (true) {
            pthread_mutex_lock(&queue->lock);
            while (queue->tail != queue->head) {
                Message msg = queue->messages[queue->tail];
                queue->tail = (queue->tail + 1) % QUEUE_SIZE;
                pthread_mutex_unlock(&queue->lock);
                callback(msg);
                pthread_mutex_lock(&queue->lock);
            }
            pthread_mutex_unlock(&queue->lock);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }).detach();
    return true;
}

bool shutdown(const std::string& topic) {
    std::string name = "/devghev_" + topic;
    return shm_unlink(name.c_str()) == 0;
}

} // namespace devghev