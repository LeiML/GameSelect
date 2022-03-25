#include "Snake.h"

Snake::Snake():score(0)                    // 初始化得分为0
  , snakeState(DEAD)            // 初始化蛇的状态为死亡
  , direct(RIGHT)             // 初始化游戏的状态
  , gameState(STOP)
{
    this->head = QPoint(1, 0);
    // 添加头部与第一节身体
    this->body.append(this->head);
    this->body.append(QPoint(0, 0));
}

bool Snake::judgeFoodState(QPoint foodPos)
{
    return foodPos == this->head;
}

bool Snake::judgeSnakeState()
{
    for(int i=1; i<this->body.length(); i++) {
        if (this->body.at(i) == this->head) return true;
    }
    if (this->head.x() < 0 || this->head.y() < 0 ||
            this->head.y() >= CELL_NUM || this->head.x() >= CELL_NUM)
        return true;
    return false;
}

void Snake::initSnake()
{
    snakeState = DEAD;            // 初始化蛇的状态为死亡
    direct = RIGHT;            // 初始化游戏的状态
    gameState = STOP;
    this->body.clear();
    this->score = 0;
    this->head = QPoint(1, 0);
    // 添加头部与第一节身体
    this->body.append(this->head);
    this->body.append(QPoint(0, 0));
}




SnakeFood::SnakeFood()
{
    this->RandomFood();
}

void SnakeFood::RandomFood()
{
    int x = QRandomGenerator::global()->bounded(0, CELL_NUM);
    int y = QRandomGenerator::global()->bounded(0, CELL_NUM);
    this->foodPos = QPoint(x, y);
}

