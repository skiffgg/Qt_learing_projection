#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

class PlayerBullet : public Bullet
{

public:
    PlayerBullet(QObject *parent = nullptr);

    void BulletMove(QPoint _dir=QPoint(0,-1));

    //玩家子弹音效
    void PlaySound();


};

#endif // PLAYERBULLET_H
