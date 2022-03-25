#include "Game2048.h"

GameTwo::GameTwo() : mapMatrix(QMatrix4x4())
  , direct(None)
  , maxPoint(1)
  , state(GameState::START)
{
   this->initMap();
}

QPoint GameTwo::randomPos()
{
    int x = QRandomGenerator::global()->bounded(0, GRID_NUM);
    int y = QRandomGenerator::global()->bounded(0, GRID_NUM);
    return QPoint(x, y);
}

QList<QPoint> GameTwo::getPosEqualOne()
{
    QList<QPoint>list;
    for (int i=0; i<4; i++) {
        if (this->mapMatrix(i, 0) != 0) list.append(QPoint(i, 0));
        if (this->mapMatrix(i, 1) != 0) list.append(QPoint(i, 1));
        if (this->mapMatrix(i, 2) != 0) list.append(QPoint(i, 2));
        if (this->mapMatrix(i, 3) != 0) list.append(QPoint(i, 3));
    }
    return list;
}

void GameTwo::initMap()
{
    this->mapMatrix.fill(0);
    QPoint num1 = this->randomPos();
    QPoint num2 = this->randomPos();
    if (num1 == num2) {
        num2 = this->randomPos();
    }
    this->mapMatrix(num1.x(), num1.y()) = 2;
    this->mapMatrix(num2.x(), num2.y()) = 2;
    this->state = GameState::START;
}

QList<float> GameTwo::logical(QList<float> data)
{
    float k = 0;
    for (int i=1; i<4; i++) {
        if (data.at(k) == 0) {
            for (int j=k+1; j<4; j++) {
                if (data.at(j)!=0) {
                    data[k] = data.at(j);
                    data[j] = 0;
                    k++;
                }
            }
        }else {
            if (data[i] == 0) {
                for (int j=i+1; j<4; j++) {
                    if (data.at(j) != 0 && data.at(j) == data.at(k)) {
                        data[k] *= 2;
                        data[j] = 0;
                        break;
                    }
                    if (data.at(j) != 0 && data.at(j) != data.at(k)) {
                        data[i] = data[j];
                        data[j] = 0;
                        break;
                    }
                }
            }
            if (data[i] == data[k]) {
                data[k] *= 2;
                data[i] = 0;
            }
            k++;
        }
    }
    return data;
}

void GameTwo::updateMatrix()
{
    switch (this->direct){
    case Game2048Direct::KeyUP:
        // 将相同且相近的元素进行列相加，移动到最上行，在生成另外一个随机位置数
        for (int i=0; i<4; i++) {
            QVector4D col = this->mapMatrix.column(i);
            QList<float> vec = {col.x(), col.y(), col.z(), col.w()};
            QList<float> data = this->logical(vec);
            this->mapMatrix.setColumn(i, QVector4D(data.at(0), data.at(1), data.at(2), data.at(3)));
        }break;
    case Game2048Direct::KeyDOWN:
        // 将相同且相近的元素进行列相加，移动到最上行，在生成另外一个随机位置数
        for (int i=0; i<4; i++) {
            QVector4D col = this->mapMatrix.column(i);
            // X Y Z W
            QList<float> vec = {col.w(), col.z(), col.y(), col.x()};
            QList<float> data = this->logical(vec);
            this->mapMatrix.setColumn(i, QVector4D(data.at(3), data.at(2), data.at(1), data.at(0)));
        }break;
    case Game2048Direct::KeyRIGHT:
        // 将相同且相近的元素进行列相加，移动到最上行，在生成另外一个随机位置数
        for (int i=0; i<4; i++) {
            QVector4D col = this->mapMatrix.row(i);
            // X Y Z W
            QList<float> vec = {col.w(), col.z(), col.y(), col.x()};
            QList<float> data = this->logical(vec);
            this->mapMatrix.setRow(i, QVector4D(data.at(3), data.at(2), data.at(1), data.at(0)));
        }break;
    case Game2048Direct::KeyLEFT:
        // 将相同且相近的元素进行列相加，移动到最上行，在生成另外一个随机位置数
        for (int i=0; i<4; i++) {
            QVector4D col = this->mapMatrix.row(i);
            // X Y Z W
            QList<float> vec = {col.x(), col.y(), col.z(), col.w()};
            QList<float> data = this->logical(vec);
            this->mapMatrix.setRow(i, QVector4D(data.at(0), data.at(1), data.at(2), data.at(3)));
        }break;
    default:break;
    }
    getMaxMatrix();
    QList<QPoint> poss = getPosEqualOne();
    qDebug() << 16 - poss.length();
    if (16 - poss.length() == 0) {
        this->state = GameState::STOP;
        return;
    }
    while (1) {
        QPoint pos = this->randomPos();
        if (!poss.contains(pos)) {
            this->mapMatrix(pos.x(), pos.y()) = this->getRandomNum();
            break;
        }
    }
}

void GameTwo::getMaxMatrix()
{
    int max = 0;
    for(int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (this->mapMatrix(i, j) > max)
                max = this->mapMatrix(i, j);
        }
    }
    this->maxPoint = log2(max);
}

int GameTwo::getRandomNum()
{
    if (this->maxPoint == 1) return 2;
    return pow(2, QRandomGenerator::global()->bounded(1, this->maxPoint));
}
