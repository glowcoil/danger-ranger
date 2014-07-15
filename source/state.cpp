#include "state.hpp"

State *state;

State::State() : view() {
	view.reset(FloatRect(0, 0, 240, 160));
}

void changeState(State *next) {
    state = next;
}
State *getState() {
    return state;
}
