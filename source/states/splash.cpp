#include "splash.hpp"
#include "../image_manager.hpp"
#include "../map_manager.hpp"

#include <algorithm>
#include <cmath>

Splash::Splash() : State(), danger(), ranger(), presskey(), jungle(), airplane(), t(0), stage(Title), flashing(false) {
	danger.setTexture(getTexture("scenes/danger.png"));
	danger.setPosition(12, 6);
	danger.setColor(Color(255, 255, 255, 0));
	ranger.setTexture(getTexture("scenes/ranger.png"));
	ranger.setPosition(22, 52);
	ranger.setColor(Color(255, 255, 255, 0));
	presskey.setTexture(getTexture("scenes/presskey.png"));
	presskey.setPosition(39, 130);
	presskey.setColor(Color(255, 255, 255, 0));
	jungle.setTexture(getTexture("scenes/jungle.png"));
	airplane.setTexture(getTexture("scenes/airplane.png"));
    airplane.setPosition(-150, 50);
    airplane.setOrigin(68, 30);

    sfx.openFromFile("scenes/airplane.ogg");
}

void Splash::update() {
    switch (stage) {
    break; case Title:
    	if (Keyboard::isKeyPressed(Keyboard::Space)) {
            stage = Transition;
            t = 0;
            sfx.play();
        } else {
            t++;
        }

		if (t < 60) {

		} else if (t < 440) {
			danger.setColor(Color(255, 255, 255, std::min(float(255), t-60)));
			ranger.setColor(Color(255, 255, 255, std::min(float(255), std::max(float(0), t-90))));
			presskey.setColor(Color(255, 255, 255, std::min(float(170), std::max(float(0), t-270))));
		} else {
			presskey.setColor(Color(255, 255, 255, 170 + (80 * sin((std::max(float(0), t - 440)) / 20))));
		}
	break; case Transition:
        if (t < 30) {
            danger.setColor(Color(255, 255, 255, std::max(float(0), 255-(t * 5))));
            ranger.setColor(Color(255, 255, 255, std::max(float(0), 255-(t * 5))));
            presskey.setColor(Color(255, 255, 255, std::max(float(0), 255-(t * 10))));
            t++;
        } else {
            t = 0;
            stage = Flying;
            danger.setColor(Color(255, 255, 255, 0));
            ranger.setColor(Color(255, 255, 255, 0));
            presskey.setColor(Color(255, 255, 255, 0));
        }
    break; case Flying:
        airplane.setPosition(std::min(float(112), t / 2 - 150), 50 + 8 * sin(t / 20));
        if (t < 550) {
            t++;
        } else if (t < 605) {
            flashing = true;
            t++;
        } else {
            flashing = false;
            t = 0;
            stage = Crashing;
        }
    break; case Crashing:
        if (t < 300) {
            airplane.setPosition(112 + (t / 60) * 9 * sin(t / 11), 50 + 8 * (t / 60) * sin(t / 20) + (t / 3));
            airplane.rotate(.05 * t);
            airplane.scale(.99, .99);
            t++;
        } else {
            t = 0;
            stage = Falling;
        }
    break; case Falling:
        airplane.move(.4, 2);
        airplane.scale(.97, .97);
        if (t < 5) {
            t++;
            flashing = true;
        } else if (t < 180) {
            flashing = false;
            t++;
        } else if (t < 360) {
            flashing = true;
            t++;
        } else {
            playMusic();
            nextMap();
        }
    }
}

void Splash::draw(RenderTarget &target, RenderStates states) const {
	target.draw(jungle, states);
	target.draw(danger, states);
	target.draw(ranger, states);
	target.draw(presskey, states);
    target.draw(airplane, states);
    if (flashing) target.clear(Color(255, 255, 255, 255));
}
