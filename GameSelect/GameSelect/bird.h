#ifndef BIRD_H
#define BIRD_H
#include <QList>
#include <QPoint>
#include <QRandomGenerator>
#include "Snake.h"
#define UP_SPEED        10
#define DOWN_SPEED      5
#define SPEED           5
#define Bird_MAP_HEIGHT      400

typedef enum BirdState {
    BirdUP, BirdDOWN
}BirdState;

class Bird
{
public:
    Bird();
    // 得分
    int score;
    // 游戏状态
    GameState state;
    // 鸟的飞行状态
    BirdState birdState;
    // 鸟的当前位置
    QPoint birdPos;
    // 鸟下降的时候的速度的递增统计
    int downCount;
    // 随机生成管道的长度，成对存在
    QList<int> randomPipHeight();
    // 鸟的状态的判断
    void judgeBird(QList<QRect> pipes);
    // 初始化状态
    void initBird();
};

#endif // BIRD_H
