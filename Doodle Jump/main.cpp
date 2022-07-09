#include"doodlejump_game.hpp"

using namespace std;

int main()
{
	Doodler* character = new Doodler (WINDOW_WIDTH/2, 0);
	Entities entities = input();

	Window* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "RSDL");
	while (true) {
		update(window, entities, character);
		draw(window, entities, character);
		entities = remove_out_entities(entities);
		delay(DELAY_TIME);
	}
	return 0;
}
