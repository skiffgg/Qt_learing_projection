#include "gameobjectpool.h"

GameObjectPool* GameObjectPool::instance=nullptr;
GameObjectPool::GameObjectPool(QObject *parent)
    : QObject{parent}
{

}

void GameObjectPool::Init()
{
    //预先生产对象
    for(int i=0;i<50;i++)
    {
        //玩家子弹生产
        PlayerBullet* playerbullet=new PlayerBullet();
        mPlayBulletpoll.append(playerbullet);

        //敌机生产
        Enemy* enemy=new Enemy();
        mEnemyPool.append(enemy);

        //敌机子弹生产
        EnemyBullet* enemybullet=new EnemyBullet();
        mEnemyBulletpoll.append(enemybullet);



    }
}

GameObject *GameObjectPool::GetGameObject(int _objectType)
{
    switch(_objectType)
    {
    case GameObject::OT_BulletPlayer://玩家子弹
    {
        PlayerBullet* playerbullet=mPlayBulletpoll.first();
        mPlayBulletpoll.pop_front();
        return playerbullet;
    }
    case GameObject::OT_Enemy://敌机
    {
        Enemy* enemy=mEnemyPool.first();
        mEnemyPool.pop_front();

        return enemy;
    }
    case GameObject::OT_EnemyBullet://玩家子弹
    {
        EnemyBullet* enemybullet=mEnemyBulletpoll.first();
        mEnemyBulletpoll.pop_front();
        return enemybullet;
    }
    }
}

void GameObjectPool::RecoveryGameObject(GameObject *_object)
{
    switch(_object->GetType())
    {
    case GameObject::OT_BulletPlayer://子弹
    {
        mPlayBulletpoll.append((PlayerBullet*)_object);
        break;
    }
    case GameObject::OT_Enemy://敌机
    {
        mEnemyPool.append((Enemy*)_object);
        break;
    }
    case GameObject::OT_EnemyBullet://玩家子弹
    {
        mEnemyBulletpoll.append((EnemyBullet*)_object);
        break;
    }
    }
}

void GameObjectPool::Clear()
{
    //清除玩家子弹容器
    for(auto pBullet:mPlayBulletpoll)
    {
        delete pBullet;
    }

    //清楚敌机子弹容器
    for(auto EBullet:mEnemyBulletpoll)
    {
        delete EBullet;
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
