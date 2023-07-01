#ifndef PLANE_H
#define PLANE_H

#include "gameobject.h"

class Plane : public GameObject
{

public:
    explicit Plane(QObject *parent = nullptr);

    virtual float MoveSpeed()=0;

    int mShootSpeed;
protected:
    float mMoveSpeed;


signals:

};

#endif // PLANE_H
