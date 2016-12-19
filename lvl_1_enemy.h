#ifndef LVL_1_ENEMY_H
#define LVL_1_ENEMY_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include "Sprite.h"
#include "timer.h"


class lvl_1_enemy
{

	public:
		Sprite *enemySprite;
		
		bool inRange;
		bool inSight;
		int enemyHealth;
		int gravity, startPos;
		int dieing;
		bool dead;
		bool run_once;
		bool hit;
		
		
		Timer *delay;
	
		
		lvl_1_enemy(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight);
		
		
		~lvl_1_enemy();


	private:


};


lvl_1_enemy::lvl_1_enemy(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight)
{

	enemySprite = new Sprite(filename,xpos,ypos,width,height,xWidth, yHeight);
	inRange = false;
	inSight = false;
	delay = new Timer();
	enemyHealth = 200;
	dead = false;
	hit = false;
	
}


lvl_1_enemy::~lvl_1_enemy()
{
	delete this->enemySprite;
}




#endif


