#include "hmi.h"

void hmi::input(AudioState *State) {
    // Start the HMI input loop
    int choice;
    cout << "************ Media Player ************" << endl;
    while(1){
        cout << "1. Play" << endl;
        cout << "2. Pause" << endl;
        cout << "Please select an option : ";
        cin >> choice;
        switch(choice){
            case 1:
                State->setState(Playing);
                break;
            case 2:
                State->setState(Paused);
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}
