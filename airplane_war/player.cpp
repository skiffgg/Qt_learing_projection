#include "player.h"

Player::Player()

{
    this->setPixmap(QPixmap(":/res/img-plane_1.png"));
    this->setPos(200,100);

    mMoveSpeed=10;
    mShootSpeed=50;

}
