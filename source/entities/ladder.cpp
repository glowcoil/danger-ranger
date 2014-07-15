#include "ladder.hpp"

Ladder::Ladder(Map *map, Vector3f position, Vector3f size) : Physical(map), position(position), size(size) {

}

Vector3f &Ladder::getPosition() {
    return position;
}
Vector3f &Ladder::getSize() {
    return size;
}
bool Ladder::isSolid() {
    return true;
}
bool Ladder::isPushable() {
    return false;
}
bool Ladder::hasFriction() {
    return true;
}
bool Ladder::isClimbable() {
    return true;
}
void Ladder::push(Vector3f d) {
    
}
