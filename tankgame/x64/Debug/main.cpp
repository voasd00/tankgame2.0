#include "ctin.h"
#include "bullet.h"
#include "tank.h"
#include "screen.h"

int main ()
{


    srand((unsigned int)time(NULL));
    char topoFile[]="topographic.inp";
    


    Texture tTankRed,tTankGreen,tBackground,t4,tBulletRed,tBulletGreen;
    tTankRed.loadFromFile("images/tankred.png");
    tTankGreen.loadFromFile("images/tankgreen.png");
    tBackground.loadFromFile("images/background.png");
    tBulletGreen.loadFromFile("images/bulletgreen.png");
    tBulletRed.loadFromFile("images/bulletred.png");

    Sprite tankred(tTankRed),tankgreen(tTankGreen);
    Sprite bulletImages[2];
    tankred.setOrigin(9,9);
    tankgreen.setOrigin(9,9);
    bulletImages[0] = Sprite(tBulletRed);
    bulletImages[1] = Sprite(tBulletGreen);
    bulletImages[0].setOrigin(3,3);
    bulletImages[1].setOrigin(3,3);

    Tank tanks[3];
    string keys1[4] = {"Up","Right","Down","Left"};
    // string keys[4],string fireKey,int id,int direction,int edge,Sprite tankPhoto
    tanks[0]=Tank(keys1,"Enter",0,0,18,tankred);
    tanks[0].x =18+9;
    tanks[0].y =18+9;
    string keys2[4] = {"W","D","S","A"};
    tanks[1]=Tank(keys2,"Space",1,0,18,tankgreen);
    tanks[1].x =28*18+9;
    tanks[1].y =28*18+9;

    RenderWindow window(VideoMode(540,540),"Tank!!");

    Screen screen(window);
    screen.createTopographic(topoFile);
    screen.setBulletImages(bulletImages);
    screen.setBackground(Sprite(tBackground));
    screen.setTanks(tanks);
    screen.startGame();






}
