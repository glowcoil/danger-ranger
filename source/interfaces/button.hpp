#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../interfaces/physical.hpp"
#include "../interfaces/graphical.hpp"
#include "../interfaces/updatable.hpp"

class Button : public Physical, public Updatable, public Graphical {
public:
    Button(Map *map, Vector3f position, Vector3f solid);
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    void push(Vector3f direction);
    void update();
    bool isPressed();
    
private:
    Vector3f size;
    Vector3f position;
    bool pressed;
};

#endif
