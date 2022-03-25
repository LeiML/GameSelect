/********************************************************************************
** Form generated from reading UI file 'GameSelect.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESELECT_H
#define UI_GAMESELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameSelect
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *GameSelect)
    {
        if (GameSelect->objectName().isEmpty())
            GameSelect->setObjectName(QString::fromUtf8("GameSelect"));
        GameSelect->resize(1064, 682);
        verticalLayout = new QVBoxLayout(GameSelect);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(GameSelect);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        frame = new QFrame(splitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(300, 16777215));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_4->setStyleSheet(QString::fromUtf8("#pushButton_4{background-color: rgb(0, 170, 255);\n"
"color: rgb(255, 255, 255);\n"
"font: 700 italic 22pt \"Times New Roman\";\n"
"border-radius: 10px;\n"
"}\n"
"#pushButton_4:hover{\n"
"background-color: rgb(10, 170, 200);\n"
"}"));

        verticalLayout_3->addWidget(pushButton_4);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton{background-color: rgb(0, 170, 255);\n"
"color: rgb(255, 255, 255);\n"
"font: 700 italic 22pt \"Times New Roman\";\n"
"border-radius: 10px;\n"
"}\n"
"#pushButton:hover{\n"
"background-color: rgb(10, 170, 200);\n"
"}"));

        verticalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("#pushButton_2{background-color: rgb(0, 170, 255);\n"
"color: rgb(255, 255, 255);\n"
"font: 700 italic 22pt \"Times New Roman\";\n"
"border-radius: 10px;\n"
"}\n"
"#pushButton_2:hover{\n"
"background-color: rgb(10, 170, 200);\n"
"}"));

        verticalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("#pushButton_3{background-color: rgb(0, 170, 255);\n"
"color: rgb(255, 255, 255);\n"
"font: 700 italic 22pt \"Times New Roman\";\n"
"border-radius: 10px;\n"
"}\n"
"#pushButton_3:hover{\n"
"background-color: rgb(10, 170, 200);\n"
"}"));

        verticalLayout_3->addWidget(pushButton_3);

        splitter->addWidget(frame);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(36);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        graphicsView = new QGraphicsView(frame_2);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setStyleSheet(QString::fromUtf8(""));
        graphicsView->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(graphicsView);

        splitter->addWidget(frame_2);

        verticalLayout->addWidget(splitter);


        retranslateUi(GameSelect);
        QObject::connect(pushButton, SIGNAL(clicked()), GameSelect, SLOT(SelectGame()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), GameSelect, SLOT(SelectGame()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), GameSelect, SLOT(SelectGame()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), GameSelect, SLOT(SelectGame()));

        QMetaObject::connectSlotsByName(GameSelect);
    } // setupUi

    void retranslateUi(QWidget *GameSelect)
    {
        GameSelect->setWindowTitle(QCoreApplication::translate("GameSelect", "GameSelect", nullptr));
        pushButton_4->setText(QCoreApplication::translate("GameSelect", "Bing Dwen Dwen", nullptr));
        pushButton->setText(QCoreApplication::translate("GameSelect", "Greedy Snake", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GameSelect", "2048", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GameSelect", "Flappy Bird", nullptr));
        label->setText(QCoreApplication::translate("GameSelect", "Bing Dwen Dwen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameSelect: public Ui_GameSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESELECT_H
