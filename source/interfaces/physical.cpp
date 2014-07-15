#include "physical.hpp"
#include <cmath>

Vector2f normalize(Vector2f vector) {
    return vector / (float)sqrt(vector.x * vector.x + vector.y * vector.y);
}
Vector3f normalize(Vector3f vector) {
    return vector / (float)sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}
Vector3f directionVector(Direction direction) {
    switch (direction) {
        break; case North:
            return Vector3f(0, -.75, 0);
        break; case South:
            return Vector3f(0, .75, 0);
        break; case West:
            return Vector3f(-1, 0, 0);
        break; case East:
            return Vector3f(1, 0, 0);
        break; case Down:
            return Vector3f(0, 0, -.75);
        break; case Up:
            return Vector3f(0, 0, .75);
        break; case None: default:
            return Vector3f(0, 0, 0);
    }
}

Physical::Physical(Map *m) : map(m) {

}
bool Physical::isWater() {
    return false;
}
bool Physical::isClimbable() {
    return false;
}
bool Physical::isWarp() {
    return false;
}
void Physical::move() {
    
}
Map *Physical::getMap() {
    return map;
}
