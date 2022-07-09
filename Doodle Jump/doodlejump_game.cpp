#include"doodlejump_game.hpp"

using namespace std;

Entities input() {
	Entities entities;
	int x, y, entity;
	Type type;
	ifstream inputs;
	inputs.open(INPUT_TXT);
	inputs >> entity;
	for (int i = 0; i < entity; i++) {
		inputs >> x >> y >> type;
		if (type == PLATFORM) {
			Platform* platform = new Platform(x, y);
			entities.push_back(platform);
		}
		else if (type == MOVING_PLATFORM) {
			Moving_platform* mplatform = new Moving_platform(x, y);
			entities.push_back(mplatform);
		}
		else if (type == BROKEN_PLATFORM) {
			Broken_platform* bplatform = new Broken_platform(x, y);
			entities.push_back(bplatform);
		}
		else if (type == ENEMY) {
			Enemy* enemy = new Enemy(x, y);
			entities.push_back(enemy);
		}
		else if (type == SPRING) {
			Spring* spring = new Spring(x, y);
			entities.push_back(spring);
		}
	}
	inputs.close();
	return entities;
}

void draw(Window* window, vector<Entity*> shapes, Doodler* character) {
	window->clear();
	window->draw_img(BACKGROUND_IMAGE);
	for (int i = 0; i < shapes.size(); i++)
		shapes[i]->draw(window);
	character->draw(window);
	window->update_screen();
}
void update_shapes(Window* window, Entities entities, Doodler* character, int& difference)
{
	if (character->get_under_high() < WINDOW_HEIGHT / 2)
		difference = (WINDOW_HEIGHT / 2) - character->get_under_high();
	for (int i = 0; i < entities.size(); i++)
		entities[i]->update();
	for (int i = 0; i < entities.size(); i++)
		entities[i]->update_high(difference);
	character->update(entities, difference, window);
	difference = 0;
}
void update(Window* window, Entities entities, Doodler* character) {
	bool key = false;
	char pressededchar;
	bool update_compleated = false;
	int differnce = 0;
	while (window->has_pending_event()) {
		Event e = window->poll_for_event();
		if (e.get_type() == Event::EventType::QUIT)
			exit(0);

		if (e.get_type() == Event::KEY_PRESS) {
			while (e.get_type() != Event::KEY_RELEASE) {
				update_compleated = true;
				key = true;
				pressededchar = e.get_pressed_key();
				if (pressededchar != MOVING_LEFT_CHAR &&
					pressededchar != MOVING_RIGHT_CHAR && pressededchar != (-1))
					key = false;
				character->horizontal_movement(pressededchar, key, window);
				update_shapes(window, entities, character, differnce);
				draw(window, entities, character);
				delay(DELAY_TIME);
				e = window->poll_for_event();
			}
		}
	}

	if (!update_compleated)
		update_shapes(window, entities, character, differnce);
}
Entities remove_out_entities(Entities entities) {
	for(int i=0;i<entities.size();i++)
		if (entities[i]->get_high() >= WINDOW_HEIGHT) {
			delete entities[i];
			entities.erase(entities.begin() + i);
			i--;
		}
	return entities;
			
}