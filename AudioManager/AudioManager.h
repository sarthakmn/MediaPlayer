#pragma once

#include <iostream>
using namespace std;

class IAudioManager {
    public:
        virtual void play(void) = 0;
        virtual void pause(void) = 0;
        virtual void next(void) = 0;
        virtual void previous(void) = 0;
};

class AudioManager : public IAudioManager {
    public:
        AudioManager() {
            cout << "AudioManager instance created." << endl;
        }
        void play(void) override;
        void pause(void) override;
        void next(void) override;
        void previous(void) override;
        ~AudioManager() {
            cout << "AudioManager instance destroyed." << endl;
        }
};