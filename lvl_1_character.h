#ifndef LVL_1_CHARACTER_H
#define LVL_1_CHARACTER_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include "Sprite.h"



class lvl_1_character
{

	public:
		Sprite *characterSprite;
		
		int health;
		int currentHealth;
		bool dead;
		int points;
		bool hit;
		bool eating;
		bool attacking;
		int maxVelocity;
		bool moving;
		

		lvl_1_character(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight);
		~lvl_1_character();
		void healthUpdate(Sprite *sprite, lvl_1_character *mainChar);




	private:


};



lvl_1_character::lvl_1_character(const char *filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight)
{

	characterSprite = new Sprite(filename,xpos,ypos,width,height,xWidth, yHeight);
	dead = false;
	points = 0;
	health = 150;
	currentHealth = this->health;
	hit = false;
	moving = false;
	eating = false;
	attacking = false;
	maxVelocity = 0;
	
}


lvl_1_character::~lvl_1_character()
{
	delete this->characterSprite;
}

void lvl_1_character::healthUpdate(Sprite *sprite, lvl_1_character *mainChar)
{
	if(mainChar->health > 100)
	{
		mainChar->health = 100;
	}
	else if(mainChar->health >= 90 && mainChar->health < 100)
	{
		sprite->rect.x = 0;
	}
	else if(mainChar->health >=  80 && mainChar->health < 90)
	{
		sprite->rect.x = 240;
	}
	else if(mainChar->health >= 70 && mainChar->health < 80)
	{
		sprite->rect.x = 480;
	}
	else if(mainChar->health >= 60 && mainChar->health < 70)
	{
		sprite->rect.x = 720;
	}
	else if(mainChar->health >= 50 && mainChar->health < 60)
	{
		sprite->rect.x = 960;
	}
	else if(mainChar->health >= 40 && mainChar->health < 50)
	{
		sprite->rect.x = 1200;
	}
	else if(mainChar->health >= 30 && mainChar->health < 40)
	{
		sprite->rect.x = 1440;
	}
	else if(mainChar->health  >= 20 && mainChar->health < 30)
	{
		sprite->rect.x = 1680;
	}
	else if(mainChar->health >= 1 && mainChar->health < 20)
	{
		sprite->rect.x = 1920;
	}
	else if(mainChar->health <= 0)
	{
		mainChar->dead = true;
	}

}





#endif