#include "animation.hpp"

Animation::Animation() : sprite(), size(16, 16), frameOffset(0), frames(1), delay(0), playing(false), frame(0), elapsed(-1) {
    
}
Animation::Animation(const Texture &texture, const Vector2i &size, int frames, float delay) :
sprite(texture), size(size), frameOffset(0), frames(frames), delay(delay), playing(true), frame(0), elapsed(0) {
    updateTextureRect();
}

void Animation::setTexture(const Texture &texture) {
    sprite.setTexture(texture);
    updateTextureRect();
}
const Texture *Animation::getTexture()       { return sprite.getTexture(); }
void Animation::setColor(const Color &color) { sprite.setColor(color); }
const Color &Animation::getColor() const     { return sprite.getColor(); }
FloatRect Animation::getLocalBounds() const  { return sprite.getLocalBounds(); }
FloatRect Animation::getGlobalBounds() const { return sprite.getGlobalBounds(); }
void Animation::setSize(const Vector2i &s)   { size = s; updateTextureRect(); }
const Vector2i &Animation::getSize() const   { return size; }
void Animation::setFrameOffset(int f)        { frameOffset = f; updateTextureRect(); }
int Animation::getFrameOffset()              { return frameOffset; }
void Animation::setFrames(int fs)            { frames = fs; updateTextureRect(); }
int Animation::getFrames() const             { return frames; }
void Animation::setFrame(int f)              { frame = (f < 0) ? 0 : (f >= frames) ? frames - 1 : f; updateTextureRect(); }
int Animation::getFrame()                    { return frame; }
void Animation::play()                       { playing = true; }
void Animation::start(int f)                 { playing = true; setFrame(f); elapsed = -1; }
void Animation::stop()                       { playing = false; setFrame(0); elapsed = -1; }
void Animation::pause()                      { playing = false; }
void Animation::setDelay(float d)            { delay = d; }
float Animation::getDelay()                  { return delay; }
void Animation::setTime(float t)             { elapsed = t; }
float Animation::getTime()                   { return elapsed; }

void Animation::setLocation(Vector3f position) {
    setPosition(position.x, position.y - position.z);
}

void Animation::update() {
    if (playing) {
        elapsed += 1;
        if (elapsed == delay) {
            elapsed = 0;
            frame = (frame + 1 == frames) ? 0 : (frame + 1);
            updateTextureRect();
        }
    }
}

void Animation::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void Animation::updateTextureRect() {
    int hCells = sprite.getTexture()->getSize().y / size.y;
    if (hCells > 0) sprite.setTextureRect(IntRect(Vector2i(((frame + frameOffset) / hCells) * size.x, ((frame + frameOffset) % hCells) * size.y), size));
}