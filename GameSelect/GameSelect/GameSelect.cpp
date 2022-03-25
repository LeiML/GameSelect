#include "GameSelect.h"
#include "ui_GameSelect.h"
#include "Snake.h"

GameSelect::GameSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameSelect)
    , scene(new QGraphicsScene)
    , snake(new Snake)
    , timer(new QTimer)
    , textItem(QGraphicsTextItem())
    , textState(QGraphicsTextItem())
    , optionText(QGraphicsTextItem())
    , mode(GameIce)
    , game(new GameTwo)
    , bird(QGraphicsPixmapItem())
    , niao(Bird())
    , pipUp(QGraphicsPixmapItem())
    , pipDown(QGraphicsPixmapItem())
    , birdTimer(new QTimer)
    , pipPos(390)
{
    ui->setupUi(this);
    ui->graphicsView->setFocus();
    this->scene->setSceneRect(0, 0, 500, 500);
    ui->graphicsView->setScene(this->scene);
    this->setFocusPolicy(Qt::StrongFocus);
    this->scene->clear();
    this->food = new SnakeFood();
    this->createGameModeMap();
    this->timer->setInterval(100);
    this->birdTimer->setInterval(50);
    // 设置定时器的槽函数
    connect(this->timer, &QTimer::timeout, this, &GameSelect::timeOut);
    connect(this->birdTimer, &QTimer::timeout, this, &GameSelect::updatePipePos);
}

GameSelect::~GameSelect()
{
    delete ui;
    delete this->timer;
}

void GameSelect::createGameModeMap()
{
    switch (this->mode) {
    case GameIce: this->createIceMap();break;
    case GameSnake: this->createSnake();break;
    case Game2048: this->create2048Map();break;
    case GameBird: this->createBirdMap();break;
    }
}

void GameSelect::updateBody(const QPoint& headPos)
{
    QList<QPoint>snakeBody = this->snake->body;
    this->snake->body.clear();
    this->snake->body.append(headPos);
    this->headItem->setPos(headPos*15);
    for(int i=0; i<snakeBody.length()-1; i++) {
        this->snake->body.append(snakeBody.at(i));
        this->scene->items().at(i)->setPos(snakeBody.at(i)*15);
    }
    if (this->snake->judgeFoodState(this->food->foodPos)) {
        this->food->RandomFood();
        this->foodItem->setPos(this->food->foodPos * 15);
        this->snake->score++;
        this->textItem.setPlainText("Score: " + QString::number(this->snake->score));
        this->snake->body.append(snakeBody.at(snakeBody.length()-1));
        this->createSnakeBody(snakeBody.at(snakeBody.length()-1));
    }
}

void GameSelect::createSnake()
{
    this->scene->update();
    this->snake->initSnake();
    this->clearScene();
    // 设置得分记录
    this->textItem.setPlainText("Score: " + QString::number(this->snake->score));
    this->optionText.setPlainText(OPTION_TXT);
    this->textItem.setPos(175, -40);
    this->optionText.setPos(-10, 450);
    QFont font;
    font.setBold(true);
    font.setPixelSize(25);
    font.setFamily("The New Roman");
    this->textItem.setFont(font);
    font.setPixelSize(15);
    this->optionText.setDefaultTextColor(QColor(255, 12, 50));
    this->optionText.setFont(font);
    this->scene->addItem(&this->textItem);
    this->scene->addItem(&this->optionText);
    // 绘制地图矩形框
    QGraphicsRectItem *rectItem = new QGraphicsRectItem(0, 0, 450, 450);
    rectItem->setBrush(QColor(100, 200, 100));
    this->scene->addItem(rectItem);
    for (int j=0; j<CELL_NUM+1; j++) {
        QGraphicsLineItem *lineItem_1 = new QGraphicsLineItem;
        QGraphicsLineItem *lineItem_2 = new QGraphicsLineItem;
        lineItem_1->setLine(j*CELL_SIZE, 0, j*CELL_SIZE, 450);
        lineItem_2->setLine(0, j*CELL_SIZE, 450, j*CELL_SIZE);
        this->scene->addItem(lineItem_1);
        this->scene->addItem(lineItem_2);
    }
    this->createSnakeFood();
    int lens = this->snake->body.length();
    // 创建蛇的身体
    for(int i=0; i<lens; i++) {
        if (i == 0) {
            this->headItem = new QGraphicsEllipseItem(0, 0, 15, 15);
            this->headItem->setBrush(QColor(255, 10, 85));
            this->headItem->setPos(this->snake->body.at(i)*15);
            this->scene->addItem(this->headItem);
        } else {
            QGraphicsRectItem *Item = new QGraphicsRectItem(0, 0, 15, 15);
            Item->setBrush(QColor(10, 10, 200));
            Item->setPos(this->snake->body.at(i)*15);
            this->scene->addItem(Item);
        }
    }
}

