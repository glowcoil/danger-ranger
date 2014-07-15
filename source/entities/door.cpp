#include "door.hpp"
#include "../image_manager.hpp"
#include "../map.hpp"

#include <cmath>

Door::Door(Map *map, Vector3f position, Vector3f size, int index) : Physical(map), position(position), size(size), velocity(0, 0, 0), index(index), sprite(), movementState(High), zOrigin(position.z), zOffset(0) {
    sprite.setTexture(getTexture("door.png"));
}
Vector3f &Door::getPosition() {
    return position;
}
Vector3f &Door::getSize() {
    return size;
}
bool Door::isSolid() {
    return true;
}
bool Door::isPushable() {
    return false;
}
bool Door::hasFriction() {
    return true;
}
void Door::push(Vector3f direction) {

}
void Door::update() {
    switch (movementState) {
    break; case MovingUp:
        if (zOffset >= 0) {
            movementState = High;
        } else {
            zOffset += 1;
        }
    case High:
        if (getMap()->getButton(index)->isPressed()) {
            movementState = MovingDown;
            zOffset -= 1;
        }
    break; case MovingDown:
        if (zOffset <= -30) {
            movementState = Low;
        } else {
            zOffset -= 1;
        }
    case Low:
        if (!getMap()->getButton(index)->isPressed()) {
            movementState = MovingUp;
            zOffset += 1;
        }
    
    }
    position.z = zOrigin + 4 * ceil(double(zOffset / 10)); 
}
void Door::move() {

}
void Door::updateGraphical() {
    sprite.setPosition(position.x, position.y - position.z - 12);
}
void Door::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}

