#include"protagonist.h"
#undef max
#undef min
Protagonist::Protagonist(int r, int y,bool nin, Screen& scr):radius(r),screen(scr),skill_ninja(nin), coordinate{200, y}  {

}
Protagonist::~Protagonist() {

}
void Protagonist::drawProtagonist() {
	if (skill_ninja == true) {
		setcolor(RGB(135, 206, 250));
	}
	circle(coordinate.x_, coordinate.y_, radius);
	setcolor(WHITE);
}
void Protagonist::fallDown(int g, int t) {
	//int temp = std::min((int)(0.25 * g * t), 10);
	int temp = std::max(t, 4);
	coordinate.y_ = coordinate.y_ + std::min(10, temp);
}
void Protagonist::flyUp(int g, int t) {
	int temp = std::max(t, 3);
	//coordinate.y_ = coordinate.y_ - std::min((int)(0.15 * g * t), 6);
	coordinate.y_ = coordinate.y_ - std::min(8, temp);
}