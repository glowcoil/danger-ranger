#ifndef MOVING_HPP
#define MOVING_HPP

#include <SFML/System.hpp>
using namespace sf;

#include "physical.hpp"
#include "../map.hpp"

class Moving : public Physical {
public:
    Moving(Map *m, Vector3f pos, Vector3f vel);
    void move() = 0;
    Vector3f position;
    Vector3f velocity;
};

#endif
