#ifndef ENEMY_H
#define ENEMY_H

#include "plane.h"

class Enemy : public Plane
{
public:
    Enemy()
    {
        mObjectType=GameObject::OT_Enemy;//标识对象
    }
    Enemy(QPoint _pos,QPixmap _pixmap);

    float MoveSpeed()
    {
        return mMoveSpeed;
    }

    void EnemyMove(QPoint _dir=QPoint(0,1));

    void Init(QPoint _pos,QPixmap _pixmap);

signals:

};

#endif // ENEMY_H


