#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

class PlayerBullet : public Bullet
{

public:
    PlayerBullet(QObject *parent = nullptr);


    //玩家子弹音效
    void PlaySound();


};

#endif // PLAYERBULLET_H
