#ifndef PLANE_H
#define PLANE_H

#include "gameobject.h"

class Plane : public GameObject
{

public:
    explicit Plane(QObject *parent = nullptr);

    virtual float MoveSpeed()=0;

protected:
    float mMoveSpeed;
    int mShootSpeed;

signals:

};

#endif // PLANE_H
