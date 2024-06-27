#include "game.h"

#undef max
#undef min
Game::Game(Screen& scr, Obstacle& obs, Protagonist& pro):screen(scr),obstacle(obs),protagonist(pro) {
    // 初始化成员变量
}

// 析构函数实现
Game::~Game() {

}
void Game::run_() {
    initgraph(screen.getterLength(), screen.getterHighth());
    
    endlessMode();
}
void Game::selectmode() {
    return;
}
void Game::endlessMode() {

    for (int i = 0;i < 10;i++) {
        createObstacles(80);
    }
    //obstacle.addObstacle(Obstacle::ObstacleStruct{ 150,150,50,20 });
    //obstacle.addObstacle(Obstacle::ObstacleStruct{ 150,150,50,100 });
    screen.position = 0;
    /*while (cheakCrash(protagonist, obstacle) == false)*/
    int pressTime = 0;
    int releaseTime = 0;
    MOUSEMSG msg;
    while(1) {
        // 开始批量绘图
        BeginBatchDraw();
        cleardevice();
        obstacle.drawObstacle();
        protagonist.drawProtagonist();

        if (cheakCrash()&& protagonist.skill_ninja==false) {
            settextcolor(RED);
            outtextxy(0,0,L"crush");
        }
        else {
            settextcolor(WHITE);
            outtextxy(0,0,L"nocrush");
        }
        EndBatchDraw();
        //获取用户操作
        if(GetAsyncKeyState(VK_LBUTTON)|| GetAsyncKeyState(VK_SPACE)){//按下按键 起飞
            protagonist.flyUp(1, pressTime);
            pressTime++;
            releaseTime = 0;
        }
        else {//释放按键 坠落
            protagonist.fallDown(1, releaseTime);
            pressTime = 0;
            releaseTime++;
        }

        if (GetAsyncKeyState(VK_RBUTTON) || GetAsyncKeyState(VK_LSHIFT)) {//无敌
            protagonist.skill_ninja = true;
        }
        else {
            protagonist.skill_ninja = false;
        }
        //将屏幕向前移动
        screen.position = screen.position + 10;

        //删除不需要渲染的障碍物 节约性能 并重新生成新的障碍物补充
        if (obstacle.deleteObstacles(0)) {
            int lastPosition = obstacle.obstacles.back().obstaclePosition + obstacle.obstacles.back().length;
            createObstacles(80);
        }
        Sleep(30);
    }
    
}
bool Game::isIntersect(float rectLeft, float rectRight, float rectTop, float rectBottom) {

    float circleX = protagonist.getterPair().x_ + screen.position;
    float circleY = protagonist.getterPair().y_;

    //找出矩形上距离圆心最近的点
    float closestX = std::max(rectLeft, std::min(circleX, rectRight));
    float closestY = std::max(rectBottom, std::min(circleY, rectTop));

    //计算矩形最近的点距离圆心的距离
    float distanceX = closestX - circleX;
    float distanceY = closestY - circleY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;

    //判断是否超过半径
    return distanceSquared <= (protagonist.getterRadius() * protagonist.getterRadius());
}
bool Game::cheakCrash() {
    float leftBound = protagonist.getterPair().x_+ screen.position - protagonist.getterRadius();
    float rightBound = protagonist.getterPair().x_+ screen.position + protagonist.getterRadius();

    for (const auto& obs : obstacle.obstacles) {
        if (obs.obstaclePosition <= rightBound && (obs.obstaclePosition + obs.length) >= leftBound) {
            //如果小球出边界
            if (protagonist.getterPair().y_ + protagonist.getterRadius() < 0 || 
                protagonist.getterPair().y_ - protagonist.getterRadius() > screen.getterHighth()) {
                return true;
            }
            //分别判断是否与上下相交 
            if (isIntersect(obs.obstaclePosition, obs.obstaclePosition+obs.length,0,obs.topHigh)
                || isIntersect(obs.obstaclePosition, obs.obstaclePosition + obs.length, screen.getterHighth(), screen.getterHighth()-obs.bottomHigh)) {
                return true;
            }
        }
    }
    return false;
}
void Game::createObstacles(int degree) {
    //如果为空则初始化第一个参数
    if (obstacle.obstacles.empty() == true) {
        obstacle.createObstacleRandom(screen.position, screen.position + degree, protagonist.getterRadius(), degree);
    }
    else {
        //否则根据难度生成地图
        int lastPosition = obstacle.obstacles.back().obstaclePosition + obstacle.obstacles.back().length;
        obstacle.createObstacleRandom(lastPosition + degree+40, lastPosition + degree*2+40, protagonist.getterRadius(),degree);
    }
}