#include "GameSelect.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameSelect w;
    w.show();
    return a.exec();
}
