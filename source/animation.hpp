#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include "interfaces/updatable.hpp"

using namespace sf;

class Animation : public Drawable, public Transformable, public Updatable {
public:
    Animation();
    Animation(const Texture &texture, const Vector2i &size, int frames = 1, float delay = 0);
    
    void setTexture(const Texture &texture);
    const Texture *getTexture();
    void setColor(const Color &color);
    const Color &getColor() const;
    void setSize(const Vector2i &s);
    const Vector2i &getSize() const;
    void setFrameOffset(int f);
    int getFrameOffset();
    void setFrames(int fs);
    int getFrames() const;
    FloatRect getLocalBounds() const;
    FloatRect getGlobalBounds() const;
    void setLocation(Vector3f position);
    
    void setFrame(int f);
    int getFrame();
    void start(int f = 0);
    void stop();
    void play();
    void pause();
    void setDelay(float d);
    float getDelay();
    void setTime(float t);
    float getTime();
    
    void update();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;
    
    void updateTextureRect();
    
    Sprite sprite;
    Vector2i size;
    int frameOffset;
    int frames;
    int frame;
    bool playing;
    float delay;
    float elapsed;
};

#endif