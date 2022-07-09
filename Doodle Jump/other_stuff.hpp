#ifndef OTHER_H
#define OTHER_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include "rsdl.hpp"
#include"entities.hpp"

using namespace std;

const int SPRING_HEIGHT = 33;
const int OPEN_SPRING_HEIGHT = 66;
const int SPRING_WIDTH = 33;
const string SPRING_IMAGE = "spring.png";
const string OPEN_SPRING_IMAGE = "open_spring.png";


class Spring :public Entity {
private:
	bool is_open;
	int times;
public:
	Spring(int x, int y);
	virtual void draw(Window* window);
	virtual bool is_collide(int v, Point point1, Point point2);
};
#endif
