#ifndef _BULLET_H
#define _BULLET_H
#include "ctin.h"
class Bullet{
    public: int x, y,id,direction,edge;
    Sprite bulletPhoto;
    bool isFlying;
    Bullet();
    Bullet(int x,int y,int direction,int id,int edge,Sprite bulletPhoto);
    void updateBulletPos();
};
#endif // _BULLET_H
