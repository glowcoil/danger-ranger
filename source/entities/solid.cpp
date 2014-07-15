#include "solid.hpp"

Solid::Solid(Map *map, Vector3f position, Vector3f size, bool friction) : Physical(map), position(position), size(size), friction(friction) {

}

Vector3f &Solid::getPosition() {
    return position;
}
Vector3f &Solid::getSize() {
    return size;
}
bool Solid::isSolid() {
    return true;
}
bool Solid::isPushable() {
    return false;
}
bool Solid::hasFriction() {
    return friction;
}
void Solid::push(Vector3f d) {
    
}
