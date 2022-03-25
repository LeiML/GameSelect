#include "bird.h"


Bird::Bird() : score(0)
  , state(GameState::STOP)
  , birdState(BirdDOWN)
  , birdPos(QPoint(200, 200))
  , downCount(1)
{
}

QList<int> Bird::randomPipHeight()
{
    QList<int>list;
    while (1) {
        int x1 = QRandomGenerator::global()->bounded(0, 300);
        int x2 = QRandomGenerator::global()->bounded(0, 300);
        if (Bird_MAP_HEIGHT - x1 - x2 > 70) {
            list.append(x1);
            list.append(x2);
            break;
        }
    }
    return list;
}

void Bird::judgeBird(QList<QRect> pipes)
{
    // 鸟的位置的最低点大于400，死亡，碰到了管子，死亡
    if (this->birdPos.y()+35 > Bird_MAP_HEIGHT) {
        this->state = GameState::STOP;
        return;
    }
    // 碰到管子的位置
    QRect rect_n = QRect(this->birdPos.x(), this->birdPos.y(), 35, 35);
    qDebug() << rect_n;
    qDebug() << pipes;
    for (int i=0; i<pipes.length(); i++) {
        qDebug() << "相交：" << rect_n.intersects(pipes.at(i));
        if (rect_n.intersects(pipes.at(i))) {
            this->state = GameState::STOP;
            return;
        }
    }
}

void Bird::initBird()
{
    score = 0;
    state = GameState::STOP;
    birdState = BirdDOWN;
    birdPos = QPoint(200, 200);
    downCount = 1;
}
