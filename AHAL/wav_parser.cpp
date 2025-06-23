#include "wav_parser.h"

FILE* wav_parser(void) {
    FILE* fp = fopen("../metaData/songs/sochnasake.wav", "rb");
    if (!fp) {
        perror("Error opening WAV file");
        return nullptr;
    }
    WAVHeader *header = (WAVHeader*)malloc(sizeof(WAVHeader));
    if (!header) {
        perror("Error allocating memory for WAV header");
        fclose(fp);
        return nullptr;
    }
    size_t bytesRead = fread(header, 1, sizeof(WAVHeader), fp);
    if (bytesRead != sizeof(WAVHeader)) {
        perror("Error reading WAV header");
        free(header);
        fclose(fp);
        return nullptr;
    }
    free(header);

    return fp;
}
