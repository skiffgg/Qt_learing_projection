#ifndef ENEMY_H
#define ENEMY_H

#include "myplane.h"

class Enemy : public MyPlane
{
public:
    Enemy(QPoint _pos,QPixmap _pixmap);

    void EnemyMove(QPoint _dir=QPoint(0,1));

signals:

};

#endif // ENEMY_H


