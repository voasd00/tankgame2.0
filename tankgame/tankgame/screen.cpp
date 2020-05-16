#include "screen.h"
#include "ctin.h"
//////////////////////////////////////////////////////////// setting
Screen::Screen(RenderWindow& thatWindow) :window(thatWindow)
{

}



void Screen::addTank(Tank tank)
{
	this->tanks.push_back(tank);

}
void Screen::setTanks(Tank tanks[])
{
	for (int i = 0; i <= 1; ++i)
		addTank(tanks[i]);
}

void Screen::setBackground(Sprite background)
{
	this->background = background;
}
void Screen::setBulletImages(Sprite bulletImages[])
{
	for (int i = 0; i <= 1; ++i)
		this->bulletImages.push_back(bulletImages[i]);
}
void Screen::setTopographic(char topoFile[])
{

	freopen(topoFile, "r", stdin);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			cin >> this->topographic[i][j];
			cout << topographic[i][j] << " ";
		}
		cout << "\n";
	}


}



/////////////////////////////////////////////////////////////// check
bool Screen::isValidPoint(Point point)
{
	return !(this->topographic[point.y / 18][point.x / 18]);
}
bool Screen::isValidObjectPos(Point object, int edge)
{


	return !(this->topographic[object.y / 18][object.x / 18]);


}
bool Screen::isEndGame() {
	for (int i = 0; i <= 1; ++i)
		for (int j = 0; j <= 1; ++j)
			if (i != j)
				if (tanks[j].hasShooted)
					if ((tanks[i].x / 18 == bullets[j].x / 18) && (tanks[i].y / 18 == bullets[j].y / 18))
						return 1;
	return 0;
}


/////////////////////////////////////////////////////////// draw

void Screen::drawBullet(Bullet bullet)
{

	bullet.bulletPhoto.setPosition((float)bullet.x, (float)bullet.y);
	window.draw(bullet.bulletPhoto);
}
void Screen::drawTank(Tank tank)
{
	tank.tankPhoto.setPosition((float)tank.x, (float)tank.y);
	window.draw(tank.tankPhoto);
}
void Screen::drawAll()
{
	window.clear();
	window.draw(background);
	for (int i = 0; i <= 1; ++i)
		drawTank(tanks[i]);

	for (int i = 0; i <= 1; ++i)
		if (tanks[i].hasShooted)
			drawBullet(bullets[i]);
}
void Screen::getKey(Event e) {
	if (e.type == e.KeyPressed) {
		for (int i = 0; i <= 1; ++i)
		{
			for (int j = 0; j < 4; j++)
				if (e.key.code == tanks[i].moveKeys[j]) tankActive[i][j] =1;
			if (e.key.code == tanks[i].fireKey)
				tankActive[i][4] = 1;
		}
	}
	else if (e.type == e.KeyReleased) {
		for (int i = 0; i <= 1; ++i)
		{
			for (int j = 0; j < 4; j++)
				if (e.key.code == tanks[i].moveKeys[j]) tankActive[i][j] = 0;
			if (e.key.code == tanks[i].fireKey)
				tankActive[i][4] = 0;
		}
	}
}
void Screen::updateTankActivation(int i) {
	while (true) {
		
			this_thread::sleep_for(chrono::milliseconds(100));
			if (tankActive[i][0])
			{
				if (isValidObjectPos(tanks[i].getAssumpPositionIfTankMoveForward(), tanks[i].edge)) {
					tanks[i].moveForward();
					cout << tanks[i].x << " " << tanks[i].y << E;
				}
			}
			if (tankActive[i][2])
			{
				if (isValidObjectPos(tanks[i].getAssumpPositionIfTankMoveBackward(), tanks[i].edge)) {
					tanks[i].moveBackward();
					cout << tanks[i].x << " " << tanks[i].y << E;
				}
			}
			if (tankActive[i][4])
			{
				if (!tanks[i].hasShooted) 
					bullets[i] = tanks[i].fire(bulletImages[i]);
				
			}
			if (tankActive[i][1]) tanks[i].changeDirection(1);
			if (tankActive[i][3]) tanks[i].changeDirection(3);

			
			
	}
}

void Screen::updateBulletsActivation() {
	while (true) {
		this_thread::sleep_for(chrono::microseconds(50));
		for (int i = 0; i < 2; ++i)
		{
			if (tanks[i].hasShooted)
			{
				bullets[i].updateBulletPos();
				if (!isValidObjectPos({ bullets[i].x,bullets[i].y }, bullets[i].edge))
					tanks[i].hasShooted = 0;
			}
		}
	}


}
void Screen::startGame()
{
	thread tank0Thread(&Screen::updateTankActivation, this, 0);
	thread tank1Thread(&Screen::updateTankActivation, this, 1);
	thread bulletThread(&Screen::updateBulletsActivation, this);
	tank0Thread.detach();
	tank1Thread.detach();
	bulletThread.detach();

	while (window.isOpen())
	{
		window.clear(Color::Black);
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			
				getKey(e);
				
			
		}
		
		
		drawAll();
		if (isEndGame()) exit(0);
		window.display();


	}
}










void Screen::createTopographic(char topoFile[])
{
	Texture t1, t2;
	t1.loadFromFile("images/whitedot.png");
	t2.loadFromFile("images/blackdot.png");
	Sprite white(t1), black(t2);
	setTopographic(topoFile);
	RenderWindow window(VideoMode(540, 540), "tank!!");
	white.setTextureRect(IntRect(0, 0, 1, 1));
	black.setTextureRect(IntRect(0, 0, 1, 1));
	for (int i = 0; i < 540; ++i)
		for (int j = 0; j < 540; ++j)
			if (topographic[i / 18][j / 18])
			{
				black.setPosition((float)j, (float)i);
				window.draw(black);
			}
			else
			{
				white.setPosition((float)j, (float)i);
				window.draw(white);
			}
	Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	Image screenshot = texture.copyToImage();
	screenshot.saveToFile("images/background.png");

}