#include "widget.h"
#include "ui_widget.h"
#include"gamecontrol.h"

Widget* Widget::widget=nullptr;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(306,454);
    widget=this;

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //添加到按键组合
    switch(event->key())
    {
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
    GameControl::Instance()->mKeyList.append(event->key());
    break;
    }

}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //移除按键组合
    if(GameControl::Instance()->mKeyList.contains(event->key()))
    {
        GameControl::Instance()->mKeyList.removeOne(event->key());
    }
}

Widget::~Widget()
{
    delete ui;
}

