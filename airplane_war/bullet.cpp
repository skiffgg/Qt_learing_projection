#include "bullet.h"

Bullet::Bullet(QObject *parent)
{
    mObjectType=GameObject::OT_BulletPlayer;
}

Bullet::Bullet(QPoint _pos,QPixmap _pixmap, int _type)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->mBulletType=_type;
    this->mSpeed=6;


}

//void Bullet::BulletMove(QPoint _dir)
//{
//    this->moveBy(_dir.x()*mSpeed,_dir.y()*mSpeed);
//}



void Bullet::Init(QPoint _pos, QPixmap _pixmap)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);

    //*******子弹微调需要时加代码
    this->setScale(0.8);//飞机子弹图片缩放我们可以不缩放
    this->setX(this->x()-this->scale()*pixmap().width()/2);


}
