#pragma once

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
}

#include "../AHAL/ahal.h"

class AudioDecoder : public ahal {
    const char* filename;
    public:
        ~AudioDecoder();
        void init_decoder();
        bool getNextFrame(uint8_t** output, int& data_size, int& nb_samples);
        int getSampleRate() const;
        int getChannels() const;

private:
    AVFormatContext* fmt_ctx = nullptr;
    AVCodecContext* codec_ctx = nullptr;
    SwrContext* swr_ctx = nullptr;
    const AVCodec* codec = nullptr;
    AVPacket* packet = nullptr;
    AVFrame* frame = nullptr;
    int audio_stream_index = -1;
    uint8_t** converted_data = nullptr;
    int out_linesize = 0;
};