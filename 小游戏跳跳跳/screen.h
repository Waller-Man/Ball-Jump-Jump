#ifndef SCREEN_H
#define SCREEN_H
#include<graphics.h>
class Screen {
public:
    int position;
private:
    int length;
    int highth;
public:
    Screen(int pos, int len, int high) : position(pos), length(len), highth(high) {}
    int getterLength() const { return length; }
    int getterHighth() const { return highth; }
};

#endif // SCREEN_H
