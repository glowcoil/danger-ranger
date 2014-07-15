#include "button.hpp"
#include "../map.hpp"

#include <iostream>

Button::Button(Map *map, Vector3f position, Vector3f size) : Physical(map), position(position), size(size), pressed(false) {

}

Vector3f &Button::getPosition() {
    return position;
}
Vector3f &Button::getSize() {
    return size;
}
bool Button::isSolid() {
    return true;
}
bool Button::isPushable() {
    return false;
}
bool Button::hasFriction() {
    return true;
}
void Button::push(Vector3f d) {
    
}
void Button::update() {
    if (getMap()->getIntersecting(this, directionVector(Up)).empty()) {
        pressed = false;
    } else {
        pressed = true;
    }
}
bool Button::isPressed() {
    return pressed;
}
