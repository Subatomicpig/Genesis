#ifndef LVL_1_FOOD_H
#define LVL_1_FOOD_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include "Sprite.h"
#include "timer.h"


class lvl_1_food
{

	public:
		Sprite *foodSprite;
		
		bool inRange;
		bool inSight;
		int foodHealth;
		int gravity, startPos;
		int dieing;
		int dead;
		bool eaten;
		bool hit;
		
		Timer *delay;
	
		
		lvl_1_food(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight);
		~lvl_1_food();


	private:


};


lvl_1_food::lvl_1_food(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight)
{

	foodSprite = new Sprite(filename,xpos,ypos,width,height,xWidth, yHeight);
	inRange = false;
	inSight = false;
	delay = new Timer();
	foodHealth = 10;
	dead = false;
	eaten = false;
	hit = false;
	
}


lvl_1_food::~lvl_1_food()
{
	delete foodSprite;
}

#endif


