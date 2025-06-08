#pragma once

#include <iostream>
#include <map>
#include <functional>

using namespace std;

enum State {
    Playing,
    Paused,
    Stopped
};

class AudioState {
    State cur_state;
    map<State, function<void()>> onEnterCallbacks;

    public:
        AudioState() {
            cur_state = Stopped; // Initialize to Stopped state
        }
        string getStateString(State state) const {
            switch (state) {
                case Playing: return "Playing";
                case Paused: return "Paused";
                case Stopped: return "Stopped";
                default: return "Unknown State";
            }
        }
        void setState(State state) {
            if (state == cur_state) return;
            cout << "[State Change] " << getStateString(cur_state) << " -> " << getStateString(state) << endl;
            cur_state = state;
            if (onEnterCallbacks.count(state)) {
                onEnterCallbacks[state]();
            }
        }

        void onEnter(State state, function<void()> callback) {
            onEnterCallbacks[state] = callback;
        }
        
        State getState() const {
            return cur_state;
        }
};

class hmi : public AudioState {
    public:
        static void input(void);
};