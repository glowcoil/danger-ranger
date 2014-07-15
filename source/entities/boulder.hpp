#ifndef BOULDER_HPP
#define BOULDER_HPP

#include <SFML/Graphics.hpp>
#include "../interfaces/updatable.hpp"
#include "../interfaces/physical.hpp"
#include "../interfaces/graphical.hpp"
#include "../interfaces/moving.hpp"
#include "../animation.hpp"
#include "shadow.hpp"

using namespace sf;

class Boulder : public Updatable, public Moving, public Graphical {
public:
    Boulder(Map *map, Vector3f position);
    void update();
    Vector3f &getPosition();
    Vector3f &getSize();
    bool isSolid();
    bool isPushable();
    bool hasFriction();
    void push(Vector3f direction);
    void updateGraphical();
    void move();

private:
    void draw(RenderTarget &target, RenderStates states) const;
    
    Animation sprite;
    Vector3f position;
    Vector3f size;
    Vector3f velocity;
    enum { Idle, Falling } movementState;
};

#endif
