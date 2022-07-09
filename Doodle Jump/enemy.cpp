#include"enemy.hpp"

using namespace std;

Enemy::Enemy(int x, int y)
	:Entity(x, y, ENEMY_WIDTH, ENEMY_HEIGHT){
	type = ENEMY;
}
void Enemy::draw(Window* window) {
	window->draw_img(ENEMY_IMAGE,
		Rectangle(points[3].x, points[3].y, ENEMY_WIDTH, ENEMY_HEIGHT));
}
bool Enemy::is_collide(int v, Point point1, Point point2){
	if ((point1.y >= points[3].y && point1.y <= points[0].y)
		&& ((point2.x >= points[0].x && point2.x <= points[1].x)
			|| (point1.x >= points[0].x && point1.x <= points[1].x)))
		return true;

	if ((point2.y <= points[0].y && point2.y >= points[3].y)
		&& ((point2.x >= points[0].x && point2.x <= points[1].x)
			|| (point1.x >= points[0].x && point1.x <= points[1].x)))
		return true;
	if ((point1.x >= points[3].x && point1.x <= points[1].x)
		&& ((point2.y <= points[0].y && point2.y >= points[3].y)
			|| (point1.y <= points[0].y && point1.y >= points[3].y)))
		return true;
	if ((point2.x <= points[2].x && point2.x >= points[0].x)
		&& ((point2.y <= points[1].y && point2.y >= points[2].y)
			|| (point1.y <= points[1].y && point1.y >= points[2].y)))
		return true;

	return false;
}