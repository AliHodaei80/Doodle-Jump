#include"platforms.hpp"

using namespace std;

Platform::Platform(int x, int y)
	:Entity(x, y, PLATFORM_WIDTH, PLATFORM_HEIGHT){
	type = PLATFORM;
}
void Platform::draw(Window* window) {

	window->draw_img(PLATFORM_IMAGE,
		Rectangle(points[3].x, points[3].y, PLATFORM_WIDTH, PLATFORM_HEIGHT));

}
bool Platform::is_collide(int v, Point point1, Point point2){
	bool is_on_way = false;
	if (points[3].y <= (point1.y - v * TIME) && points[3].y >= point1.y)
		is_on_way = true;
	if ((is_on_way || (point1.y <= points[3].y && point1.y >= points[0].y))
		&& ((point1.x >= points[0].x && point1.x <= points[1].x)
			|| (point2.x >= points[0].x && point2.x <= points[1].x)))
		return true;

	else
		return false;
}


Moving_platform::Moving_platform(int x, int y)
	:Platform(x, y){
	moving_right = true;
	type = MOVING_PLATFORM;
}
void Moving_platform::update() {
	if (moving_right){
		for (int point_counter = 0; point_counter < 4; point_counter++)
			points[point_counter].x++;
	}
	else {
		for (int point_counter = 0; point_counter < 4; point_counter++)
			points[point_counter].x--;
	}

	if (points[0].x == 0) {
		moving_right = true;
	}
	else if (points[1].x == WINDOW_WIDTH) {
		moving_right = false;
	}
}
void Moving_platform::draw(Window* window) {
	window->draw_img(MOVING_PLATFORM_IMAGE,
		Rectangle(points[3].x, points[3].y, PLATFORM_WIDTH, PLATFORM_HEIGHT));
}


Broken_platform::Broken_platform(int x, int y)
	:Platform(x, y)
{
	vy = 0;
	times = 0;
	is_broken = false;
	type = BROKEN_PLATFORM;
}
void Broken_platform::draw(Window* window) {
	if (!is_broken)
		window->draw_img(BROKEN_PLATFORM_IMAGE1,
			Rectangle(points[3].x, points[3].y, PLATFORM_WIDTH, PLATFORM_HEIGHT));
	else if (times <= REPETITION_TIMES)
		window->draw_img(BROKEN_PLATFORM_IMAGE2,
			Rectangle(points[3].x, points[3].y, PLATFORM_WIDTH, PLATFORM_HEIGHT));
	else if (times < 2*REPETITION_TIMES)
		window->draw_img(BROKEN_PLATFORM_IMAGE3,
			Rectangle(points[3].x, points[3].y, PLATFORM_WIDTH, PLATFORM_HEIGHT));
	else if (times >= 2*REPETITION_TIMES)
		window->draw_img(BROKEN_PLATFORM_IMAGE4,
			Rectangle(points[3].x, points[3].y, PLATFORM_WIDTH, PLATFORM_HEIGHT));

	times++;
}
void Broken_platform::update() {
	if (is_broken)
	{
		for (int point_counter = 0; point_counter < 4; point_counter++)
			points[point_counter].y -= vy * TIME;
		vy -= ACCELERATION * TIME;
	}

}
bool Broken_platform::is_collide(int v, Point point1, Point point2)
{
	if (is_broken)
		return false;
	bool is_on_way = false;
	if (points[3].y <= (point1.y - v * TIME) && points[3].y >= point1.y)
		is_on_way = true;
	if ((is_on_way || (point1.y <= points[3].y && point1.y >= points[0].y))
		&& ((point1.x >= points[0].x && point1.x <= points[1].x)
			|| (point2.x >= points[0].x && point2.x <= points[1].x)))
	{
		is_broken = true;
		return true;
	}

	else
		return false;
}