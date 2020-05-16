#include "tank.h"

int tankDy[5] = {-18,0,18,0};
int tankDx[5] = {0,18,0,-18};
map<string,int> Map {
    {"A" , 0},
    {"S" , 18},
    {"D" , 3},
    {"W" , 22},
    {"Up" , 73},
    {"Down" , 74},
    {"Left" , 71},
    {"Right" , 72},
    {"Enter" , 58},
    {"Space" , 57},
};
// 0 Up
// 1 Right
// 2 Down
// 3 Left
Tank::Tank(){
}
Tank::Tank(string keys[4],string fireKey,int id,int direction,int edge,Sprite tankPhoto)
{
    this->moveKeys[0]= Map[keys[0]];
    this->moveKeys[1]=     Map[keys[1]];
    this->moveKeys[2]=     Map[keys[2]];
    this->moveKeys[3]=     Map[keys[3]];
    this->fireKey = Map[fireKey];
    this->id = id;
    this->edge = edge;
    this->direction = direction;
    this->tankPhoto=tankPhoto;
    this->hasShooted =0;





}
void Tank::moveForward(){

    x+=tankDx[direction];
    y+=tankDy[direction];
}
void Tank::moveBackward(){
    x+=tankDx[(direction+2)%4];
    y+=tankDy[(direction+2)%4];
}
void Tank::changeDirection(int i){

    if (i == 1 ){
        direction=(direction==3) ? 0 : direction+1;
        //right
        tankPhoto.rotate(90.f);
    }

    else if (i == 3){
        direction = (direction==0) ? 3 : direction-1;//left
        //left

        tankPhoto.rotate(-90.f);

    }


}

// /

Bullet Tank::fire(Sprite bulletImage)
{

    hasShooted =1;

    return  Bullet( this->x,this->y,this->direction, this->id ,6,bulletImage);
}
Point Tank::getAssumpPositionIfTankMoveForward(){
    return {x+tankDx[direction],y+tankDy[direction] };
}

Point Tank::getAssumpPositionIfTankMoveBackward(){
    return {x+tankDx[(direction+2)%4],y+tankDy[(direction+2)%4] };
}










