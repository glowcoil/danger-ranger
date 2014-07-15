#include "../interfaces/button.hpp"
#include "../animation.hpp"

class StoneButton : public Button, public Graphical {
public:
    StoneButton(Map *map, Vector3f position, Vector3f size);
    void updateGraphical();
    
private:
    void draw(RenderTarget &target, RenderStates states) const;
    
    Animation sprite;
};
