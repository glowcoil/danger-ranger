#include "stone_button.hpp"
#include "../image_manager.hpp"

StoneButton::StoneButton(Map *map, Vector3f position, Vector3f size) : Button(map, position, size), sprite() {
    sprite.setTexture(getTexture("stone_button.png"));
    sprite.setSize(Vector2i(16, 24));
}

void StoneButton::updateGraphical() {
    sprite.setFrameOffset(isPressed());
}
void StoneButton::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
