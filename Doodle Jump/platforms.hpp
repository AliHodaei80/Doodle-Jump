#ifndef PLATFORM_H
#define PLATFORM_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include "rsdl.hpp"
#include"entities.hpp"

using namespace std;

const int PLATFORM_HEIGHT = 27;
const int PLATFORM_WIDTH = 90;
const string PLATFORM_IMAGE = "platform.png";
const string MOVING_PLATFORM_IMAGE = "moving_platform.png";
const string BROKEN_PLATFORM_IMAGE1 = "broken_platform1.png";
const string BROKEN_PLATFORM_IMAGE2 = "broken_platform2.png";
const string BROKEN_PLATFORM_IMAGE3 = "broken_platform3.png";
const string BROKEN_PLATFORM_IMAGE4 = "broken_platform4.png";

class Platform : public Entity {
public:
	Platform(int x, int y);
	virtual void draw(Window* window);
	virtual bool is_collide(int v, Point point1, Point point2);
};
class Moving_platform : public Platform {
private:
	bool moving_right;
public:
	Moving_platform(int x, int y);
	virtual void update();
	virtual void draw(Window* window);
};

class Broken_platform : public Platform {
private:
	int times;
	bool is_broken;
	int vy;
public:
	Broken_platform(int x, int y);
	void draw(Window* window);
	virtual void update();
	virtual bool is_collide(int v, Point point1, Point point2);
};

#endif
