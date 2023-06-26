#include "bullet.h"

//Bullet::Bullet(QObject *parent)
//    : QObject{parent}
//{

//}

Bullet::Bullet(QPoint _pos,QPixmap _pixmap, int _type)
{
    this->setPos(_pos);
    this->setPixmap(_pixmap);
    this->mBulletType=_type;
    this->mSpeed=6;

//*******子弹微调需要时加代码
    this->setScale(0.8);//飞机子弹图片缩放我们可以不缩放
    this->setX(this->x()-this->scale()*pixmap().width()/2);

    PlaySound();
}

void Bullet::BulletMove(QPoint _dir)
{
    this->moveBy(_dir.x()*mSpeed,_dir.y()*mSpeed);
}

void Bullet::PlaySound()
{
    if(mBulletType==BT_Player)
    {
        startSound=new QSoundEffect();
        startSound->setSource(QUrl::fromLocalFile(":/res/myPlaneMusic.wav"));//添加资源
//        startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
    }
    else if(mBulletType==BT_Enemy)
    {
        startSound=new QSoundEffect();
        startSound->setSource(QUrl::fromLocalFile(":/res/EnemyMusic.wav"));//添加资源
//        startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
    }

    startSound->play();
}
