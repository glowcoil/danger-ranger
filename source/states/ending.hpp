#ifndef ENDING_HPP
#define ENDING_HPP

#include "../state.hpp"
#include "../animation.hpp"

class Ending : public State {
public:
    Ending();
    void update();
private:
    void draw(RenderTarget &target, RenderStates states) const;

    float t;

    Sprite skyline;
    Sprite cliffside;
    Animation character;
};

#endif