#include "shadow.hpp"

#include <cmath>
#include <iostream>
#include "../image_manager.hpp"

Shadow::Shadow(Map *map, Physical *owner) : map(map), owner(owner), size(16, 12, 0), sprite(), position(10, 10, 12), visible(true) {
    sprite.setTexture(getTexture("shadow.png"));
    sprite.setColor(Color(255, 255, 255, 100));
}

Vector3f &Shadow::getPosition() {
    return position;
}
Vector3f &Shadow::getSize() {
    return size;
}

void Shadow::updateGraphical() {
    position = owner->getPosition();
    visible = false;

    Vector3f offset(0, 0, 0);

    if (int(position.z) % 12 != 0) {
        offset.z = (12 * int(position.z / 12)) - position.z;
        visible = true;
    }
    while (!(map->intersectsSolid(owner, offset + directionVector(Down)) || offset.z < -36)) {
        visible = true;
        offset += directionVector(Down);
    }
    position += offset;
    position.z += 1;
    
    sprite.setPosition(position.x, position.y - position.z + 6);
}

void Shadow::draw(RenderTarget &target, RenderStates states) const {
    if (visible) target.draw(sprite, states);
}
