#include "gamecontrol.h"
#include"gameobjectpool.h"


GameControl* GameControl:: instance=nullptr;
GameControl::GameControl(QWidget* parent)
{
    this->setParent(Widget::widget);
}


void GameControl::BGMove()
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

void GameControl::GameInit()
{
    //对象池初始化
    GameObjectPool::Instance()->Init();

    mGameview.setParent(Widget::widget); //设置视图的父亲为窗口
    LoadStartScene();//开始场景初始化

    //定时器初始化
    mBGMoveTimer=new QTimer(this);
    mPlaneMoveTimer=new QTimer(this);
    mPlaneShootTimer=new QTimer(this);
    mBulletMoveTimer=new QTimer(this);
    mEnemyCreatTimer=new QTimer(this);
    mEnemyMoveTimer=new QTimer(this);

    //绑定定时器处理函数
    connect(mBGMoveTimer,&QTimer::timeout,[=](){
        this->BGMove();
    });

    connect(mPlaneMoveTimer,&QTimer::timeout,[=](){
            this->PlaneMove();
        });

    connect(mPlaneShootTimer,&QTimer::timeout,this,[=](){
        this->PlaneBulletShoot();
    });

    connect(mBulletMoveTimer,&QTimer::timeout,this,[=](){
        for(auto bullet: mBulletList)
        {
            bullet->BulletMove();

            //判断越界回收
            if(bullet->y()<-200)
            {
                //移除场景 对象池回收对象
                bullet->GameObjectDelete(&mGameScene);


                //移除容器
                mBulletList.removeOne(bullet);




            }
        }

        //碰撞检测
        Collision();
    });

    connect(mEnemyCreatTimer,&QTimer::timeout,this,[=](){
        this->CreateEnemy();
    });

    connect(mEnemyMoveTimer,&QTimer::timeout,this,[=](){
        for(auto enemy : mEnemyList)
        {
            enemy->EnemyMove();

            if(enemy->y()>GameDefine::ScreenHeight+enemy->pixmap().height())
            {
                //移除场景 对象池回收对象
                enemy->GameObjectDelete(&mGameScene);


                //移除容器
                mEnemyList.removeOne(enemy);



            }
        }
    });

}

void GameControl::LoadStartScene()
{
    mStartScene.setSceneRect(QRect(0,0,306,454));//游戏开始场景设置大小
    mStartScene.addPixmap(QPixmap(":/res/img_bg_level_1.jpg"));//开始场景初始化

    //工具按钮
    auto startBtn=new QToolButton();
    startBtn->setAutoRaise(true);
    startBtn->setIcon(QIcon(":/res/startBtn.png"));
    startBtn->setIconSize(QSize(152,43));
    startBtn->move(77,201);

    //开始游戏点击
    connect(startBtn,&QToolButton::clicked,[=](){

        //加载游戏场景
        this->LoadGameScene();
        //开始游戏
        this->GameStart();

        QSoundEffect * startSound = new QSoundEffect(this);//创建对象
        startSound->setSource(QUrl::fromLocalFile(":/res/bg.wav"));//添加资源
        startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
        startSound->play();//软件启动自动播放

    });

    mStartScene.addWidget(startBtn);

    //设置当前场景为 开始场景
    mGameview.setScene(&mStartScene);
    mGameview.show();
}

void GameControl::LoadGameScene()
{
    mGameScene.setSceneRect(QRect(0,0,306,454));//游戏进行场景设置大小

    //元素 背景 视图 他们相关设置
    mBackGround1.setPixmap(QPixmap(":/res/img_bg_level_2.jpg"));
    mBackGround2.setPixmap(QPixmap(":/res/img_bg_level_2.jpg"));
    //mPlane.setPixmap(QPixmap(":/res/img-plane_1.png"));

    //mPlane.setPos(100,100); //设置元素位置
    mBackGround2.setPos(0,-mBackGround2.pixmap().height());

    //图片元素添加到场景中
    mGameScene.addItem(&mBackGround1);
    mGameScene.addItem(&mBackGround2);
    mGameScene.addItem(&mPlane);

    //    mScene.addWidget(new QPushButton());//场景可以添加 文本 图形 矩形 图片





    //设置当前场景为游戏场景
    mGameview.setScene(&mGameScene);
    mGameview.show();
}

