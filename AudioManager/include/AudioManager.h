#pragma once

#include <decoder.h>
#include <audio.h>
#include "../../AHAL/include/ahal.h"
#include "StateMachine.h"
#include "devghevClient.h"

using namespace std;

class IAudioManager {
    public:
        virtual void init(void) = 0;
        virtual void play(void) = 0;
        virtual void pause(int) = 0;
        virtual void next(void) = 0;
        virtual void previous(void) = 0;
};

class AudioManager : public IAudioManager, public AudioState, public ahal{
    std::unique_ptr<AudioDecoder> Adecoder = make_unique<AudioDecoder>();
    std::unique_ptr<fileParser> Fparser = make_unique<fileParser>();
    std::unique_ptr<ahal> Ahal = make_unique<ahal>();

    map<int , string> songs;
    uint8_t* pcm_data;
    int data_size;
    int nb_samples;
    static int cur_song;
    AudioState *state;
    AMDevghevClient devghevClient;
    AudioNetworkClient audioClient;
    
    public:
        AudioManager(AudioState *st) {
            state = st;
            songs = Fparser->get_song_list();

            // Register state change callbacks
            st->onEnter(Playing, [this]() { this->pause(0); });
            st->onExit(Playing, [this]() { this->pause(1); });
            st->onEnter(Paused,  [this]() { this->pause(1); });
            //st->onEnter(Next,    [this]() { devghevClient.sendCommand("alsa_drop"); });
            //st->onEnter(Prev,    [this]() { devghevClient.sendCommand("alsa_drop"); });
        }
        void init(void) override;
        void play(void) override;
        void pause(int) override;
        void next(void) override;
        void previous(void) override;
        ~AudioManager() {
            cout << "AudioManager instance destroyed." << endl;
        }
};