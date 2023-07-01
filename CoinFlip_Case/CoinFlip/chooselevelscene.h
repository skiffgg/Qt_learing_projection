#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent* );


    //游戏场景的对象指针
    PlayScene* play=NULL;
signals:
    //写一个自定义的信号，告诉主场景 点击了返回 (注自定义的信号只需要声明不需要实现)
    void chooseSceneBack();


};

#endif // CHOOSELEVELSCENE_H
