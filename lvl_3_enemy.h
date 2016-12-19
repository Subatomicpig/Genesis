#ifndef LVL_3_ENEMY_H
#define LVL_3_ENEMY_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include "Sprite.h"
#include "timer.h"

class lvl_3_enemy
{

	public:
		Sprite *enemySprite;
		
		bool inRange;
		bool inSight;
		int enemyHealth;
		int gravity, startPos;
		int dieing;
		bool dead;
		bool hit;

		int dType;
		
		
		Timer *delay;
	
		
		lvl_3_enemy(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight);
		void update();
		void finalBoss();//ONLY FOR USE FOR LEVEL 3 FINAL BOSS, DO NOT CALL
		void drop();
		
		~lvl_3_enemy();


};


lvl_3_enemy::lvl_3_enemy(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight)
{

	enemySprite = new Sprite(filename,xpos,ypos,width,height,xWidth, yHeight);
	inRange = false;
	inSight = false;
	delay = new Timer();
	enemyHealth = 100;
	dead = false;
	hit = false;
	
}

void lvl_3_enemy::update()
{
	if (this->dead) drop();
}

void lvl_3_enemy::drop()
{
	if (dType == 1)
	{

	}

	else if (dType == 2)
	{

	}
	else if (dType == 3)
	{

	}


	
}

void lvl_3_enemy::finalBoss()
{
	delay->start();

	
}


lvl_3_enemy::~lvl_3_enemy()
{
	delete this->enemySprite;
}




#endif
