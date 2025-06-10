#include "ahal.h"
FILE *fd = nullptr;

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
    //cout << "ALSA Interface Initialized" << endl;
    fd = wav_parser();
    frame_bytes = 2 * (16 / 8);
    frames = bufferSize / frame_bytes;
    return 0;
}

void ahal::alsa_write() {
    size_t bytes_read = fread(buffer, 1, bufferSize, fd);
    err = snd_pcm_writei(handle, buffer, frames);
    if (err < 0) {
        cerr << "Error writing to PCM device: " << snd_strerror(err) << endl;
        snd_pcm_prepare(handle);  
    }
}

void ahal::alsa_pause(int enable) {
    if (enable) snd_pcm_pause(handle, 1);  
    else snd_pcm_pause(handle, 0);
}

void ahal::alsa_read(void) {
    // TODO
}