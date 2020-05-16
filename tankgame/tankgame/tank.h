
#ifndef _TANK_H
#define _TANK_H
#include "ctin.h"
#include "bullet.h"
class Tank{
    public: int x  , y, id, direction, moveKeys[5], fireKey,edge;//array
    Sprite tankPhoto;
    bool hasShooted;
    Tank();
    Tank(string keys[4],string fireKey,int id,int direction,int edge,Sprite tankPhoto);
    void moveForward();
    void moveBackward();
    void changeDirection(int i);
    Point getAssumpPositionIfTankMoveForward();
    Point getAssumpPositionIfTankMoveBackward();
    Bullet fire(Sprite  bulletImage);

};
#endif // _TANK_H
