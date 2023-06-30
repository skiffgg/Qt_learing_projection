#include"gamecontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    //游戏加载
    GameControl::Instance()->GameInit();

    return a.exec();
}
