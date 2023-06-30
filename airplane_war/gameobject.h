#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QSoundEffect>


class GameObject : public QGraphicsPixmapItem
{
//    Q_OBJECT
public:
   enum ObjectType
    {
        OT_BulletPlayer,

        OT_Enemy,

        OT_Player,

        OT_EnemyBullet
    };

   GameObject(QObject *parent = nullptr);

   int GetType()
   {
       return mObjectType;
   }

   //对象回收
   void GameObjectDelete(QGraphicsScene* _scene);

   //t统计对象构造 和析构
   static int createCount;

   ~GameObject()
   {

        qDebug()<<"当前释放第"+QString::number(createCount--)+"几个对象";
   }
protected:
   int mObjectType;


};

#endif // GAMEOBJECT_H
