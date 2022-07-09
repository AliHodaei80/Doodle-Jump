#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include "rsdl.hpp"
#include"entities.hpp"
#include"platforms.hpp"
#include"enemy.hpp"
#include"other_stuff.hpp"
#include"doodler.hpp"
#include<fstream>

using namespace std;

const int DELAY_TIME = 25;
const string INPUT_TXT = "map.txt";

vector<Entity*> input();
void draw(Window* window, vector<Entity*> shapes, Doodler* character);
void update_shapes(Window* window, Entities entities, Doodler* character, int& difference);
void update(Window* window, Entities entities, Doodler* character);
Entities remove_out_entities(Entities entities);

#endif
