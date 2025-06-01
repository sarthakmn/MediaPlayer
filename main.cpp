#include <iostream>
#include <memory>
#include "AudioManager.h"
#include "ahal.h"
#include "hmi.h"

using namespace std;
 
int main(void){
    shared_ptr<AudioManager>audioManager = make_shared<AudioManager>();
    audioManager->play();
    return 0;
}