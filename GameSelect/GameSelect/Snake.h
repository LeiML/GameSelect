#ifndef SNAKE_H
#define SNAKE_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QPoint>
#include <QTimer>
#include <QPen>
#include <QObject>
#include <QKeyEvent>
#include <QWidget>
#include <QRandomGenerator>

#define CELL_SIZE   15
#define CELL_NUM    30
#define MAP_WIDTH   450
#define MAP_HEIGHT  450
// 判断蛇的状态
typedef enum SnakeState {
    ALIVE=1, DEAD=0
}SnakeState;

// 蛇行动的方向
typedef enum SnakeDirect {
    UP, DOWN, LEFT, RIGHT
}SnakeDirect;

// 游戏状态的定义
typedef enum GameState {
    START=1, STOP=0
}GameState;

// 食物类
class SnakeFood{
public:
    SnakeFood();
    ~SnakeFood();
    QPoint foodPos;
    void RandomFood();
};

// 蛇的基本类
class Snake
{
public:
    Snake();
public:
    // 判断食物是否被吃掉
    bool judgeFoodState(QPoint foodPos);
    // 判断是否死亡
    bool judgeSnakeState();
    // 重新初始化参数
    void initSnake();
public:
    // 得分
    int score;
    // 蛇的状态
    SnakeState snakeState;
    // 食物状态
    SnakeState FoodState;
    // 蛇行动的方向
    SnakeDirect direct;
    // 蛇头的位置坐标
    QPoint head;
    // 蛇的身体长度
    QList<QPoint>body;
    // 游戏的状态
    GameState gameState;
};

#endif // SNAKE_H
