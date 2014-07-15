#include "moving.hpp"

#include <iostream>

Moving::Moving(Map *m, Vector3f pos, Vector3f vel) : Physical(m), position(pos), velocity(vel) {
    
}
