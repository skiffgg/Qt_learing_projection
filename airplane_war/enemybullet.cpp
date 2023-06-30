#include "enemybullet.h"

EnemyBullet::EnemyBullet(QObject *parent)
{
    mObjectType=GameObject::OT_EnemyBullet;
}

void EnemyBullet::PlaySound()
{


        startSound=new QSoundEffect();
        startSound->setSource(QUrl::fromLocalFile(":/res/EnemyMusic.wav"));//添加资源
        //        startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环


    startSound->play();
}
