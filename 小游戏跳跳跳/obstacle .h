#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include<graphics.h>
#include"screen.h"
class Obstacle {
public:
    struct ObstacleStruct {
        int topHigh;
        int bottomHigh;
        int length;
        int obstaclePosition;
    };
    std::vector<ObstacleStruct> obstacles;
private:
    std::mt19937 gen;
    std::string model;
    Screen& screen;

public:
    Obstacle( std::string& m, Screen& scr);  // 构造函数
    ~Obstacle(); // 析构函数
    void drawObstacle();
    bool deleteObstacles(int i);
    void addObstacle(const struct ObstacleStruct& newObstacle);
    void createObstacleRandom(int minposition, int maxposition,int radius,int degree);
private:
    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<> distr(min, max);
        return distr(gen);
    }
};
#endif 