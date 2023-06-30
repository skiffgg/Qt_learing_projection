#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include <QObject>
#include"gamedefine.h"
#include"widget.h"
/*
 对象缓存池：当对象被频繁创建 或 删除 大量使用 new 和 delete 关键字
处理堆内存 如果该对象比较大 则对计算机的消耗越大 很有在创建大量对象可能导致游戏卡顿
频繁的创建和删除对计算机消耗比较大。对象那缓存池专门处理这个问题  在对象还未使用时，
预先缓存一定数量的对象 可以有效解决在创建导致的问题，使用时直接从对象池中获取，对象被需要消耗，不消毁，而是回收到对象池
 */

class GameObjectPool : public QObject
{
    GameObjectPool(QObject *parent = nullptr);
    static GameObjectPool* instance;
public:
    static GameObjectPool* Instance()
    {
        if(instance==nullptr)
        {
            return instance=new GameObjectPool(Widget::widget);
        }
        return instance;
    }

    //对象池初始化 缓存对象
    void Init();

    //获取对象
    GameObject* GetGameObject(int _objectType);

    //回收对象
    void RecoveryGameObject(GameObject* _object);

    //内存清除
    void Clear();


    ~GameObjectPool();





protected:
    //玩家子弹对象池容器
    QList<PlayerBullet*> mBulletpoll;

    //敌机对象池容器
    QList<Enemy*> mEnemyPool;



};

#endif // GAMEOBJECTPOOL_H
