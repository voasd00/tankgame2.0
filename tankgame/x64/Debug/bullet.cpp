#include "bullet.h"
#include "ctin.h"
int dy[5] = {-1,0,1,0};
int dx[5] = {0,1,0,-1};
Bullet::Bullet(){
}
Bullet::Bullet(int x,int y,int direction,int id,int edge,Sprite bulletPhoto)
{

    this->x = x+dx[direction]*9;
    this->y = y+dy[direction]*9;
    this->direction = direction;
    this->id = id;
    this->edge = edge;
    this->bulletPhoto = bulletPhoto;
    this->bulletPhoto.setTextureRect(IntRect(0,0,this->edge,this->edge));
    this->bulletPhoto . setOrigin(this->edge/2.f,this->edge/2.f);

}
void Bullet::updateBulletPos()
{
    x+=dx[direction];
    y+=dy[direction];
}











