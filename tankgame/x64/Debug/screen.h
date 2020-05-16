#ifndef _SCREEN_H
#define _SCREEN_H
#include "ctin.h"
#include "bullet.h"
#include "tank.h"

class Screen{
    private:
        Bullet bullets[5];
        vector<Tank> tanks;
        Sprite background;
        vector<Sprite> bulletImages;
        int tankActive[2][10];

    public:
        int topographic[100][100];
        RenderWindow& window;
    Screen(RenderWindow& thatWindow);
    Screen();
    
    
    
    void setBackground(Sprite background);
    void setBulletImages(Sprite bulletImages[]);
    void addTank(Tank tank);
    void setTanks(Tank tanks[]);

    void updateTankActivation(int i);
    void updateBulletsActivation();
    bool isValidPoint(Point point);
    bool isValidObjectPos(Point object ,int edge);

    void setTopographic(char topoFile[]);

    void drawBullet(Bullet bullet);
    void drawTank(Tank tank);
    void drawAll();

    void test();
    void getKey(Event e);
    void createTopographic(char topoFile[]);
    void startGame();
    bool isEndGame();

};
#endif // _SCREEN_H
