#ifndef GAMECONTROL_H
#define GAMECONTROL_H
#include"gamedefine.h"
#include"widget.h"

class GameControl:public QObject
{
    //单例
    GameControl(QWidget* parent=nullptr);
    static GameControl* instance;
public:
    //获取单例
    static GameControl* Instance()
    {
        if(instance==nullptr)
        {
            return instance=new GameControl(Widget::widget);
        }
        return instance;
    }

    ~GameControl()
    {
        qDebug()<<"游戏控制释放";
    }

    //游戏初始化
    void GameInit();

    //加载开始场景
    void LoadStartScene();

    //游戏场景加载
    void LoadGameScene();

    //游戏逻辑定时器开启(游戏开始）
    void GameStart();

    //游戏逻辑定时器关闭(游戏结束）
    void GameOver();

    //背景移动函数
    void BGMove();

    //飞机移动函数
    void PlaneMove();



    //我机子弹生成函数
    void PlaneBulletShoot();

    //敌机子弹生成函数
    void EnemyBulletShoot(Enemy& enemy);//未写

    //敌机生成
    void CreateEnemy();

    //我机击落敌机碰撞检测
    void PlayerCollision();

    //我机击落敌机碰撞检测
    void EnemyCollision();


    QList<int> mKeyList;//按键组合

protected:
    QGraphicsView mGameview;//游戏视图
    QGraphicsScene mGameScene;//场景
    QGraphicsScene mStartScene;//开始游戏场景

    //场景元素
    //    QGraphicsPixmapItem mPlane;//飞机元素
    QGraphicsPixmapItem mBackGround1;//背景元素
    QGraphicsPixmapItem mBackGround2;
    Player mPlane;

    //定时器
    QTimer* mBGMoveTimer; //背景移动定时器
    QTimer* mPlaneMoveTimer;//机移动检测定时器
    QTimer* mPlaneShootTimer;//我机子弹发射定时器
    QTimer* mplayerBulletMoveTimer;//我机子弹移动定时器
    QTimer* EnemyBulletMoveTimer;//敌机机子弹移动定时器
    QTimer* mEnemyCreatTimer;//敌机创建定时器
    QTimer* mEnemyMoveTimer;//敌机移动定时器

    //注：只有在创建敌机时候再开启敌机子弹发射定时器
    QTimer* mEnemyShootTimer;

    //容器
    QList<PlayerBullet*> mPlayerBulletList;//我机子弹容器
    QList<EnemyBullet*> EnemyBulletList;//敌机子弹容器
    QList<Enemy*> mEnemyList;//敌机容器

    //背景音乐
    QMediaPlayer* mMediaBG;
    //    QVideoWidget* videoWidget;
};
#endif // GAMECONTROL_H

