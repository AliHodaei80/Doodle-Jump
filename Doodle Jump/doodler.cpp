#include"doodler.hpp"

using namespace std;

Doodler::Doodler(int x, int y)
	:Entity(x, y, CHARACTER_WIDTH, CHARACTER_HEIGHT){
	high = 0;
	all_differnce = 0;
	score = 0;
	times = 0;
	colided = false;
	is_going_up = false;
	head_side_right = false;
	vx = 0;
	vy = JUMPING_SPEED;
}
int Doodler::get_speed() { return vy; }
int Doodler::get_under_high() { return points[0].y; }
void Doodler::calculate_score(int differnce) {
	int current_high = WINDOW_HEIGHT - points[0].y;
	all_differnce += differnce;
	if (score <= current_high + all_differnce)
		score = current_high + all_differnce;
}
int Doodler::get_score() { return score; }
void Doodler::check_high(Window* window, Entities entities) {
	if (points[3].y > WINDOW_HEIGHT)
		game_over(this, window, entities);
}
void Doodler::change_character_info(int y_speed, int height, bool can_jump) {
	vy = y_speed;
	high = height;
	colided = true;
	is_going_up = can_jump;
	times = 0;
}
bool Doodler::check_colide(Entity* entity, Point point1, Point point2, Type type) {
	if (type == ENEMY) {
		if (entity->is_collide(vy, point1, point2))
			return true;
		else
			return false;
	}
	if (head_side_right){
		Point temp = point1;
		temp.x -= NOSE_SIZE;
		if (entity->is_collide(vy, temp, point2))
			return true;
		else return false;
	}
	else {
		Point temp = point2;
		temp.x += NOSE_SIZE;
		if (entity->is_collide(vy, point1, temp))
			return true;
		else return false;
	}
}
void Doodler::update(Entities entities, int differnce, Window* window) {
	colided = false;
	high = 0;
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->get_type() == ENEMY) {
			if (check_colide(entities[i], points[1], points[3], ENEMY)) {
				game_over(this, window, entities);
			}
		}
		else if (entities[i]->get_type() == SPRING) {
			if (!is_going_up) {
				if (check_colide(entities[i], points[1], points[3], SPRING)) {
					change_character_info(2 * JUMPING_SPEED, entities[i]->get_high());
					break;
				}
			}
		}
		else if (entities[i]->get_type() == PLATFORM || entities[i]->get_type() == MOVING_PLATFORM) {
			if (!is_going_up) {
				if (check_colide(entities[i], points[1], points[0], PLATFORM)) {
					change_character_info(JUMPING_SPEED, entities[i]->get_high());
					break;
				}
			}
		}
		else if (entities[i]->get_type() == BROKEN_PLATFORM) {
			if (!is_going_up) {
				if (check_colide(entities[i], points[1], points[0], BROKEN_PLATFORM)) {
					change_character_info(vy, entities[i]->get_high(), false);
					break;
				}
			}
		}
	}

	calculate_score(differnce);
	check_high(window,entities);
	vertical_movement(colided, high, differnce);
}
bool Doodler::out_from_right() {
	if (points[3].x > WINDOW_WIDTH - (CHARACTER_WIDTH / 2))
		return true;
	return false;
}
bool Doodler::out_from_left() {
	if (points[3].x < -CHARACTER_WIDTH / 2)
		return true;
	return false;
}
void Doodler::move_to(string side) {
	if (side == RIGHT_SIDE) {
		points[3].x = WINDOW_WIDTH - (CHARACTER_WIDTH / 2);
		points[0].x = WINDOW_WIDTH - (CHARACTER_WIDTH / 2);
		points[1].x = WINDOW_WIDTH + (CHARACTER_WIDTH / 2);
		points[2].x = WINDOW_WIDTH + (CHARACTER_WIDTH / 2);
	}
	else {
		points[3].x = -CHARACTER_WIDTH / 2;
		points[0].x = -CHARACTER_WIDTH / 2;
		points[1].x = CHARACTER_WIDTH / 2;
		points[2].x = CHARACTER_WIDTH / 2;
	}
}
bool Doodler::is_collide(int v, Point point1, Point point2) { return false; }
void Doodler::horizontal_movement(char& pressededchar, bool& key_pressed, Window* window) {
	if (key_pressed) {
		if (pressededchar == MOVING_RIGHT_CHAR) {
			head_side_right = true;
			vx = HORIZONTAL_SPEED;
		}
		else if (pressededchar == MOVING_LEFT_CHAR) {
			vx = -HORIZONTAL_SPEED;
			head_side_right = false;
		}
	}
	else {
		vx = 0;
	}

	for (int point_counter = 0; point_counter < 4; point_counter++)
		points[point_counter].x += vx;

	if (out_from_right())
		move_to(LEFT_SIDE);

	if (out_from_left())
		move_to(RIGHT_SIDE);

}

void Doodler::vertical_movement(bool colided, int entity_height, int difference){
	if (colided == false){
		for (int point_counter = 0; point_counter < 4; point_counter++)
			points[point_counter].y -= vy * TIME;
	}
	else{
		points[0].y = entity_height;
		points[1].y = entity_height;
		points[2].y = entity_height - CHARACTER_HEIGHT;
		points[3].y = entity_height - CHARACTER_HEIGHT;
	}

	for (int point_counter = 0; point_counter < 4; point_counter++)
		points[point_counter].y += difference;

	vy -= ACCELERATION * TIME;

	if (vy < 0)
		is_going_up = false;
}
void Doodler::draw(Window* window) {
	if (head_side_right && (colided || times < REPETITION_TIMES))
		window->draw_img(CHARACTER_RIGHT_JUMPING_IMAGE,
			Rectangle(points[3].x, points[3].y + LEG_SIZE, CHARACTER_WIDTH, CHARACTER_HEIGHT - LEG_SIZE));
	else if (colided || times < REPETITION_TIMES)
		window->draw_img(CHARACTER_LEFT_JUMPING_IMAGE,
			Rectangle(points[3].x, points[3].y + LEG_SIZE, CHARACTER_WIDTH, CHARACTER_HEIGHT - LEG_SIZE));
	else if (head_side_right)
		window->draw_img(CHARACTER_RIGHT_IMAGE,
			Rectangle(points[3].x, points[3].y, CHARACTER_WIDTH, CHARACTER_HEIGHT));
	else
		window->draw_img(CHARACTER_LEFT_IMAGE,
			Rectangle(points[3].x, points[3].y, CHARACTER_WIDTH, CHARACTER_HEIGHT));
	times++;
	window->show_text(to_string(score), Point(0, 0), BLACK, FONT);
}

void game_over(Doodler* character, Window* window,Entities entities) {
	window->clear();
	window->draw_img(BACKGROUND_IMAGE);
	window->show_text("Game over!", Point(WINDOW_WIDTH/5, WINDOW_HEIGHT/4), RED, FONT, FONT_SIZE);
	window->show_text("Your score:", 
		Point(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 4 + 2 * FONT_SIZE), BLACK, FONT, FONT_SIZE);
	window->show_text(to_string(character->get_score()), 
		Point(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 4 + 4 * FONT_SIZE), BLACK, FONT, FONT_SIZE);
	Event e;
	window->update_screen();
	while (true) {
		e = window->poll_for_event();
		if (e.get_type() == Event::KEY_PRESS || e.get_type() == Event::EventType::QUIT)
			break;
	}
	for (int i = 0; i < entities.size(); i++)
		delete entities[i];
	delete character;
	exit(0);
}