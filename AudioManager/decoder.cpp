#include "decoder.h"
#include <iostream>

void AudioDecoder::init_decoder() {
    filename = "../metaData/songs/sanamterikasam.wav";
    packet = av_packet_alloc();
    frame = av_frame_alloc();

    avformat_open_input(&fmt_ctx, filename, nullptr, nullptr);
    avformat_find_stream_info(fmt_ctx, nullptr);

    for (unsigned i = 0; i < fmt_ctx->nb_streams; i++) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_index = i;
            break;
        }
    }

    codec = avcodec_find_decoder(fmt_ctx->streams[audio_stream_index]->codecpar->codec_id);
    codec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_ctx, fmt_ctx->streams[audio_stream_index]->codecpar);
    avcodec_open2(codec_ctx, codec, nullptr);

    swr_ctx = swr_alloc();
    av_opt_set_channel_layout(swr_ctx, "in_channel_layout", codec_ctx->channel_layout, 0);
    av_opt_set_channel_layout(swr_ctx, "out_channel_layout", AV_CH_LAYOUT_STEREO, 0);
    av_opt_set_int(swr_ctx, "in_sample_rate", codec_ctx->sample_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "in_sample_fmt", codec_ctx->sample_fmt, 0);
    av_opt_set_int(swr_ctx, "out_sample_rate", 44100, 0);
    av_opt_set_sample_fmt(swr_ctx, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);
    swr_init(swr_ctx);

    av_samples_alloc_array_and_samples(&converted_data, &out_linesize, 2, 1152, AV_SAMPLE_FMT_S16, 0);
}

AudioDecoder::~AudioDecoder() {
    av_freep(&converted_data[0]);
    av_freep(&converted_data);
    swr_free(&swr_ctx);
    av_frame_free(&frame);
    av_packet_free(&packet);
    avcodec_free_context(&codec_ctx);
    avformat_close_input(&fmt_ctx);
}

bool AudioDecoder::getNextFrame(uint8_t** output, int& data_size, int& nb_samples) {
    while (av_read_frame(fmt_ctx, packet) >= 0) {
        if (packet->stream_index == audio_stream_index) {
            if (avcodec_send_packet(codec_ctx, packet) == 0) {
                while (avcodec_receive_frame(codec_ctx, frame) == 0) {
                    int out_samples = swr_convert(swr_ctx, converted_data, 1152,
                                                  (const uint8_t**)frame->extended_data, frame->nb_samples);
                    data_size = av_samples_get_buffer_size(nullptr, 2, out_samples, AV_SAMPLE_FMT_S16, 1);
                    *output = converted_data[0];
                    nb_samples = out_samples;
                    av_packet_unref(packet);
                    return true;
                }
            }
        }
        av_packet_unref(packet);
    }
    return false;
}

int AudioDecoder::getSampleRate() const {
    return 44100;
}

int AudioDecoder::getChannels() const {
    return 2;
}