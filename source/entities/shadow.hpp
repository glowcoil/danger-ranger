#ifndef SHADOW_HPP
#define SHADOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "../interfaces/graphical.hpp"
#include "../map.hpp"
#include "../animation.hpp"

using namespace sf;

class Shadow : public Graphical {
public:
    Shadow(Map *map, Physical *owner);
    
    Vector3f &getPosition();
    Vector3f &getSize();
    
    void updateGraphical();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;
    
    Sprite sprite;
    Map *map;
    Physical *owner;
    Vector3f position;
    Vector3f size;
    bool visible;
};

#endif
