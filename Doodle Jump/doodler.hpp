#ifndef DOODLER_H
#define DOODLER_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include "rsdl.hpp"
#include"entities.hpp"

using namespace std;

const int CHARACTER_HEIGHT = 82;
const int CHARACTER_WIDTH = 84;
const int NOSE_SIZE = 20;
const int LEG_SIZE = 10;
const int HORIZONTAL_SPEED = 10;
const int JUMPING_SPEED = 500;
const string CHARACTER_RIGHT_IMAGE = "character_right.png";
const string CHARACTER_RIGHT_JUMPING_IMAGE = "character_right_jumping.png";
const string CHARACTER_LEFT_IMAGE = "character_left.png";
const string CHARACTER_LEFT_JUMPING_IMAGE = "character_left_jumping.png";
const string RIGHT_SIDE = "right_side";
const string LEFT_SIDE = "left_side";
const char MOVING_RIGHT_CHAR = 'd';
const char MOVING_LEFT_CHAR = 'a';
const string FONT = "FreeSansOblique-ol30.ttf";
const int FONT_SIZE = 60;

class Doodler :public Entity {
private:
	int all_differnce;
	int score;
	bool colided;
	bool is_going_up;
	int vy;
	int vx;
	bool head_side_right;
	int times;
	int high;
public:
	Doodler(int x, int y);
	int get_speed();
	int get_under_high();
	void calculate_score(int differnce);
	int get_score();
	void check_high(Window* window, Entities entities);
	void change_character_info(int y_speed, int height, bool can_jump = true);
	bool check_colide(Entity* entity, Point point1, Point point2, Type type);
	void update(Entities entities, int differnce, Window* window);
	bool out_from_right();
	bool out_from_left();
	void move_to(string side);
	virtual bool is_collide(int v, Point point1, Point point2);
	void horizontal_movement(char& pressededchar, bool& key_pressed, Window* window);
	void vertical_movement(bool colided, int entity_height, int difference);
	virtual void draw(Window* window);
};
void game_over(Doodler* character, Window* window,Entities entities);

#endif
