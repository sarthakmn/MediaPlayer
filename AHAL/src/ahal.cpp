#include "include/ahal.h"

int ahal::alsa_init() {
    err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        cerr << "Error opening PCM device: " << snd_strerror(err) << endl;
        return 1;
    }
    err = snd_pcm_set_params(handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 500000);
    if (err < 0) {
        cerr << "Error setting PCM parameters: " << snd_strerror(err) << endl;
        snd_pcm_close(handle);
        return 1;
    }
    snd_pcm_prepare(handle);
    frame_bytes = 2 * (16 / 8);
    frames = bufferSize / frame_bytes;
    return 0;
}

void ahal::alsa_write(uint8_t* buffer,int nb_samples) {
    err = snd_pcm_writei(handle, buffer, nb_samples);
    if (err < 0) {
        // cerr << "Error writing to PCM device: " << snd_strerror(err) << endl;
        snd_pcm_prepare(handle);  
    }
}

void ahal::alsa_pause(int enable) {
    if (enable) {
        snd_pcm_pause(handle, enable);
    }
    else{
        snd_pcm_pause(handle, 0);
    }
}

void ahal::alsa_drop() {
    // Drop the current PCM data immediately
    snd_pcm_drop(handle);
}

void ahal::alsa_drain() {
    // Drain or flush audio gracefully the PCM device to ensure all data is played before closing
    snd_pcm_drain(handle);
}

ahal::~ahal() {
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    handle = nullptr;
    cout << "AHAL destructor called" << endl;
}