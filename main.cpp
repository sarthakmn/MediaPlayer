#include <cstdlib>
#include <thread>

int main() {
    // Launch HMI UI
    std::thread([](){
        std::system("/usr/bin/pfHMI &");
    }).detach();

    // Launch AudioManager service
    std::system("/usr/bin/pfAudioManager");

    return 0;
}