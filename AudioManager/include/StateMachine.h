#pragma once

#include <iostream>
#include <map>
#include <functional>

enum State {
    Playing = 1,
    Paused,
    Next,
    Prev,
    Stopped
};

class AudioState {
    State cur_state;
    map<State, function<void()>> onEnterCallbacks;
    map<State, function<void()>> onExitCallbacks;

    public:
        AudioState() {
            cur_state = Stopped; // Initialize to Stopped state
        }
        ~AudioState() {
            cout << "Audio state destructed" << endl;
        }
        string getStateString(State state) const {
            switch (state) {
                case Playing: return "Playing";
                case Paused: return "Paused";
                case Next: return "Next";
                case Prev: return "Previous";
                case Stopped: return "Stopped";
                default: return "Unknown State";
            }
        }
        void setState(State state) {
            if (state == cur_state) return;
            cout << "[State Change] " << getStateString(cur_state) << " -> " << getStateString(state) << endl;

            if (onExitCallbacks.count(cur_state)) {
                onExitCallbacks[cur_state]();
            }
            cur_state = state;
            if (onEnterCallbacks.count(state)) {
                onEnterCallbacks[state]();
            }
        }

        void onEnter(State state, function<void()> callback) {
            onEnterCallbacks[state] = callback;
        }
        
        void onExit(State state, function<void()> callback) {
            onExitCallbacks[state] = callback;
        }

        State getState() const {
            return cur_state;
        }
};