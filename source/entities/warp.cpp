#include "warp.hpp"

Warp::Warp(Map *map, Vector3f position, Vector3f size) : Physical(map), position(position), size(size) {

}

Vector3f &Warp::getPosition() {
    return position;
}
Vector3f &Warp::getSize() {
    return size;
}
bool Warp::isSolid() {
    return false;
}
bool Warp::isPushable() {
    return false;
}
bool Warp::hasFriction() {
    return false;
}
void Warp::push(Vector3f d) {
    
}
bool Warp::isWarp() {
    return true;
}
