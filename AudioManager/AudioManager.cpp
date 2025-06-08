#include "AudioManager.h"

void AudioManager::init(void){
    ahal::alsa_init();
}

void AudioManager::play(void){
    ahal::alsa_write();
}

void AudioManager::pause(void){
    // TODO
    cout << "Pause" << endl;
}

void AudioManager::next(void){
    // TODO
    cout << "Next" << endl;
}

void AudioManager::previous(void){
    // TODO
    cout << "Previous" << endl;
}
