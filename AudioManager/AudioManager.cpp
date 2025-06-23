#include "AudioManager.h"
#include <map>

int AudioManager::cur_song = 1;

void AudioManager::init(void){
    songs = Fparser->get_song_list();
    Ahal->alsa_init();
    if(songs.empty()) {
        cerr << "No songs found" << endl;
        return;
    }
    Adecoder->init(songs[cur_song]);
}

void AudioManager::play(void){
    if(Adecoder->getNextFrame(&pcm_data, data_size, nb_samples) == false) {
        // If no frame is available (EOS), set the state to Next
        state->setState(Next);
        Ahal->alsa_drain();
        return;
    }
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
    cur_song++;
    if (cur_song > songs.size()) {
        cur_song = 1; // Loop back to the first song
    }
    Adecoder = make_unique<AudioDecoder>();
    Adecoder->init(songs[cur_song]);
    state->setState(Playing);
}

void AudioManager::previous(void){
    cur_song--;
    if (cur_song < 1) {
        cur_song = songs.size(); // Loop back to the last song
    }
    Adecoder = make_unique<AudioDecoder>();
    Adecoder->init(songs[cur_song]);
    state->setState(Playing);
}
