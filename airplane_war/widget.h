#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


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

    static Widget* widget;

    //按键事件
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
