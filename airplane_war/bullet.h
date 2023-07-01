#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"



class Bullet : public GameObject
{
public:
    //子弹类型
    enum BulletType
    {
        BT_Player,//我方
        BT_Enemy//敌方
    };

    explicit Bullet(QObject* parent=nullptr);
    Bullet(QPoint _pos,QPixmap _pixmap,int _type);
//    void BulletMove(QPoint _dir=QPoint(0,-1));//移动函数
    virtual void  BulletMove(QPoint _dir)=0;

    void Init(QPoint _pos,QPixmap _pixmap);//初始化函数

protected:
    int mBulletType;
    int mSpeed;

    QSoundEffect * startSound;

    ~Bullet()
    {
        qDebug() <<"子弹释放";
    }

};

#endif // BULLET_H
