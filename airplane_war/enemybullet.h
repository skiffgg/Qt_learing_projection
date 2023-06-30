#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"

class EnemyBullet : public Bullet
{

public:
    explicit EnemyBullet(QObject *parent = nullptr);
    void PlaySound();


};

#endif // ENEMYBULLET_H
