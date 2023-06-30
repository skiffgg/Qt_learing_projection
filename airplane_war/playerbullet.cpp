#include "playerbullet.h"

PlayerBullet::PlayerBullet(QObject *parent)
{
    mObjectType=GameObject::OT_BulletPlayer;
    mSpeed=6;
}


void PlayerBullet::PlaySound()
{


        startSound=new QSoundEffect();
        startSound->setSource(QUrl::fromLocalFile(":/res/myPlaneMusic.wav"));//添加资源
        //        startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环



    startSound->play();
}
