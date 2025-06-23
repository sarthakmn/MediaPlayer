#include "decoder.h"
#include <iostream>

AudioDecoder::AudioDecoder() {
    av_log_set_level(AV_LOG_ERROR);
    avformat_network_init();
    packet = av_packet_alloc();
    frame = av_frame_alloc();
    audio_stream_index = -1;
}

bool AudioDecoder::init(const std::string& filename) {
    if (avformat_open_input(&fmt_ctx, filename.c_str(), nullptr, nullptr) < 0) {
        std::cerr << "❌ Could not open file: " << filename << std::endl;
        return false;
    }

    if (avformat_find_stream_info(fmt_ctx, nullptr) < 0) {
        std::cerr << "❌ Could not find stream info" << std::endl;
        return false;
    }

    for (unsigned i = 0; i < fmt_ctx->nb_streams; ++i) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_index = i;
            break;
        }
    }

    if (audio_stream_index == -1) {
        std::cerr << "❌ No audio stream found" << std::endl;
        return false;
    }

    codec = avcodec_find_decoder(fmt_ctx->streams[audio_stream_index]->codecpar->codec_id);
    if (!codec) {
        std::cerr << "❌ Unsupported codec" << std::endl;
        return false;
    }

    codec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_ctx, fmt_ctx->streams[audio_stream_index]->codecpar);

    if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
        std::cerr << "❌ Could not open codec" << std::endl;
        return false;
    }

    // 🛠️ Handle unset channel layout
    if (codec_ctx->channel_layout == 0) {
        codec_ctx->channel_layout = av_get_default_channel_layout(codec_ctx->channels);
    }

    // ✅ Initialize the software resampler
    swr_ctx = swr_alloc_set_opts(nullptr,
        AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16, 44100,                      // Output format
        codec_ctx->channel_layout, codec_ctx->sample_fmt, codec_ctx->sample_rate, // Input format
        0, nullptr);

    if (!swr_ctx || swr_init(swr_ctx) < 0) {
        std::cerr << "❌ Failed to initialize resampler" << std::endl;
        return false;
    }

    // Allocate buffer for converted PCM data
    av_samples_alloc_array_and_samples(&converted_data, &out_linesize, 2, 1152, AV_SAMPLE_FMT_S16, 0);
    return true;
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

AudioDecoder::~AudioDecoder() {
    if (converted_data) {
        av_freep(&converted_data[0]);
        av_freep(&converted_data);
    }
    if (swr_ctx) swr_free(&swr_ctx);
    if (frame) av_frame_free(&frame);
    if (packet) av_packet_free(&packet);
    if (codec_ctx) avcodec_free_context(&codec_ctx);
    if (fmt_ctx) avformat_close_input(&fmt_ctx);
}


map<int, string> fileParser::get_song_list(void){
    int count = 1;
    std::string path = "../metaData/songs/";  // or any path you want to scan
    for (const auto& entry : filesystem::recursive_directory_iterator(path)) {
        if ((entry.is_regular_file()) && 
            (entry.path().extension() == ".mp3" ||
            entry.path().extension() == ".wav" ||
            entry.path().extension() == ".flac" ||
            entry.path().extension() == ".aac" ||
            entry.path().extension() == ".wma")) {

            files.insert({count, entry.path().string()});
            count++;
        }
    }
    return files;
}
