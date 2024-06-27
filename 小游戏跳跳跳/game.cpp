#include "game.h"

#undef max
#undef min
Game::Game(Screen& scr, Obstacle& obs, Protagonist& pro):screen(scr),obstacle(obs),protagonist(pro) {
    // ��ʼ����Ա����
}

// ��������ʵ��
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
        // ��ʼ������ͼ
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
        //��ȡ�û�����
        if(GetAsyncKeyState(VK_LBUTTON)|| GetAsyncKeyState(VK_SPACE)){//���°��� ���
            protagonist.flyUp(1, pressTime);
            pressTime++;
            releaseTime = 0;
        }
        else {//�ͷŰ��� ׹��
            protagonist.fallDown(1, releaseTime);
            pressTime = 0;
            releaseTime++;
        }

        if (GetAsyncKeyState(VK_RBUTTON) || GetAsyncKeyState(VK_LSHIFT)) {//�޵�
            protagonist.skill_ninja = true;
        }
        else {
            protagonist.skill_ninja = false;
        }
        //����Ļ��ǰ�ƶ�
        screen.position = screen.position + 10;

        //ɾ������Ҫ��Ⱦ���ϰ��� ��Լ���� �����������µ��ϰ��ﲹ��
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

    //�ҳ������Ͼ���Բ������ĵ�
    float closestX = std::max(rectLeft, std::min(circleX, rectRight));
    float closestY = std::max(rectBottom, std::min(circleY, rectTop));

    //�����������ĵ����Բ�ĵľ���
    float distanceX = closestX - circleX;
    float distanceY = closestY - circleY;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;

    //�ж��Ƿ񳬹��뾶
    return distanceSquared <= (protagonist.getterRadius() * protagonist.getterRadius());
}
bool Game::cheakCrash() {
    float leftBound = protagonist.getterPair().x_+ screen.position - protagonist.getterRadius();
    float rightBound = protagonist.getterPair().x_+ screen.position + protagonist.getterRadius();

    for (const auto& obs : obstacle.obstacles) {
        if (obs.obstaclePosition <= rightBound && (obs.obstaclePosition + obs.length) >= leftBound) {
            //���С����߽�
            if (protagonist.getterPair().y_ + protagonist.getterRadius() < 0 || 
                protagonist.getterPair().y_ - protagonist.getterRadius() > screen.getterHighth()) {
                return true;
            }
            //�ֱ��ж��Ƿ��������ཻ 
            if (isIntersect(obs.obstaclePosition, obs.obstaclePosition+obs.length,0,obs.topHigh)
                || isIntersect(obs.obstaclePosition, obs.obstaclePosition + obs.length, screen.getterHighth(), screen.getterHighth()-obs.bottomHigh)) {
                return true;
            }
        }
    }
    return false;
}
void Game::createObstacles(int degree) {
    //���Ϊ�����ʼ����һ������
    if (obstacle.obstacles.empty() == true) {
        obstacle.createObstacleRandom(screen.position, screen.position + degree, protagonist.getterRadius(), degree);
    }
    else {
        //��������Ѷ����ɵ�ͼ
        int lastPosition = obstacle.obstacles.back().obstaclePosition + obstacle.obstacles.back().length;
        obstacle.createObstacleRandom(lastPosition + degree+40, lastPosition + degree*2+40, protagonist.getterRadius(),degree);
    }
}