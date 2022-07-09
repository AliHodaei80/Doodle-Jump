#ifndef ENTITIES_H
#define ENTITIES_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include "rsdl.hpp"
using namespace std;

const string BACKGROUND_IMAGE = "background.png";
const string PLATFORM = "platform";
const string MOVING_PLATFORM = "mplatform";
const string BROKEN_PLATFORM = "bplatform";
const string ENEMY = "enemy";
const string SPRING = "spring";
const int WINDOW_HEIGHT = 768;
const int WINDOW_WIDTH = 480;
const float TIME = 0.04;
const int ACCELERATION = 500;
const int REPETITION_TIMES = 3;


typedef string Type;
class Entity {
protected:
	Point points[4];
	string type;
public:
	Entity(int under_mid_point_x, int under_mid_point_y, int weight, int high);
	int get_high();
	virtual bool is_collide(int v, Point point1, Point point2) = 0;
	virtual Type get_type();
	virtual void update();
	virtual void draw(Window* window) = 0;
	void update_high(int difference);
};
typedef vector<Entity*> Entities;

#endif
