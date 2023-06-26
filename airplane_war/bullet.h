#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include<QDebug>
#include<QSoundEffect>

class Bullet : public QGraphicsPixmapItem
{
public:
    //子弹类型
    enum BulletType
    {
        BT_Player,//我方
        BT_Enemy//敌方
    };

    Bullet(QPoint _pos,QPixmap _pixmap,int _type);
    void BulletMove(QPoint _dir=QPoint(0,-1));//移动函数
    void PlaySound();



    int mBulletType;
    int mSpeed;

    QSoundEffect * startSound;

    ~Bullet()
    {
        qDebug() <<"子弹释放";
    }

};

#endif // BULLET_H
