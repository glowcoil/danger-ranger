#include "../interfaces/button.hpp"
#include "../animation.hpp"

class GrassButton : public Button {
public:
    GrassButton(Map *map, Vector3f position, Vector3f size);
    void updateGraphical();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;
    
    Animation sprite;
};
