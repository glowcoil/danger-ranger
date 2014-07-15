#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "map.hpp"
#include "state.hpp"
#include "map_manager.hpp"
#include "entities/character.hpp"
#include "entities/boulder.hpp"
#include "states/splash.hpp"
#include "states/ending.hpp"

using namespace sf;

int main(int argc, char **argv) {
    RenderWindow window(VideoMode(480, 320), "Danger Ranger");

    window.setFramerateLimit(60);
    
    initMusic();

    changeState(new Splash());

    window.setView(getState()->view);

    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape)) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        
        window.clear(Color(0, 0, 0));
        
        getState()->update();

        window.setView(getState()->view);

        window.draw(*getState());

        window.display();
    }
    return 0;
}
