#include "water.hpp"

Water::Water(Map *map, Vector3f position, Vector3f size) : Physical(map), position(position), size(size) {

}

Vector3f &Water::getPosition() {
    return position;
}
Vector3f &Water::getSize() {
    return size;
}
bool Water::isSolid() {
    return false;
}
bool Water::isPushable() {
    return false;
}
bool Water::hasFriction() {
    return false;
}
bool Water::isWater() {
    return true;
}
void Water::push(Vector3f d) {
    
}
