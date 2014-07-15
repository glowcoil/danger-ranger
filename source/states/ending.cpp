#include "ending.hpp"

#include "../image_manager.hpp"
#include "../map_manager.hpp"
#include "../interfaces/physical.hpp"

#include <algorithm>
#include <cmath>

Ending::Ending() : State(), skyline(), cliffside(), character() {
    skyline.setTexture(getTexture("scenes/city_skyline.png"));
    cliffside.setTexture(getTexture("scenes/cliffside.png"));
    cliffside.setPosition(0, 110);
    character.setTexture(getTexture("character.png"));
    character.setSize(Vector2i(16, 24));
    character.setPosition(120, 100);
    character.setFrames(4);
    character.setFrameOffset(North * 4);
}

void Ending::update() {
}

void Ending::draw(RenderTarget &target, RenderStates states) const {
    target.draw(skyline);
    target.draw(cliffside);
    target.draw(character);
}
