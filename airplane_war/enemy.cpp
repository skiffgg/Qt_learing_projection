#include "enemy.h"

Enemy::Enemy(QPoint _pos, QPixmap _pixmap)
{
    this->mMoveSpeed=3;
    this->mShootSpeed=10000;
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->setScale(0.8);
}

void Enemy::EnemyMove(QPoint _dir)
{
    this->moveBy(_dir.x()*mMoveSpeed,_dir.y()*mMoveSpeed);
}

