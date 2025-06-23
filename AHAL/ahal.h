#pragma once

#include <iostream>
#include <memory>
#include <alsa/asoundlib.h>
#include "wav_parser.h"
#include <stdlib.h>

using namespace std;
#define bufferSize 4096

class ahal {
    int err = 0;
    snd_pcm_t *handle = nullptr;
    size_t frame_bytes = 0;
    size_t frames = 0;

    public:
        int alsa_init();
        void alsa_drop();
        void alsa_write(uint8_t* buffer,int nb_samples);
        void alsa_read();
        void alsa_pause(int);
        ~ahal();

};