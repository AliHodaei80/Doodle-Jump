#include"entities.hpp"

using namespace std;

Entity::Entity(int under_mid_point_x, int under_mid_point_y, int weight, int high) {
	int mid_weigh = weight / 2;
	points[0].x = under_mid_point_x - mid_weigh;
	points[0].y = WINDOW_HEIGHT - under_mid_point_y;
	points[1].x = under_mid_point_x + mid_weigh;
	points[1].y = WINDOW_HEIGHT - (under_mid_point_y);
	points[2].x = under_mid_point_x + mid_weigh;
	points[2].y = WINDOW_HEIGHT - (under_mid_point_y + high);
	points[3].x = under_mid_point_x - mid_weigh;
	points[3].y = WINDOW_HEIGHT - (under_mid_point_y + high);
}
int Entity::get_high() { return points[3].y; }
string Entity::get_type() { return type; }
void Entity::update() {};
void Entity::update_high(int difference) {
	if (difference > 0) {
		for (int point_counter = 0; point_counter < 4; point_counter++)
			points[point_counter].y += difference;
	}
}