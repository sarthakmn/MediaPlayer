#include <iostream>
#include <memory>
#include <thread>
#include "AudioManager.h"
#include "ahal.h"
#include "hmi.h"

using namespace std;

int main(void){
    AudioState *st = new AudioState();
    AudioManager *am = new AudioManager(st);
    
    am->init();

    thread hmiThread(hmi::input,st);
    
    while(1){
        switch (st->getState())  
        {
        case Playing:
            am->play();
            break;
        default:
            break;
        }
    }
    hmiThread.join();
    return 0;
}