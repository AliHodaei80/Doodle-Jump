#include"other_stuff.hpp"

using namespace std;

Spring::Spring(int x, int y)
	:Entity(x, y, SPRING_WIDTH, SPRING_HEIGHT){
	type = SPRING;
	is_open = false;
	times = 3;
}
void Spring::draw(Window* window) {
	if (is_open == true || times <= 2)
		window->draw_img(OPEN_SPRING_IMAGE,
			Rectangle(points[3].x, points[3].y - 33, SPRING_WIDTH, OPEN_SPRING_HEIGHT));
	else
		window->draw_img(SPRING_IMAGE,
			Rectangle(points[3].x, points[3].y, SPRING_WIDTH, SPRING_HEIGHT));

	times++;
}
bool Spring::is_collide(int v, Point point1, Point point2)
{
	bool is_on_way = false;
	is_open = false;
	if (points[3].y <= (point1.y - v * TIME) && points[3].y >= point1.y)
		is_on_way = true;
	if ((is_on_way || (point1.y <= points[3].y && point1.y >= points[0].y))
		&& (((point2.x >= points[0].x && point2.x <= points[1].x)
			|| (point1.x >= points[0].x && point1.x <= points[1].x))
			|| (point2.x <= points[0].x && point1.x >= points[1].x))) {

		times = 0;
		is_open = true;
		return true;
	}
	else
		return false;
}