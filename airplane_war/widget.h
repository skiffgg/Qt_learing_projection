#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGraphicsPixmapItem>//图形元素
#include<QGraphicsView>//视图
#include<QGraphicsScene>//场景
#include<QTimer>
#include<QKeyEvent>
#include<QList>
#include"myplane.h"
#include"bullet.h"
#include"enemy.h"
#include <QVideoWidget>
#include<QMediaPlayer>//媒体播放器类
#include<QSoundEffect>

// 元素组成-->场景-->视图-->窗口
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{

    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //背景移动函数
    void BGMove();

    //飞机移动函数
    void PlaneMove();

    //按键事件
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    //我机子弹生成函数
    void PlaneBulletShoot();

    //敌机生成
    void CreateEnemy();

    //碰撞检测
    void Collision();

private:
    Ui::Widget *ui;

    QGraphicsView mGameview;//游戏视图
    QGraphicsScene mScene;//场景
    QGraphicsScene mStartScene;//开始游戏场景

    //场景元素
//    QGraphicsPixmapItem mPlane;//飞机元素
    QGraphicsPixmapItem mBackGround1;//背景元素
    QGraphicsPixmapItem mBackGround2;
    MyPlane mPlane;

    //定时器
    QTimer* mBGMoveTimer; //背景移动定时器
    QTimer* mPlaneMoveTimer;//机移动检测定时器
    QTimer* mPlaneShootTimer;//飞机发射定时器
    QTimer* mBulletMoveTimer;//子弹移动定时器
    QTimer* mEnemyCreatTimer;//敌机创建定时器
    QTimer* mEnemyMoveTimer;//敌机移动定时器

    //容器
    QList<int> mKeyList;//按键组合
    QList<Bullet*> mBulletList;//子弹容器
    QList<Enemy*> mEnemyList;//敌机容器

    //背景音乐
    QMediaPlayer* mMediaBG;
//    QVideoWidget* videoWidget;

};
#endif // WIDGET_H
