#include "ice.hpp"

Ice::Ice(Map *map, Vector3f position, Vector3f size) : Physical(map), position(position), size(size) {
}
Vector3f &Ice::getPosition() {
    return position;
}
Vector3f &Ice::getSize() {
    return size;
}
bool Ice::isSolid() {
    return true;
}
bool Ice::isPushable() {
    return false;
}
bool Ice::hasFriction() {
    return false;
}
void Ice::push(Vector3f d) {
}
