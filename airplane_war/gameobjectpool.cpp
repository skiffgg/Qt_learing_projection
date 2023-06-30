#include "gameobjectpool.h"

GameObjectPool* GameObjectPool::instance=nullptr;
GameObjectPool::GameObjectPool(QObject *parent)
    : QObject{parent}
{

}

void GameObjectPool::Init()
{
    //预先生产对象
    for(int i=0;i<20;i++)
    {
        //子弹生产
        PlayerBullet* bullet=new PlayerBullet();
        mBulletpoll.append(bullet);

        //敌机生产
        Enemy* enemy=new Enemy();
        mEnemyPool.append(enemy);

    }
}

GameObject *GameObjectPool::GetGameObject(int _objectType)
{
    switch(_objectType)
    {
    case GameObject::OT_BulletPlayer://子弹
    {
        PlayerBullet* bullet=mBulletpoll.first();
        mBulletpoll.pop_front();
        return bullet;
    }
    case GameObject::OT_Enemy://敌机
    {
        Enemy* enemy=mEnemyPool.first();
        mEnemyPool.pop_front();

        return enemy;
    }
    }
}

void GameObjectPool::RecoveryGameObject(GameObject *_object)
{
    switch(_object->GetType())
    {
    case GameObject::OT_BulletPlayer://子弹
    {
        mBulletpoll.append((PlayerBullet*)_object);
        break;
    }
    case GameObject::OT_Enemy://敌机
    {
        mEnemyPool.append((Enemy*)_object);
        break;
    }
    }
}

void GameObjectPool::Clear()
{
    //清除子弹容器
    for(auto pBullet:mBulletpoll)
    {
        delete pBullet;
    }

    //清除敌机容器
    for(auto pEnemy :mEnemyPool)
    {
        delete pEnemy;
    }
}

GameObjectPool::~GameObjectPool()
{
    Clear();//内存清除
}
