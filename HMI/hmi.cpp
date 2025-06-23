#include "hmi.h"

void hmi::input(AudioState *State) {
    // Start the HMI input loop
    int choice;
    cout << "************ Media Player ************" << endl;
    while(1){
        cout << "1. Play" << endl;
        cout << "2. Pause" << endl;
        cout << "3. Next" << endl;
        cout << "4. Prev" << endl;
        cout << "Please select an option : ";
        cin >> choice;
        switch(choice){
            case Playing:
                State->setState(Playing);
                break;
            case Paused:
                State->setState(Paused);
                break;
            case Next:
                State->setState(Next);
                break;
            case Prev:
                State->setState(Prev);
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}
