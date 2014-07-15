#ifndef GRAPHICAL_HPP
#define GRAPHICAL_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class Graphical : public Drawable {
public:
    virtual Vector3f &getPosition() = 0;
    virtual Vector3f &getSize() = 0;
    virtual void updateGraphical() = 0;
};

#endif