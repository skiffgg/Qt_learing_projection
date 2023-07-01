#include "chooselevelscene.h"
#include "qmenubar.h"
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include<QSoundEffect>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡场景
    this->setFixedSize(320,500);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡的场景");

    //创建菜单栏
    QMenuBar* bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu* startMenu=bar->addMenu("开始");

    //创建退出 菜单项
    QAction* quitAction=startMenu->addAction("退出");


    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();

    });

    //选择关卡按钮音效
    QSoundEffect * chooseSound = new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    //返回按钮音效
    QSoundEffect * backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //返回按钮
    MyPushButton* backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);

    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击了返回按钮";

        //告诉主场景 我返回了 主场景监听ChooseLevelScene的返回按钮

        //做个延时的返回

        //播放返回按钮音效
        backSound->play();
        QTimer::singleShot(500,this,[=](){
            //发送自定义信号
            emit this->chooseSceneBack();
        });
    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton* menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //播放选择关卡音效
            chooseSound->play();
            //格式化字符串
            QString str=QString("你选择的是第 %1 关").arg(i+1);
            qDebug()<<str;

            //进入到游戏的场景
            this->hide();//将选关场景隐藏掉
            play=new PlayScene(i+1);//创建游戏场景
            play->show();//显示游戏场景

            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->show();
                delete play;
                play=NULL;
            });

        });

        QLabel* label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);

        //设置label上的文字对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置让鼠标穿透 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

void ChooseLevelScene::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    \
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
