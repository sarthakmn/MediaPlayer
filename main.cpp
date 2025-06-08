#include <iostream>
#include <memory>
#include <thread>
#include "AudioManager.h"
#include "ahal.h"
#include "hmi.h"

using namespace std;
 
int main(void){
    thread hmiThread(hmi::input);
    AudioManager audioManager;
    audioManager.init();
    while(1){
        audioManager.play();
    }
    hmiThread.join();
    return 0;
}