void GameControl::GameStart()
{
    //开启定时器
    mBGMoveTimer->start(GameDefine::BackgroundUpdateTime);
    mPlaneMoveTimer->start(GameDefine::PlayerMoveUpdateTime);
    mPlaneShootTimer->start(GameDefine::PlaneShootUpdateTime);
    mBulletMoveTimer->start(GameDefine::BulletMoveUpdateTime);
    mEnemyCreatTimer->start(GameDefine::EnemyCreatTime);
    mEnemyMoveTimer->start(GameDefine::EnemyMoveUpdateTime);
}

void GameControl::GameOver()
{
    //结束逻辑
    //....
}

void GameControl::PlaneMove()
{
    for(int keyCode: mKeyList)
    {
        switch(keyCode)
        {
        case Qt::Key_W: mPlane.moveBy(0,-1*mPlane.MoveSpeed());break;
        case Qt::Key_S: mPlane.moveBy(0,1*mPlane.MoveSpeed());break;
        case Qt::Key_A: mPlane.moveBy(-1*mPlane.MoveSpeed(),0);break;
        case Qt::Key_D: mPlane.moveBy(1*mPlane.MoveSpeed(),0);break;
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

    if(mPlane.x()>GameDefine::ScreenWidth-mPlane.pixmap().width())
    {
        mPlane.setX(GameDefine::ScreenWidth-mPlane.pixmap().width());
    }

    if(mPlane.y()>GameDefine::ScreenHeight-mPlane.pixmap().height())
    {
        mPlane.setY(GameDefine::ScreenHeight-mPlane.pixmap().height());
    }
    //********************************************************

}



void GameControl::PlaneBulletShoot()
{

    //对象池构建子弹
    QPixmap bulletImg(":/res/bullet_1.png");

    QPoint pos(mPlane.x()+mPlane.pixmap().width()/2,
               mPlane.y());
    GameObject* obj=GameObjectPool::Instance()->GetGameObject(GameObject::OT_BulletPlayer);
    PlayerBullet* bullet=(PlayerBullet* )obj;
    bullet->Init(pos,bulletImg);
    bullet->PlaySound();//播放音效

    mGameScene.addItem(bullet);//添加到场景

    mBulletList.append(bullet); //添加到子弹管理器
}


void GameControl::CreateEnemy()
{

    //对象池获取对象
    QPixmap pixmap(":/res/game.ico");

    // 定义目标宽度和高度
    int targetWidth = 90;
    int targetHeight = 90;

    // 缩放图像
    QPixmap scaledPixmap = pixmap.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio);

    int randX=rand()%(306-scaledPixmap.width());//[0 -32768]
//    Enemy* enemy=new Enemy(QPoint(randX,-200),scaledPixmap);


    GameObject* obj=GameObjectPool::Instance()->GetGameObject(GameObject::OT_Enemy);
    Enemy* enemy=(Enemy*)obj;
    enemy->Init(QPoint(randX,-200),scaledPixmap);

    //添加到场景
    mGameScene.addItem(enemy);

    //添加到管理容器
    mEnemyList.append(enemy);
}

void GameControl::Collision()
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
//                mGameScene.removeItem(mBulletList[i]);
//                mGameScene.removeItem(mEnemyList[j]);

                //移除场景并回收到对象池
                mBulletList[i]->GameObjectDelete(&mGameScene);
                mEnemyList[j]->GameObjectDelete(&mGameScene);

                //移除管理器
                mBulletList.removeOne(mBulletList[i]);
                mEnemyList.removeOne(mEnemyList[j]);
            }
        }
    }
}
