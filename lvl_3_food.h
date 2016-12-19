#ifndef LVL_3_FOOD_H
#define LVL_3_FOOD_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include "Sprite.h"
#include "timer.h"

class lvl_3_food
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
	
		
		lvl_3_food(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight);
		~lvl_3_food();
	
	
	


};

lvl_3_food::lvl_3_food(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight)
{

	foodSprite = new Sprite(filename,xpos,ypos,width,height,xWidth, yHeight);
	inRange = false;
	inSight = false;
	delay = new Timer();
	foodHealth = 100;
	dead = false;
	eaten = false;
	hit = false;
	
}


lvl_3_food::~lvl_3_food()
{

}

#endif
