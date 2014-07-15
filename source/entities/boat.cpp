#include "boat.hpp"
#include "../image_manager.hpp"
#include "../map.hpp"

#include <iostream>

Boat::Boat(Map *map, Vector3f position, Vector3f size) : Physical(map), position(position), size(size), velocity(0, 0, 0), sprite(), movementState(Idle) {
    sprite.setTexture(getTexture("raft.png"));
}
Vector3f &Boat::getPosition() {
    return position;
}
Vector3f &Boat::getSize() {
    return size;
}
bool Boat::isSolid() {
    return true;
}
bool Boat::isPushable() {
    return true;
}
bool Boat::hasFriction() {
    return true;
}
void Boat::push(Vector3f direction) {
	if (movementState == Idle && !getMap()->intersectsSolid(this, direction)) {
		velocity = direction;
		movementState = Moving;
	}
}
void Boat::update() {

}
void Boat::move() {
	switch (movementState) {
	break; case Idle:

	break; case Moving:
		position += velocity;
		if (Vector3f(Vector3i(position)) == position && int(position.x) % 16 == 0 && position.y == float(int(position.y)) && int(position.y) % 12 == 0) {
			movementState = Idle;
			velocity = Vector3f(0, 0, 0);
		}
	}
}
void Boat::updateGraphical() {
    sprite.setPosition(float(int(position.x + 2)), float(int(position.y - position.z - 13)));
    if (velocity.y != 0) sprite.setFrame(0);
    else if (velocity.x != 0) sprite.setFrame(1);
}
void Boat::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
