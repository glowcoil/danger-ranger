#ifndef SPLASH_HPP
#define SPLASH_HPP

#include "../state.hpp"
#include <SFML/Audio.hpp>

class Splash : public State {
public:
	Splash();
	void update();
private:
    void draw(RenderTarget &target, RenderStates states) const;

    float t;

    Sprite danger;
    Sprite ranger;
    Sprite presskey;
    Sprite jungle;
    Sprite airplane;

    enum { Title, Transition, Flying, Crashing, Falling } stage;
    bool flashing;

    Music sfx;
};

#endif