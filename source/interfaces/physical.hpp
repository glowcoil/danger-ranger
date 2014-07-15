#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include <SFML/System.hpp>
using namespace sf;

enum Direction { South, North, West, East, Down, Up, None };

Vector2f normalize(Vector2f vector);
Vector3f normalize(Vector3f vector);
Vector3f directionVector(Direction direction);

// Stupid forward declaration because of cyclic dependencies
class Map;

class Physical {
public:
    Physical(Map *m);
    virtual Vector3f &getPosition() = 0;
    virtual Vector3f &getSize() = 0;
    virtual bool isSolid() = 0;
    virtual bool isPushable() = 0;
    virtual bool hasFriction() = 0;
    virtual bool isWater();
    virtual bool isClimbable();
    virtual bool isWarp();
    virtual void push(Vector3f direction) = 0;
    virtual void move();
    Map *getMap();
private:
    Map *map;
};

#endif
