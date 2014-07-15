#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "../interfaces/graphical.hpp"

using namespace sf;

class Tile : public Graphical {
public:
    Tile(Vector3f position, Vector3f size, const char *filename, IntRect tile);
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
