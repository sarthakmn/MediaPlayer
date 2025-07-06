#include <cstdlib>
#include <thread>

int main() {
    // Launch HMI UI
    std::thread([](){
        std::system("/usr/bin/pfHMI &");
    }).detach();

    // Launch AudioManager service
    std::thread([](){
        std::system("/usr/bin/pfAudioManager &");
    }).detach();

    // Launch AHAL service
    std::system("/usr/bin/pfAHAL");

    return 0;
}