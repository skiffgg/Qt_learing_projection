#include "widget.h"
#include "ui_widget.h"
#include"myplane.h"
#include<QPushButton>
#include<QToolButton>
#include <QtGlobal>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(306,454);

    //*******************************************************
    mGameview.setSceneRect(QRect(0,0,306,454));//游戏视图设置大小
    mScene.setSceneRect(QRect(0,0,306,454));//游戏进行场景设置大小
    mStartScene.setSceneRect(QRect(0,0,306,454));//游戏开始场景设置大小
    mStartScene.addPixmap(QPixmap(":/res/img_bg_level_1.jpg"));

    //********************************************************
    //工具按钮
    auto startBtn=new QToolButton();
    startBtn->setAutoRaise(true);
//    startBtn->resize(152,43);
    startBtn->setIcon(QIcon(":/res/startBtn.png"));
    startBtn->setIconSize(QSize(152,43));
    startBtn->move(77,201);

    //开始游戏点击
    connect(startBtn,&QToolButton::clicked,[=](){
        mGameview.setScene(&mScene);
        mGameview.show();

        //设置媒体音乐
//        mMediaBG.setVideoOutput(&videoWidget);
//        this->mMediaBG=new QMediaPlayer(this);
//        this->mMediaBG->setSource(QUrl(":/res/backMusic.mp3"));
//        this->mMediaBG->play();

        QSoundEffect * startSound = new QSoundEffect(this);//创建对象
        startSound->setSource(QUrl::fromLocalFile(":/res/bg.wav"));//添加资源
        startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
        startSound->play();//软件启动自动播放

    });

    mStartScene.addWidget(startBtn);

    //*******************************************************
    //元素 背景 视图 他们相关设置
    mBackGround1.setPixmap(QPixmap(":/res/img_bg_level_2.jpg"));
    mBackGround2.setPixmap(QPixmap(":/res/img_bg_level_2.jpg"));
   //mPlane.setPixmap(QPixmap(":/res/img-plane_1.png"));

   //mPlane.setPos(100,100); //设置元素位置
    mBackGround2.setPos(0,-mBackGround2.pixmap().height());

    //图片元素添加到场景中
    mScene.addItem(&mBackGround1);
    mScene.addItem(&mBackGround2);
    mScene.addItem(&mPlane);

//    mScene.addWidget(new QPushButton());//场景可以添加 文本 图形 矩形 图片

    mGameview.setScene(&mStartScene);//设置视图场景
//    mGameview.setScene(&mScene);

    mGameview.setParent(this); //设置视图的父亲为窗口
    mGameview.show();

    //*********************************************************
   //定时器
    //开启背景移动定时器
    mBGMoveTimer=new QTimer(this);
    mBGMoveTimer->start(10);

    connect(mBGMoveTimer,&QTimer::timeout,[=](){
        this->BGMove();
    });

    //开启飞机移动检测定时器
    mPlaneMoveTimer=new QTimer(this);
    mPlaneMoveTimer->start(10);

    connect(mPlaneMoveTimer,&QTimer::timeout,[=](){
        this->PlaneMove();
    });

    //开启发射定时器
    mPlaneShootTimer=new QTimer(this);
    mPlaneShootTimer->start(mPlane.mShootSpeed);
    connect(mPlaneShootTimer,&QTimer::timeout,this,[=](){
        this->PlaneBulletShoot();
    });

    //开启子弹移动定时器
    mBulletMoveTimer=new QTimer(this);
    mBulletMoveTimer->start(100);
    connect(mBulletMoveTimer,&QTimer::timeout,this,[=](){
        for(auto bullet: mBulletList)
        {
            bullet->BulletMove();
        }

        //碰撞检测
        Collision();
    });

    //开启敌机创建定时器
    mEnemyCreatTimer=new QTimer(this);
    mEnemyCreatTimer->start(300);
    connect(mEnemyCreatTimer,&QTimer::timeout,this,[=](){
        this->CreateEnemy();
    });

    //开启敌人移动定时器
    mEnemyMoveTimer=new QTimer(this);
    mEnemyMoveTimer->start(10);
    connect(mEnemyMoveTimer,&QTimer::timeout,this,[=](){
        for(auto enemy : mEnemyList)
        {
            enemy->EnemyMove();
        }
    });

}

