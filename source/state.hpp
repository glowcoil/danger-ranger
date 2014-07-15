#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class State : public Drawable {
public:
	State();
    virtual void update() = 0;
	View view;
};

void changeState(State *state);
State *getState();

#endif
