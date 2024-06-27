#ifndef PROTAGONIST_H
#define PROTAGONIST_H
#include<graphics.h>
#include <algorithm>
#include"screen.h"
class Protagonist {
public:
    struct Pair_ {
        int x_;
        int y_;
    };
    Screen& screen;
    bool skill_ninja;
private:
    int radius;
    struct Pair_ coordinate;
public:
    Protagonist(int r,int y, bool nin, Screen& scr);  // 构造函数
    ~Protagonist(); // 析构函数
    int getterRadius() const { return radius; }
    struct Pair_ getterPair() const { return coordinate; }
    void drawProtagonist();
    void fallDown(int g,int t);
    void flyUp(int g, int t);
};

#endif // PROTAGONIST_H