void GameSelect::createSnakeFood()
{
    this->foodItem = new QGraphicsEllipseItem(0, 0, 15, 15);
    this->foodItem->setBrush(QColor(255, 0, 255));
    this->foodItem->setPos(this->food->foodPos * 15);
    this->scene->addItem(this->foodItem);
}

void GameSelect::createSnakeBody(QPoint pos)
{
    QGraphicsRectItem *Item = new QGraphicsRectItem(0, 0, 15, 15);
    Item->setBrush(QColor(10, 10, 200));
    Item->setPos(pos*15);
    this->scene->addItem(Item);
}

void GameSelect::clearScene()
{
    for(QGraphicsItem *item: this->scene->items()) {
        this->scene->removeItem(item);
    }
}

void GameSelect::timeOut()
{
    this->scene->update();
    QPoint nextHead = this->snake->head;
    switch (this->snake->direct) {
    // 向上走
    case SnakeDirect::UP: nextHead.setY(nextHead.y()-1);break;
    // 向下走
    case SnakeDirect::DOWN: nextHead.setY(nextHead.y()+1);break;
    // 向右走
    case SnakeDirect::RIGHT:nextHead.setX(nextHead.x()+1);break;
    // 向左走
    case SnakeDirect::LEFT:nextHead.setX(nextHead.x()-1);break;
    }
    this->snake->head = nextHead;
    this->updateBody(nextHead);
    if (this->snake->judgeSnakeState()) {
        this->textState.setPlainText("Game  Over");
        this->textState.setPos(130, 150);
        this->scene->addItem(&this->textState);
        this->snake->initSnake();
        this->timer->stop();
        return;
    }
}

void GameSelect::updatePipePos()
{
    this->updateBirdMap();
    if (this->pipPos < 80) this->pipPos = 390;
    else this->pipPos -= SPEED;
    if (this->niao.birdState == BirdDOWN) {
        this->niao.birdPos.setY(this->niao.birdPos.y()+DOWN_SPEED*this->niao.downCount);
        this->niao.downCount += 1;
    }
    this->updateBirdPos();
    if (this->niao.state == GameState::STOP) {
        this->birdTimer->stop();
    }
}

void GameSelect::SelectGame()
{
    if (this->timer->isActive())
        this->timer->stop();
    if (this->birdTimer->isActive())
        this->birdTimer->stop();
    this->clearScene();
    if (this->sender()->objectName() == "pushButton_4")
        this->mode = GameMode::GameIce;
    else if (this->sender()->objectName() == "pushButton")
        this->mode = GameMode::GameSnake;
    else if (this->sender()->objectName() == "pushButton_2")
        this->mode = GameMode::Game2048;
    else this->mode = GameMode::GameBird;
    ui->graphicsView->setFocus();
    ui->label->setText(qobject_cast<QPushButton*>(this->sender())->text());
    this->createGameModeMap();
}

