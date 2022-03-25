#ifndef GAME2048_H
#define GAME2048_H

#include <QMatrix4x4>
#include <QRandomGenerator>
#include <QPoint>
#include <QString>
#include "Snake.h"

#define GRID_SIZE  100
#define GAP        10
#define GRID_NUM    4

typedef enum Game2048Direct {
    None, KeyUP, KeyDOWN, KeyLEFT, KeyRIGHT
}Game2048Direct;

class GameTwo
{
public:
    GameTwo();
    // 构建一个4*4的矩阵存储地图
    QMatrix4x4 mapMatrix;
    // 按键按下的方向
    Game2048Direct direct;
    // 记录最大值
    int maxPoint;
    // 游戏的状态
    GameState state;
    // 生成随机位置
    QPoint randomPos();
    // 获取等于1的位置
    QList<QPoint> getPosEqualOne();
    // 重新初始化
    void initMap();
    // 进行逻辑实现，相同且相近的元素相加，在移动到最边界
    QList<float> logical(QList<float> data);
    // 进行矩阵的更新
    void updateMatrix();
    // 获取矩阵的最大值
    void getMaxMatrix();
    // 生成随机数
    int getRandomNum();
};

#endif // GAME2048_H
