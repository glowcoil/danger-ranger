#ifndef CRASHED_AIRPLANE_HPP
#define CRASHED_AIRPLANE_HPP

#include <SFML/Graphics.hpp>
#include "../interfaces/graphical.hpp"

using namespace sf;

class CrashedAirplane : public Graphical {
public:
    CrashedAirplane(Vector3f position);
    Vector3f &getPosition();
    Vector3f &getSize();
    void updateGraphical();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;
    Sprite sprite;
    Vector3f size;
    Vector3f position;
};

#endif