void GameSelect::keyReleaseEvent(QKeyEvent *event)
{
    if (this->mode == GameSnake) {
        switch (event->key()) {
        case Qt::Key_Up:if (this->snake->direct == SnakeDirect::DOWN)break;this->snake->direct = SnakeDirect::UP;break;
        case Qt::Key_Down:if (this->snake->direct == SnakeDirect::UP)break;this->snake->direct = SnakeDirect::DOWN;break;
        case Qt::Key_Right:if (this->snake->direct == SnakeDirect::LEFT)break;this->snake->direct = SnakeDirect::RIGHT;break;
        case Qt::Key_Left:if (this->snake->direct == SnakeDirect::RIGHT)break;this->snake->direct = SnakeDirect::LEFT;break;
        case Qt::Key_Space:
            if (this->snake->snakeState == SnakeState::DEAD &&
                    this->snake->gameState == GameState::STOP) {
                this->createSnake();
                this->textState.setPlainText("Game Start");
                this->textState.setPos(130, 150);
                this->textState.setFont(QFont("The New Roman", 30));
                this->textState.setDefaultTextColor(QColor(255, 0, 0));
                this->scene->addItem(&this->textState);
                this->Sleep(1000);
                this->textState.setPlainText("    3     ");
                this->Sleep(1000);
                this->textState.setPlainText("    2     ");
                this->Sleep(1000);
                this->textState.setPlainText("    1     ");
                this->Sleep(1000);
                this->scene->removeItem(&this->textState);
                this->snake->snakeState = SnakeState::ALIVE;
                this->snake->gameState = GameState::START;
                this->timer->start();
            }else if (this->snake->snakeState == SnakeState::ALIVE &&
                      this->snake->gameState == GameState::START) {
                this->snake->gameState = GameState::STOP;
                this->timer->stop();
            } else if (this->snake->snakeState == SnakeState::ALIVE &&
                       this->snake->gameState == GameState::STOP) {
                this->snake->gameState = GameState::START;
                this->timer->start();
            }break;
        default:break;
        }
    }
    else if (this->mode == Game2048) {
        if (this->game->state == GameState::START) {
            switch (event->key()) {
            case Qt::Key_Space: this->create2048Map();break;
            case Qt::Key_Up:
                this->game->direct = Game2048Direct::KeyUP;break;
            case Qt::Key_Down:
                this->game->direct = Game2048Direct::KeyDOWN;break;
            case Qt::Key_Left:
                this->game->direct = Game2048Direct::KeyLEFT;break;
            case Qt::Key_Right:
                this->game->direct = Game2048Direct::KeyRIGHT;break;
            }
            this->game->updateMatrix();
            this->textItem.setPlainText("Score: " + QString::number(pow(2, this->game->maxPoint)));
            this->updateMap();
            if (this->game->state == GameState::STOP) {
                QGraphicsTextItem *text = new QGraphicsTextItem;
                text->setPlainText("Game  Over");
                text->setPos(130, 150);
                text->setFont(QFont("The New Roman", 30));
                text->setDefaultTextColor(QColor(255, 0, 0));
                this->scene->addItem(text);
            }
        }else {
            if (event->key() == Qt::Key_Space)
                this->create2048Map();
        }
    }
    else if (this->mode == GameBird) {
        switch (event->key()) {
        case Qt::Key_Space:
            if (this->niao.state == GameState::START)
                this->niao.birdState = BirdDOWN;
            else {
                this->createBirdMap();
                this->birdTimer->start();
                this->niao.state = GameState::START;
            }
        }
    }
}

void GameSelect::keyPressEvent(QKeyEvent *event)
{
    if (this->mode == GameBird){
        if (this->niao.state == GameState::START) {
            if (event->key() == Qt::Key_Space) {
                this->niao.birdState = BirdUP;
                this->niao.downCount = 1;
                this->niao.birdPos.setY(this->niao.birdPos.y() - UP_SPEED);
                this->updateBirdPos();
            }
        }
    }
}

void GameSelect::create2048Map()
{
    this->game->initMap();
    // 先清空一下Scene
    this->clearScene();
    // 创建一个方块
    QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 450, 450);
    rect->setPen(QPen(Qt::PenStyle::NoPen));
    rect->setBrush(QColor(139, 105, 20));
    this->scene->addItem(rect);
    // 得分
    this->textItem.setPlainText("Score: " + QString::number(this->game->maxPoint));
    this->textItem.setPos(175, -40);
    QFont font;
    font.setBold(true);
    font.setPixelSize(25);
    font.setFamily("The New Roman");
    this->textItem.setFont(font);
    this->scene->addItem(&this->textItem);
    // 创建网格 4*4,
    for(int i=1; i<5; i++) {
        for (int j=1; j<5; j++){
            QGraphicsRectItem *grid = new QGraphicsRectItem(0, 0, 100, 100);
            QGraphicsTextItem *text = new QGraphicsTextItem;
            QFont font;
            font.setBold(true);
            font.setPixelSize(32);
            font.setFamily("The New Roman");
            text->setFont(font);
            grid->setPen(QPen(Qt::PenStyle::NoPen));
            grid->setBrush(QColor(255, 218, 185));
            grid->setPos(GAP * j + 100 * (j-1), GAP * i + 100 * (i-1));
            text->setPlainText(game->mapMatrix(i-1, j-1) == 0 ? "":QString::number(game->mapMatrix(i-1, j-1)));
            text->setDefaultTextColor(QColor(25, 25, 112));
            text->setPos(GAP * j + 100 * (j-1) + 35 - text->textWidth(), GAP * i + 100 * (i-1) + 35 - text->textWidth());
            this->scene->addItem(grid);
            this->scene->addItem(text);
        }
    }
}

