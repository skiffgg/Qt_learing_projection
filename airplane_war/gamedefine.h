#ifndef GAMEDEFINE_H
#define GAMEDEFINE_H


#include<QDebug>
#include<QSoundEffect>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QTimer>
#include<QToolButton>
#include<QList>
#include <QGraphicsPixmapItem>
#include<QMediaPlayer>
#include <QKeyEvent>
#include"bullet.h"
#include"player.h"
#include"enemy.h"
#include"playerbullet.h"
#include"enemybullet.h"


//游戏定义类 定义游戏相关属性
class GameDefine
{
    GameDefine();
public:
    static const int PlaneShootUpdateTime =500;
    static const int PlayerMoveUpdateTime =20;
    static const int EnemyMoveUpdateTime =20;
    static const int BulletMoveUpdateTime =10;
    static const int BackgroundUpdateTime =50;
    static const int EnemyCreatTime=2000;

    //屏幕宽高
    static const int ScreenWidth=306;
    static const int ScreenHeight=454;

};

#endif // GAMEDEFINE_H
