#include "grass_button.hpp"
#include "../image_manager.hpp"

GrassButton::GrassButton(Map *map, Vector3f position, Vector3f size) : Button(map, position, size), sprite() {
    sprite.setTexture(getTexture("grass_button.png"));
    sprite.setSize(Vector2i(16, 24));
}

void GrassButton::updateGraphical() {
    sprite.setFrameOffset(isPressed());
    sprite.setPosition(getPosition().x, getPosition().y - getPosition().z - 12);
}
void GrassButton::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
