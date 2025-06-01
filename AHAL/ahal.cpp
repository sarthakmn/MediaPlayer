#include "ahal.h"

void ahal::alsa_init() {
    cout << "ALSA Interface Initialized" << endl;
}
void ahal::alsa_write() {
    cout << "Playing sound through ALSA" << endl;
}
void ahal::alsa_read() {
    cout << "Stopping sound through ALSA" << endl;
}