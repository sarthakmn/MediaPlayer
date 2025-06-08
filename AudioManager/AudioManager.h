#pragma once

#include <iostream>
#include "../HMI/hmi.h"
#include "../AHAL/ahal.h"

using namespace std;

class IAudioManager {
    public:
        virtual void init(void) = 0;
        virtual void play(void) = 0;
        virtual void pause(void) = 0;
        virtual void next(void) = 0;
        virtual void previous(void) = 0;
};

class AudioManager : public IAudioManager, public AudioState, public ahal {
    public:
        AudioManager() {
            cout << "AudioManager instance created." << endl;
        }
        void init(void) override;
        void play(void) override;
        void pause(void) override;
        void next(void) override;
        void previous(void) override;
        ~AudioManager() {
            cout << "AudioManager instance destroyed." << endl;
        }
};