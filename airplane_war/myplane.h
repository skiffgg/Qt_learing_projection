#ifndef MYPLANE_H
#define MYPLANE_H


#include<QGraphicsPixmapItem>

class MyPlane : public QGraphicsPixmapItem
{
//  Q_OBJECT QGraphicsItem的派生类 不支持  Q_OBJECT（老式 信号和槽 宏）
public:
    MyPlane();
    float mMoveSpeed;
    int mShootSpeed;

signals:

};

#endif // MYPLANE_H
