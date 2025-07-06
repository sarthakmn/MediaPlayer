#include <map>

#include "AudioManager.h"

int AudioManager::cur_song = 1;

void AudioManager::init(void){
    devghevClient.sendCommand("alsa_init");
    cout << "AudioManager initialized." << endl;
    audioClient.init("127.0.0.1", 5000, 12345);
    audioClient.connect();
    songs = Fparser->get_song_list();
    //Ahal->alsa_init();
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
        devghevClient.sendCommand("alsa_drain");
        //Ahal->alsa_drain();
        return;
    }
    while (Adecoder->getNextFrame(&pcm_data, data_size, nb_samples)) {
        if(state->getState() != Playing){
            return;
        }
        //devghevClient.sendCommand("alsa_write");
        audioClient.send(reinterpret_cast<char*>(pcm_data), data_size);
        //Ahal->alsa_write(pcm_data,nb_samples);
    }
}

void AudioManager::pause(int enable){
    if (enable) {
        devghevClient.sendCommand("alsa_pause", "1");
    } else {
        devghevClient.sendCommand("alsa_pause", "0");
    }
    //Ahal->alsa_pause(enable);
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
