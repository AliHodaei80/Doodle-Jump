#ifndef ENEMY_H
#define ENEMY_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include "rsdl.hpp"
#include"entities.hpp"

using namespace std;

const int ENEMY_HEIGHT = 138;
const int ENEMY_WIDTH = 102;
const string ENEMY_IMAGE = "enemy.png";

class Enemy : public Entity {
public:
	Enemy(int x, int y);
	virtual void draw(Window* window);
	virtual bool is_collide(int v, Point point1, Point point2);
};

#endif
