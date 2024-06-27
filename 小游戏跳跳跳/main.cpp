#include "game.h"
int main() {
	Screen scr(0, 800, 400);
	std::string mode = "";
	Obstacle obs(mode, scr);
	Protagonist pro(30, scr.getterHighth() / 2,false, scr);
	Game game(scr,obs,pro);
	game.run_();
	return 0;
}