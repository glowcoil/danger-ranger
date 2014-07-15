#ifndef WATER_HPP
#define WATER_HPP

#include "../map.hpp"

class Water : public Physical {
public:
    Water(Map *map, Vector3f position, Vector3f size);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    bool isWater();
    void push(Vector3f d);
    
private:
    Vector3f size;
    Vector3f position;
};

#endif
