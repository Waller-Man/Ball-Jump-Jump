#ifndef GAME_H
#define GAME_H
#include <algorithm>
#include<graphics.h>
#include "obstacle .h"
#include "protagonist.h"
class Game {
private:
    Screen& screen;
    Obstacle& obstacle;
    Protagonist& protagonist;
public:
    Game(Screen&scr, Obstacle& obs, Protagonist& pro);
    ~Game(); // Îö¹¹º¯Êý
    void run_();
    void selectmode();
    void endlessMode();
    bool cheakCrash();
    
private:
    bool isIntersect(float rectLeft, float rectRight, float rectTop, float rectBottom);
    void createObstacles(int degree);
};
#endif 