void GameSelect::updateMap()
{
    int count = 15;
    for(int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (this->game->mapMatrix(i, j) != 0)
                qgraphicsitem_cast<QGraphicsTextItem*>(this->scene->items().at(count*2))->setPlainText(QString::number(this->game->mapMatrix(i, j)));
            else
                qgraphicsitem_cast<QGraphicsTextItem*>(this->scene->items().at(count*2))->setPlainText("");
            count--;
        }
    }
}

void GameSelect::createBirdMap()
{
    this->scene->update();
    this->niao.initBird();
    this->pipPos = 390;
    this->clearScene();
    this->textItem.setPlainText("Score: " + QString::number(this->niao.score));
    this->textItem.setPos(175, -40);
    QFont font;
    font.setBold(true);
    font.setPixelSize(25);
    font.setFamily("The New Roman");
    this->textItem.setFont(font);
    this->scene->addItem(&this->textItem);
    QGraphicsPixmapItem *pix = new QGraphicsPixmapItem;
    QPixmap *map = new QPixmap(":/images/background.png");
    pix->setPixmap(map->scaled(350, 400));
    pix->setPos(80, 0);
    this->scene->addItem(pix);
    for (int i=0; i<14; i++) {
        QGraphicsPixmapItem *pix2 = new QGraphicsPixmapItem;
        QPixmap *map2 = new QPixmap(":/images/ground.png");
        pix2->setPixmap(map2->scaled(26, 100));
        pix2->setPos(80+25*i, 400);
        this->scene->addItem(pix2);
    }
    this->bird.setPixmap(QPixmap(":/images/bird.png").scaled(35, 35));
    this->bird.setPos(this->niao.birdPos);
    this->scene->addItem(&this->bird);
    this->scene->addItem(&this->pipUp);
    this->scene->addItem(&this->pipDown);
}

void GameSelect::updateBirdMap()
{
    this->scene->update();
    QList<int> pips;
    if (this->pipPos == 390) {
        pips = this->niao.randomPipHeight();
        this->textItem.setPlainText("Score: " + QString::number(this->niao.score));
        this->niao.score++;
    }
    else{
        pips.append(this->pipUp.pixmap().height());
        pips.append(this->pipDown.pixmap().height());
    }
    this->pipUp.setPixmap(QPixmap(":/images/pipe.png").scaled(40, pips.at(0)).transformed(QTransform().rotate(180)));
    this->pipDown.setPixmap(QPixmap(":/images/pipe.png").scaled(40, pips.at(1)));
    this->pipUp.setPos(this->pipPos, 0);
    this->pipDown.setPos(this->pipPos, 400-pips.at(1));
}

void GameSelect::updateBirdPos()
{
    QList<QRect> pipes;
    pipes.append(QRect(this->pipUp.pos().x(), this->pipUp.pos().y(), this->pipUp.pixmap().width(), this->pipUp.pixmap().height()));
    pipes.append(QRect(this->pipDown.pos().x(), this->pipDown.pos().y(), this->pipUp.pixmap().width(), this->pipUp.pixmap().height()));
    this->niao.judgeBird(pipes);
    this->scene->update();
    this->bird.setPos(this->niao.birdPos);
}

void GameSelect::createIceMap()
{
    this->clearScene();
    QGraphicsPixmapItem *ice = new QGraphicsPixmapItem;
    ice->setPixmap(QPixmap(":/images/ice.png").scaled(500, 500));
    this->scene->addItem(ice);
}

