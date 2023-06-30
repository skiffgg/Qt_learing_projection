#ifndef PLAYER_H
#define PLAYER_H

#include"plane.h"

class Player : public Plane
{
//  Q_OBJECT QGraphicsItem的派生类 不支持  Q_OBJECT（老式 信号和槽 宏）
public:
    Player();

    float MoveSpeed()
    {
        return mMoveSpeed;
    }

signals:

};

#endif // PLAYER_H