void Widget::BGMove()
{
    mBackGround2.moveBy(0,2);
    mBackGround1.moveBy(0,2);//moveBy 移动量 dx-->x方向移动量 dy也是如此

    if(mBackGround1.y() >= mBackGround1.pixmap().height())
    {
        mBackGround1.setY(-mBackGround1.pixmap().height());
    }

    if(mBackGround2.y() >= mBackGround2.pixmap().height())
    {
        mBackGround2.setY(-mBackGround2.pixmap().height());
    }

}

void Widget::PlaneMove()
{
    for(int keyCode: mKeyList)
    {
        switch(keyCode)
        {
        case Qt::Key_W: mPlane.moveBy(0,-1*mPlane.mMoveSpeed);break;
        case Qt::Key_S: mPlane.moveBy(0,1*mPlane.mMoveSpeed);break;
        case Qt::Key_A: mPlane.moveBy(-1*mPlane.mMoveSpeed,0);break;
        case Qt::Key_D: mPlane.moveBy(1*mPlane.mMoveSpeed,0);break;
        }
    }

    //*******************************************************
    //边界判断
    if(mPlane.x()<0)
    {
        mPlane.setX(0);
    }

    if(mPlane.y()<0)
    {
        mPlane.setY(0);
    }

    if(mPlane.x()>this->width()-mPlane.pixmap().width())
    {
        mPlane.setX(this->width()-mPlane.pixmap().width());
    }

    if(mPlane.y()>this->height()-mPlane.pixmap().height())
    {
        mPlane.setY(this->height()-mPlane.pixmap().height());
    }
    //********************************************************

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //添加到按键组合
    switch(event->key())
    {
        case Qt::Key_W:
        case Qt::Key_S:
        case Qt::Key_A:
        case Qt::Key_D:
        mKeyList.append(event->key());
        break;
    }

}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //移除按键组合
    if(mKeyList.contains(event->key()))
    {
        mKeyList.removeOne(event->key());
    }
}

void Widget::PlaneBulletShoot()
{
    //创建子弹
    QPixmap bulletImg(":/res/bullet_1.png");

    QPoint pos(mPlane.x()+mPlane.pixmap().width()/2,
               mPlane.y());
    Bullet* bullet=new Bullet(pos,bulletImg,Bullet::BT_Player);

    mScene.addItem(bullet);//添加到场景

    mBulletList.append(bullet); //添加到子弹管理器


}

void Widget::CreateEnemy()
{
    QPixmap pixmap(":/res/game.ico");

    // 定义目标宽度和高度
    int targetWidth = 90;
    int targetHeight = 90;

    // 缩放图像
    QPixmap scaledPixmap = pixmap.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio);

    int randX=rand()%(306-scaledPixmap.width());//[0 -32768]
    Enemy* enemy=new Enemy(QPoint(randX,-200),scaledPixmap);

    //添加到场景
    mScene.addItem(enemy);

    //添加到管理容器
    mEnemyList.append(enemy);
}

void Widget::Collision()
{
    //遍历子弹
    for(int i=0;i<mBulletList.size();i++)
    {
        //遍历敌机
        for(int j=0;j<mEnemyList.size();j++)
        {
            if(mBulletList[i]->collidesWithItem(mEnemyList[j])) //碰撞检测
            {
                //移除场景  (实际的对象并没有被删除)
                mScene.removeItem(mBulletList[i]);
                mScene.removeItem(mEnemyList[j]);

                //移除管理器
                mBulletList.removeOne(mBulletList[i]);
                mEnemyList.removeOne(mEnemyList[j]);
            }
        }
    }
}

Widget::~Widget()
{
    delete ui;
}

