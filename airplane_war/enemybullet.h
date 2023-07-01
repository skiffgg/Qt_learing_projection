#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"

class EnemyBullet : public Bullet
{

public:
    explicit EnemyBullet(QObject *parent = nullptr);

    void BulletMove(QPoint _dir=QPoint(0,1));

    void PlaySound();


};

#endif // ENEMYBULLET_H
