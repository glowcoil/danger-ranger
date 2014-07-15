#include "boulder.hpp"
#include "../image_manager.hpp"

#include <iostream>

Boulder::Boulder(Map *map, Vector3f position) : sprite(), position(position), Moving(map, position, Vector3f(0, 0, 0)), size(Vector3f(16, 12, 12)), movementState(Idle) {
    sprite.setTexture(getTexture("boulder.png"));
    Shadow *shadow = new Shadow(map, this);
    getMap()->addGraphical(shadow);
}
void Boulder::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
void Boulder::update() {
    switch (movementState) {
    break; case Idle:
        if (Vector3f(Vector3i(position)) == position && int(position.x) % 16 == 0 && position.y == float(int(position.y)) && int(position.y) % 12 == 0 &&
            !getMap()->intersectsSolid(this, directionVector(Down))) {
            movementState = Falling;
            velocity = float(.5)*directionVector(Down);
        }
    break; case Falling:        
        if (getMap()->intersectsSolid(this, velocity)) {
            velocity = Vector3f(0, 0, 0);
            position = Vector3f(position.x, position.y, 12*int(position.z / 12));
            movementState = Idle;
        } else {
            velocity += float(.5)*directionVector(Down);
        }
    }
    //std::cout << "b:"<<position.x << "," << position.y << "," << position.z <<" "<<movementState<< std::endl;
}
void Boulder::move() {
    if ((velocity.x != 0 || velocity.y != 0 || velocity.z != 0)) {
        if (getMap()->intersectsSolid(this, velocity)) {
            velocity = Vector3f(0, 0, 0);
        } else {
            position += velocity;
            if (Vector3f(Vector3i(position)) == position && int(position.x) % 16 == 0 && position.y == float(int(position.y)) && int(position.y) % 12 == 0 && getMap()->intersectsFriction(this, directionVector(Down))) {
                velocity = Vector3f(0, 0, 0);
            }
        }
    }
}
Vector3f &Boulder::getPosition() {
    return position;
}
Vector3f &Boulder::getSize() {
    return size;
}
bool Boulder::isSolid() {
    return true;
}
bool Boulder::isPushable() {
    return movementState == Idle;
}
bool Boulder::hasFriction() {
    return true;
}
void Boulder::push(Vector3f direction) {
    if (movementState == Idle) velocity = direction;
}
void Boulder::updateGraphical() {
    sprite.setLocation(Vector3f(Vector3i(position - Vector3f(0, 8, 0))));
}
