#include "AudioManager.h"
#include <map>

int AudioManager::cur_song = 1;

void AudioManager::init(void){
    songs = Fparser->get_song_list();
    Ahal->alsa_init();
    Adecoder->init(songs[cur_song]);
}

void AudioManager::play(void){
    while (Adecoder->getNextFrame(&pcm_data, data_size, nb_samples)) {
        if(state->getState() != Playing){
            return;
        }
        Ahal->alsa_write(pcm_data,nb_samples);
    }
}

void AudioManager::pause(int enable){
    Ahal->alsa_pause(enable);
}

void AudioManager::next(void){
    // TODO
    cout << "Next" << endl;
}

void AudioManager::previous(void){
    // TODO
    cout << "Previous" << endl;
}
