#ifndef GAMESELECT_H
#define GAMESELECT_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <QKeyEvent>
#include <QEventLoop>
#include <QCoreApplication>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QTimeLine>
#include "Snake.h"
#include "Game2048.h"
#include "bird.h"
#define OPTION_TXT "         [温馨提示]按下空格键(SPACE)继续/暂停/开始游戏        \n[Warm tip]Press The Space Key To Continue/Pause/Start The Game"

QT_BEGIN_NAMESPACE
namespace Ui { class GameSelect; }
QT_END_NAMESPACE

typedef enum GameMode {
    GameIce, GameSnake, Game2048, GameBird
} GameMode;

class GameSelect : public QWidget
{
    Q_OBJECT

public:
    GameSelect(QWidget *parent = nullptr);
    ~GameSelect();
private:
    Ui::GameSelect *ui;
    QGraphicsScene *scene;
    // 创建一个蛇类对象
    Snake *snake;
    // 创建一个食物类对象
    SnakeFood *food;
    // 食物的item
    QGraphicsEllipseItem *foodItem;
    // 创建一个定时器对象
    QTimer *timer;
    // 游戏状态，得分
    QGraphicsTextItem textItem;
    // 游戏状态的文字提示
    QGraphicsTextItem textState;
    // 存储蛇的头部位置
    QGraphicsEllipseItem* headItem;
    // 存储操作方式
    QGraphicsTextItem optionText;
    // 游戏的模式
    GameMode mode;
private:
    void createGameModeMap();
private:
    void updateBody(const QPoint& headPos);
    void createSnake();
    void createSnakeFood();
    void createSnakeBody(QPoint pos);
    void clearScene();
    void Sleep(int msec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(msec);
        while(QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
private slots:
    void timeOut();
    // 刷新管道的位置
    void updatePipePos();
    // 按键的选择响应
    void SelectGame();
protected:
    void keyReleaseEvent(QKeyEvent *event);
    // 按下按键
    void keyPressEvent(QKeyEvent *event);
// 2048游戏的基本定义位置
private:
    GameTwo *game;
private:
    void create2048Map();
    void updateMap();
// 小鸟的基本定义位置
private:
    // 定义鸟的图片
    QGraphicsPixmapItem bird;
    // 定义鸟的类
    Bird niao;
    // 定义两个管道，上管道与下管道
    QGraphicsPixmapItem pipUp;
    QGraphicsPixmapItem pipDown;
    // 管道移动，开始游戏的定时器
    QTimer *birdTimer;
    // 管道的位置
    int pipPos;
private:
    void createBirdMap();
    void updateBirdMap();
    void updateBirdPos();
// 加载冰墩墩
private:
    void createIceMap();
};
#endif // GAMESELECT_H
