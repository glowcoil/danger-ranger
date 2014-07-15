#include "crashed_airplane.hpp"
#include "../image_manager.hpp"

CrashedAirplane::CrashedAirplane(Vector3f position) : position(position), size(Vector3f(0, 0, 0)) {
    sprite.setTexture(getTexture("crashed_airplane.png"));
    sprite.setPosition(position.x, position.y - position.z);
}

Vector3f &CrashedAirplane::getPosition() {
    return position;
}
Vector3f &CrashedAirplane::getSize() {
    return size;
}

void CrashedAirplane::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
void CrashedAirplane::updateGraphical() {

}