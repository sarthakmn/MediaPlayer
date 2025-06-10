#pragma once

#include <iostream>
#include "../HMI/hmi.h"
#include "../AHAL/ahal.h"

using namespace std;

class IAudioManager {
    public:
        virtual void init(void) = 0;
        virtual void play(void) = 0;
        virtual void pause(int) = 0;
        virtual void next(void) = 0;
        virtual void previous(void) = 0;
};

class AudioManager : public IAudioManager, public AudioState, public ahal {
    public:
        AudioManager(AudioState *st) {
            // Register state change callbacks
            st->onEnter(Playing, [this]() { this->pause(0); });
            st->onEnter(Paused,  [this]() { this->pause(1); });
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