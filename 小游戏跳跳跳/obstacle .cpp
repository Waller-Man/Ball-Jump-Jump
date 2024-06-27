#include"obstacle .h"
#undef max
#undef min
Obstacle::Obstacle(std::string& m, Screen& scr):model(m),screen(scr), gen(std::chrono::system_clock::now().time_since_epoch().count()) {
    //用户选择了模式 从文件中读取并初始化
    if (!model.empty()) {
        std::string filename = model + ".txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int topHigh, bottomHigh, length, obstaclePosition;
            if (iss >> topHigh >> bottomHigh >> length>> obstaclePosition) {
                addObstacle(ObstacleStruct{ topHigh, bottomHigh, length, obstaclePosition });
            }
            else {
                std::cerr << "Error: Invalid data format in " << filename << std::endl;
            }
        }
        file.close();
    }
}

Obstacle::~Obstacle() {
    
}
void Obstacle::drawObstacle() {
    //只需要渲染位于屏幕中的实体
    for (int i = 0;i < obstacles.size() && obstacles[i].obstaclePosition < screen.position + screen.getterLength();i++) {
        if (obstacles.empty() == false) {
            //画上半部分障碍物
            line(obstacles[i].obstaclePosition - screen.position, 0, obstacles[i].obstaclePosition - screen.position, obstacles[i].topHigh);
            line(obstacles[i].obstaclePosition - screen.position, obstacles[i].topHigh, obstacles[i].obstaclePosition - screen.position + obstacles[i].length, obstacles[i].topHigh);
            line(obstacles[i].obstaclePosition - screen.position + obstacles[i].length, obstacles[i].topHigh, obstacles[i].obstaclePosition - screen.position + obstacles[i].length, 0);
            //画下半部分障碍物
            line(obstacles[i].obstaclePosition - screen.position, screen.getterHighth(), obstacles[i].obstaclePosition - screen.position, screen.getterHighth() - obstacles[i].bottomHigh);
            line(obstacles[i].obstaclePosition - screen.position, screen.getterHighth() - obstacles[i].bottomHigh, obstacles[i].obstaclePosition - screen.position + obstacles[i].length, screen.getterHighth() - obstacles[i].bottomHigh);
            line(obstacles[i].obstaclePosition - screen.position + obstacles[i].length, screen.getterHighth() - obstacles[i].bottomHigh, obstacles[i].obstaclePosition - screen.position + obstacles[i].length, screen.getterHighth());
        }
    }
}
bool Obstacle::deleteObstacles(int i) {
    if (obstacles.empty() == false && obstacles[i].obstaclePosition + obstacles[i].length < screen.position) {//删除不需要渲染的障碍物
        obstacles.erase(obstacles.begin(), obstacles.begin() + i + 1);
        return true;
    }
    return false;
}
void Obstacle::addObstacle(const struct ObstacleStruct& newObstacle) {
    //将障碍物加入向量的时候 确保其的有序性
    auto it = std::lower_bound(obstacles.begin(), obstacles.end(), newObstacle, [](const struct ObstacleStruct& a, const struct ObstacleStruct& b) {
        return a.obstaclePosition < b.obstaclePosition;
        });
    obstacles.insert(it, newObstacle);
}
void Obstacle::createObstacleRandom(int minposition, int maxposition, int radius, int degree) {
    ObstacleStruct newObstacle;
    if (obstacles.empty()) {
        newObstacle.topHigh = getRandomInt(0, screen.getterHighth()/2);
        newObstacle.bottomHigh= getRandomInt(0, std::min(0,(screen.getterHighth() - newObstacle.topHigh - radius * 2 - degree / 3)));
    }
    else {
        int low = std::max(0, obstacles.back().topHigh - ((screen.getterHighth() - degree) / 8));
        int high = std::min(200, obstacles.back().topHigh + ((screen.getterHighth() - degree) / 8));
        newObstacle.topHigh = getRandomInt(low, high);

        low = std::max(0, obstacles.back().bottomHigh - ((screen.getterHighth() - degree) / 8));
        high = std::min(200, obstacles.back().topHigh + ((screen.getterHighth() - degree) / 8));
        //中间的间隙要确保小球能通过
        high = std::min((screen.getterHighth() - newObstacle.topHigh - radius * 2 - degree / 3), high);
        newObstacle.bottomHigh = getRandomInt(low, high);
    }
    newObstacle.length = getRandomInt(20, 80);

    newObstacle.obstaclePosition = getRandomInt(minposition, maxposition);
    addObstacle(newObstacle);
}