#pragma once

#include <stdint.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

// WAV file header structure (first 44 bytes)
typedef struct {
    char riff[4];          // "RIFF"
    uint32_t chunkSize;    // Size of the WAV file
    char wave[4];          // "WAVE"
    char fmt[4];           // "fmt "
    uint32_t subchunk1Size;// Size of the format chunk (usually 16 for PCM)
    uint16_t audioFormat;  // PCM = 1
    uint16_t numChannels;  // Mono = 1, Stereo = 2
    uint32_t sampleRate;   // 44100, 48000, etc.
    uint32_t byteRate;     // SampleRate * NumChannels * BitsPerSample/8
    uint16_t blockAlign;   // NumChannels * BitsPerSample/8
    uint16_t bitsPerSample;// 8, 16, 24, 32 bits
    char dataHeader[4];    // "data"
    uint32_t dataSize;     // Size of audio data in bytes
} WAVHeader;

extern WAVHeader *header;
extern FILE* file;
FILE* wav_parser(void);
