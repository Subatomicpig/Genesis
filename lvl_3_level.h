#ifndef LVL_3_LEVEL_H
#define LVL_3_LEVEL_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include "Sprite.h"
#include "Attacks.h"

#include "timer.h"
#include "lvl_3_control.h"
#include "lvl_3_character.h"
#include "lvl_3_enemy.h"
#include "lvl_3_food.h"
#include <vector>

class lvl_3_level
{
public:
	//background and powerups//
		Sprite *background;
		Sprite *health;
		
		
		//collision boxes//
		Sprite *col;
		Sprite *enemyCol;
		Sprite *enemyCol_2;
		Sprite *enemyCol_3;
		Sprite *enemyCol_4;
		Sprite *enemyCol_5;
		Sprite *enemyCol_6;
		Sprite *enemyCol_7;
		Sprite *enemyCol_8;
		Sprite *enemyCol_9;
		Sprite *enemyCol_10;
		Sprite *enemyCol_11;
		Sprite *enemyCol_12;
		Sprite *foodCol_1;
		Sprite *foodCol_2;
		Sprite *foodCol_3;
		Sprite *foodCol_4;
		Sprite *foodCol_5;
		Sprite *foodCol_6;
		Sprite *foodCol_7;
		Sprite *foodCol_8;
		Sprite *foodCol_9;
		Sprite *foodCol_10;
		Sprite *foodCol_11;
		Sprite *foodCol_12;
		Sprite *foodCol_13;
		Sprite *foodCol_14;
		Sprite *foodCol_15;
		Sprite *foodCol_16;
		Sprite *foodCol_17;
		Sprite *foodCol_18;
		Sprite *foodCol_19;
		Sprite *foodCol_20;
		
		
		//food and enemies//
		lvl_3_food *food_1;
		lvl_3_food *food_2;
		lvl_3_food *food_3;
		lvl_3_food *food_4;
		lvl_3_food *food_5;
		lvl_3_food *food_6;
		lvl_3_food *food_7;
		lvl_3_food *food_8;
		lvl_3_food *food_9;
		lvl_3_food *food_10;
		lvl_3_food *food_11;
		lvl_3_food *food_12;
		lvl_3_food *food_13;
		lvl_3_food *food_14;
		lvl_3_food *food_15;
		lvl_3_food *food_16;
		lvl_3_food *food_17;
		lvl_3_food *food_18;
		lvl_3_food *food_19;
		lvl_3_food *food_20;
		
		lvl_3_character *mainChar;
		

		lvl_3_enemy *enemy1;
		lvl_3_enemy *enemy2;
		lvl_3_enemy *enemy3;
		lvl_3_enemy *enemy4;
		lvl_3_enemy *enemy5;
		lvl_3_enemy *enemy6;
		lvl_3_enemy *enemy7;
		lvl_3_enemy *enemy8;
		lvl_3_enemy *enemy9;
		lvl_3_enemy *enemy10;
		lvl_3_enemy *enemy11;
		lvl_3_enemy *enemy12;
		lvl_3_enemy *boss;

		Attacks *att;

		Timer *timer;

		lvl_3_level(const char *filename);
		void update(SDL_Surface *screen);
		void lvl_3_level::deadCheck(lvl_3_food *food);
		lvl_3_enemy* operator=(lvl_3_enemy &temp);
		~lvl_3_level();

	

		
		
	
	private:
		bool completed;
		bool run_once;	

};


lvl_3_level::lvl_3_level(const char *filename)
{
	//flags for letting the foundation know if the lvl should be finished or not//
	run_once = false;
	completed = false;
	att = new Attacks();

	
	
	//initializes and loads the image files for sprites//
	mainChar = new lvl_3_character("lvl3_mainChar.png",20,20,400,400,0,0);
	background = new Sprite(filename,0,0,9000,9000,0,0);
	health = new Sprite("healthbar3.png",mainChar->characterSprite->xpos + 100,mainChar->characterSprite->ypos + 100, 52,67,0,0);
	


	timer = new Timer();

}

void lvl_3_level::update(SDL_Surface *screen)
{	
	//draws the background for the third lvl//
	background->Draw_Sprite(screen);
	

	
}

lvl_3_level::~lvl_3_level()
{
}

void lvl_3_level::deadCheck(lvl_3_food *foodCheck)
{
	if(foodCheck->dead == true)
	{
		delete foodCheck;
	}
}


lvl_3_enemy* lvl_3_level::operator =(lvl_3_enemy &temp)
{
	return &temp;

}


#endif


