#ifndef LVL_1_CONTROL
#define LVL_1_CONTROL
#define MouseButtonDown(evt) (event.button.state == SDL_PRESSED)
#define MouseButtonUp(evt) (event.button.state == SDL_RELEASED)
#define FRAMES_PER_SECOND = 25;

#include "SDL.h"
#include "SDL_Mixer.h"
#include "lvl_1_character.h"
#include "lvl_1_food.h"
#include "lvl_1_enemy.h"
#include "Collision.h"
#include "SDL_Collide.h"
#include "timer.h"
#include "lvl_1_list.h"



#include <vector>
#include <cmath>
#include "math.h"
#include <stdio.h> 
#include <sstream>
#include <string>

class lvl_1_control
{
	public:
		
		SDL_Event event;
		Uint8 *keys;
		int xMotion, yMotion;
		int xMouse, yMouse;
		int quit;
		//background pos//
		int xPos, yPos;
		float dist, xVel, yVel;
		double angle;
		bool charAttack;
		int buttonState;
		bool lvl_1_control::buttonDown();
		bool escape;
		int charSpeed;
		int velocity;

		
		Timer *fps;
		Mix_Music *tonal;
		Mix_Chunk *enemyHit;
		Mix_Chunk *enemyDeath;
		Mix_Chunk *playerHit;
		Mix_Chunk *eat;

		lvl_1_objects *lvl_1;
	
		lvl_1_control();
		~lvl_1_control();

		void micro_control(SDL_Surface *screen);
		void checkAngle(Sprite *sprite, Sprite *sprite2);
		void patrol(Sprite *sprite, Sprite *sprite2);
		void bossChase(Sprite *sprite, Sprite *sprite2);
		void foodRun(Sprite *sprite, Sprite *sprite3);
		
		int angleVel;
		bool started;
		bool done;
		double angle2;
		double angle3;
		float dist2,xVel2,yVel2;
		float dist3,xVel3,yVel3;
		int spriteXpos,spriteYpos,enemyXpos,enemyYpos;
		int charAngle;

		

	private:

};

lvl_1_control::lvl_1_control()
{
	done = false;
	velocity = 20;
	quit = 0;
	xPos = 0;
	yPos = 0;
	charAttack = false;
	buttonState = 1;
	fps = new Timer();
	fps->start();
	lvl_1 = new lvl_1_objects();
	//lvl_1->boss->enemyHealth = 550;
	lvl_1->boss->enemyHealth = 50;
	tonal = Mix_LoadMUS("LVL1_TNL.mp3");
	enemyHit = Mix_LoadWAV("enemy1_hit.wav");
	enemyDeath = Mix_LoadWAV("enemy1_death.wav");
	playerHit = Mix_LoadWAV("level_1_hitPlayer.wav");
	eat = Mix_LoadWAV("eating.wav");
	started = false;
	Mix_PlayMusic(tonal,-1);
	
}

bool lvl_1_control::buttonDown()
{
	return SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1);
}

lvl_1_control::~lvl_1_control()
{
	delete lvl_1;

}

void lvl_1_control::micro_control(SDL_Surface *screen)
{
	
	while(SDL_PollEvent(&event))  
	{			
		switch(event.type)  
		{
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				this->escape = true;
				break;
				if(event.key.keysym.sym == SDLK_RETURN)
					Mix_PlayChannel(2,enemyHit, 0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					//flag for moving the character constaltly after the mousebutton is clicked//
					buttonState = 1;
				}
				else if(event.button.button == SDL_BUTTON_RIGHT)
				{
					charAttack = true;
				}
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_RIGHT && event.button.state == SDL_RELEASED)
				{
					charAttack = false;
				}
				break;
			
				

		}
				
		
		//determines what way to face the sprite//
		//also faces the healthbar with the sprite//
		if( event.type == SDL_MOUSEMOTION )
		{
	
			//UPER LEFTHAND CORNER//
			if(angle >= 112.5 && angle < 157.5)
			{
				charAngle = 8;
				lvl_1->mainChar->characterSprite->rect.y = 1680;
				lvl_1->health->rect.y = 1680;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos + 20;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos + 20;
				
			}

			//THE UPWARD DIRECTION//
			else if(angle >= 67.5 && angle < 112.5)
			{
				charAngle = 0;
				lvl_1->mainChar->characterSprite->rect.y = 0;
				lvl_1->health->rect.y = 0;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos + 100;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos;
				
			}
			//UPER RIGHTHAND CORNER//
			else if(angle >= 22.5 && angle < 67.5)
			{
				charAngle = 1;
				lvl_1->mainChar->characterSprite->rect.y = 240;
				lvl_1->health->rect.y = 240;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos + 180;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos + 20;
			}
			//LEFT SIDE//
			else if(angle >= 157.5 && angle < 202.5)
			{
				charAngle = 7;
				lvl_1->mainChar->characterSprite->rect.y = 1440;
				lvl_1->health->rect.y = 1440;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos - 10;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos + 100;
			}
			//LOWER LEFTHAND CORNER//
			else if(angle >= 202.5 && angle < 247.5)
			{
				charAngle = 6;
				lvl_1->mainChar->characterSprite->rect.y = 1200;
				lvl_1->health->rect.y = 1200;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos + 10;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos + 170;
			}
			//BOTTOM//
			else if(angle >= 247.5 && angle < 292.5)
			{
				charAngle = 5;
				lvl_1->mainChar->characterSprite->rect.y = 960;
				lvl_1->health->rect.y = 960;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos + 100;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos + 180;
			}
			//BOTTOM RIGHT HAND CORNER//
			else if(angle >= 292.5 && angle < 337.5)
			{
				charAngle = 4;
				lvl_1->mainChar->characterSprite->rect.y = 720;
				lvl_1->health->rect.y = 720;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos + 170;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos + 170;
			}
			//RIGHT//
			else
			{
				charAngle = 3;
				lvl_1->mainChar->characterSprite->rect.y = 480;
				lvl_1->health->rect.y = 480;
				lvl_1->charCol->xpos = lvl_1->mainChar->characterSprite->xpos + 190;
				lvl_1->charCol->ypos = lvl_1->mainChar->characterSprite->ypos + 100;
			}

			
			//IF MAIN CHAR COLLIDES WITH BOSS COLL/
			if(SDL_BoundingCollide(lvl_1->charCol->image,lvl_1->charCol->xpos,lvl_1->charCol->ypos,lvl_1->bossCol_1->image,lvl_1->bossCol_1->xpos,lvl_1->bossCol_1->ypos) == 1 && charAttack == true || SDL_BoundingCollide(lvl_1->charCol->image,lvl_1->charCol->xpos,lvl_1->charCol->ypos,lvl_1->bossCol_2->image,lvl_1->bossCol_2->xpos,lvl_1->bossCol_2->ypos) == 1 && charAttack == true || SDL_BoundingCollide(lvl_1->charCol->image,lvl_1->charCol->xpos,lvl_1->charCol->ypos,lvl_1->bossCol_3->image,lvl_1->bossCol_3->xpos,lvl_1->bossCol_3->ypos) == 1 && charAttack == true || SDL_BoundingCollide(lvl_1->charCol->image,lvl_1->charCol->xpos,lvl_1->charCol->ypos,lvl_1->bossCol_4->image,lvl_1->bossCol_4->xpos,lvl_1->bossCol_4->ypos) == 1 && charAttack == true)
			{
				
					lvl_1->boss->enemyHealth -= 10;
					lvl_1->boss->enemySprite->rect.y = 480;
					lvl_1->boss->hit = true;
				
			}
				else
					lvl_1->boss->enemySprite->rect.y = 0;
					

			//collision for the food sprites //
			if(lvl_1->foodCol_1->destroyed == false)
			{
				//( food Sprite 1)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_1->image,lvl_1->foodCol_1->xpos,lvl_1->foodCol_1->ypos) == 1)
				{
					lvl_1->mainChar->eating = true;
					if(lvl_1->food_1->dead != true)
					{
						lvl_1->food_1->foodHealth -=10;
					}
					lvl_1->mainChar->health += 10;
					//plays sound for character eating food//
					Mix_PlayChannel(2,eat,0);
				}
				else 
					lvl_1->mainChar->eating = false;
				
			}
			else 
				lvl_1->mainChar->eating = false;
			
			
			if(lvl_1->foodCol_2->destroyed == false)
			{
				//( food Sprite 2)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_2->image,lvl_1->foodCol_2->xpos,lvl_1->foodCol_2->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_2->dead != true)
					{
						lvl_1->food_2->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;
			
			//food sprite 3//
			if(lvl_1->foodCol_3->destroyed == false)
			{
				//( food Sprite 3)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_3->image,lvl_1->foodCol_3->xpos,lvl_1->foodCol_3->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_3->dead != true)
					{
						lvl_1->food_3->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;
				
			//food sprite 4//
			if(lvl_1->foodCol_4->destroyed == false)
			{
				//( food Sprite 4)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_4->image,lvl_1->foodCol_4->xpos,lvl_1->foodCol_4->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_4->dead != true)
					{
						lvl_1->food_4->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;
		
			//food sprite 5//
			if(lvl_1->foodCol_5->destroyed == false)
			{
				//( food Sprite 5)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_5->image,lvl_1->foodCol_5->xpos,lvl_1->foodCol_5->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_5->dead != true)
					{
						lvl_1->food_5->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 6//
			if(lvl_1->foodCol_6->destroyed == false)
			{
				//( food Sprite 6)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_6->image,lvl_1->foodCol_6->xpos,lvl_1->foodCol_6->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_6->dead != true)
					{
						lvl_1->food_6->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 7//
			if(lvl_1->foodCol_7->destroyed == false)
			{
				//( food Sprite 7)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_7->image,lvl_1->foodCol_7->xpos,lvl_1->foodCol_7->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_7->dead != true)
					{
						lvl_1->food_7->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;
			
			//food sprite 8//
			if(lvl_1->foodCol_8->destroyed == false)
			{
				//( food Sprite 8)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_8->image,lvl_1->foodCol_8->xpos,lvl_1->foodCol_8->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_8->dead != true)
					{
						lvl_1->food_8->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 9//
			if(lvl_1->foodCol_9->destroyed == false)
			{
				//( food Sprite 9)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_9->image,lvl_1->foodCol_9->xpos,lvl_1->foodCol_9->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_9->dead != true)
					{
						lvl_1->food_9->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 10//
			if(lvl_1->foodCol_10->destroyed == false)
			{
				//( food Sprite 10)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_10->image,lvl_1->foodCol_10->xpos,lvl_1->foodCol_10->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_10->dead != true)
					{
						lvl_1->food_10->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 11//
			if(lvl_1->foodCol_11->destroyed == false)
			{
				//( food Sprite 11)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_11->image,lvl_1->foodCol_11->xpos,lvl_1->foodCol_11->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_11->dead != true)
					{
						lvl_1->food_11->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 12//
			if(lvl_1->foodCol_11->destroyed == false)
			{
				//( food Sprite 12)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_12->image,lvl_1->foodCol_12->xpos,lvl_1->foodCol_12->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_12->dead != true)
					{
						lvl_1->food_12->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 13//
			if(lvl_1->foodCol_13->destroyed == false)
			{
				//( food Sprite 13)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_13->image,lvl_1->foodCol_13->xpos,lvl_1->foodCol_13->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_13->dead != true)
					{
						lvl_1->food_13->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 14//
			if(lvl_1->foodCol_14->destroyed == false)
			{
				//( food Sprite 14)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_14->image,lvl_1->foodCol_14->xpos,lvl_1->foodCol_14->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_14->dead != true)
					{
						lvl_1->food_14->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 15//
			if(lvl_1->foodCol_15->destroyed == false)
			{
				//( food Sprite 15)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_15->image,lvl_1->foodCol_15->xpos,lvl_1->foodCol_15->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_15->dead != true)
					{
						lvl_1->food_15->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 16//
			if(lvl_1->foodCol_16->destroyed == false)
			{
				//( food Sprite 16)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_16->image,lvl_1->foodCol_16->xpos,lvl_1->foodCol_16->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_16->dead != true)
					{
						lvl_1->food_16->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 17//
			if(lvl_1->foodCol_17->destroyed == false)
			{
				//( food Sprite 17)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_17->image,lvl_1->foodCol_17->xpos,lvl_1->foodCol_17->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_17->dead != true)
					{
						lvl_1->food_17->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 18//
			if(lvl_1->foodCol_18->destroyed == false)
			{
				//( food Sprite 18)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_18->image,lvl_1->foodCol_18->xpos,lvl_1->foodCol_18->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_18->dead != true)
					{
						lvl_1->food_18->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 19//
			if(lvl_1->foodCol_19->destroyed == false)
			{
				//( food Sprite 19)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_19->image,lvl_1->foodCol_19->xpos,lvl_1->foodCol_19->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_19->dead != true)
					{
						lvl_1->food_19->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;

			//food sprite 20//
			if(lvl_1->foodCol_20->destroyed == false)
			{
				//( food Sprite 20)//
				if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->foodCol_20->image,lvl_1->foodCol_20->xpos,lvl_1->foodCol_20->ypos) == 1)
				 {
					lvl_1->mainChar->eating = true;
					lvl_1->mainChar->health += 10;
					if(lvl_1->food_20->dead != true)
					{
						lvl_1->food_20->foodHealth -=10;
						//plays sound for character eating food//
						Mix_PlayChannel(2,eat,0);
					}
				 }
				
			}
			else 
					lvl_1->mainChar->eating = false;



			//IF BOSS HEALTH DEAD//
			if (lvl_1->boss->dead != true)
			{
				if(lvl_1->boss->enemyHealth == 0)
				{

					lvl_1->boss->dead = true;
					lvl_1->bossCol_1->destroyed = true;
					lvl_1->bossCol_2->destroyed = true;
					lvl_1->bossCol_3->destroyed = true;
					lvl_1->bossCol_4->destroyed = true;
				}
			}

			//IF MAIN CHAR IS DEAD//
			if (lvl_1->mainChar->dead != true)
			{
				if(lvl_1->mainChar->health == 0)
				{
					lvl_1->mainChar->dead = true;
					lvl_1->col->destroyed = true;
				}
			}


			
			//IF THE FOOD'S HEALTH IS 0 DEAD TRUE//
			if(lvl_1->food_1->dead != true)
			{
				if(lvl_1->food_1->foodHealth == 0)
				{
					lvl_1->food_1->dead = true;
					lvl_1->foodCol_1->destroyed = true;
				}
			}

			//IF FOOD 2 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_2->dead != true)
			{
				if(lvl_1->food_2->foodHealth == 0)
				{
					lvl_1->food_2->dead = true;
					lvl_1->foodCol_2->destroyed = true;
				}
			}

			//IF FOOD 3 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_3->dead != true)
			{
				if(lvl_1->food_3->foodHealth == 0)
				{
					lvl_1->food_3->dead = true;
					lvl_1->foodCol_3->destroyed = true;
				}
			}

			//IF FOOD 4 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_4->dead != true)
			{
				if(lvl_1->food_4->foodHealth == 0)
				{
					lvl_1->food_4->dead = true;
					lvl_1->foodCol_4->destroyed = true;
				}
			}

			//IF FOOD 5 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_5->dead != true)
			{
				if(lvl_1->food_5->foodHealth == 0)
				{
					lvl_1->food_5->dead = true;
					lvl_1->foodCol_5->destroyed = true;
				}
			}

			//IF FOOD 6 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_6->dead != true)
			{
				if(lvl_1->food_6->foodHealth == 0)
				{
					lvl_1->food_6->dead = true;
					lvl_1->foodCol_6->destroyed = true;
				}
			}

			//IF FOOD 7 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_7->dead != true)
			{
				if(lvl_1->food_7->foodHealth == 0)
				{
					lvl_1->food_7->dead = true;
					lvl_1->foodCol_7->destroyed = true;
				}
			}

			//IF FOOD 8 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_8->dead != true)
			{
				if(lvl_1->food_8->foodHealth == 0)
				{
					lvl_1->food_8->dead = true;
					lvl_1->foodCol_8->destroyed = true;
				}
			}

			//IF FOOD 9 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_9->dead != true)
			{
				if(lvl_1->food_9->foodHealth == 0)
				{
					lvl_1->food_9->dead = true;
					lvl_1->foodCol_9->destroyed = true;
				}
			}

			//IF FOOD 10 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_10->dead != true)
			{
				if(lvl_1->food_10->foodHealth == 0)
				{
					lvl_1->food_10->dead = true;
					lvl_1->foodCol_10->destroyed = true;
				}
			}

			//IF FOOD 11 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_11->dead != true)
			{
				if(lvl_1->food_11->foodHealth == 0)
				{
					lvl_1->food_11->dead = true;
					lvl_1->foodCol_11->destroyed = true;
				}
			}

			//IF FOOD 12 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_12->dead != true)
			{
				if(lvl_1->food_12->foodHealth == 0)
				{
					lvl_1->food_12->dead = true;
					lvl_1->foodCol_12->destroyed = true;
				}
			}

			//IF FOOD 13 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_13->dead != true)
			{
				if(lvl_1->food_13->foodHealth == 0)
				{
					lvl_1->food_13->dead = true;
					lvl_1->foodCol_13->destroyed = true;
				}
			}

			//IF FOOD 14 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_14->dead != true)
			{
				if(lvl_1->food_14->foodHealth == 0)
				{
					lvl_1->food_14->dead = true;
					lvl_1->foodCol_14->destroyed = true;
				}
			}

			//IF FOOD 15 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_15->dead != true)
			{
				if(lvl_1->food_15->foodHealth == 0)
				{
					lvl_1->food_15->dead = true;
					lvl_1->foodCol_15->destroyed = true;
				}
			}

			//IF FOOD 16 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_16->dead != true)
			{
				if(lvl_1->food_16->foodHealth == 0)
				{
					lvl_1->food_16->dead = true;
					lvl_1->foodCol_16->destroyed = true;
				}
			}

			//IF FOOD 17 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_17->dead != true)
			{
				if(lvl_1->food_17->foodHealth == 0)
				{
					lvl_1->food_17->dead = true;
					lvl_1->foodCol_17->destroyed = true;
				}
			}

			//IF FOOD 18 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_18->dead != true)
			{
				if(lvl_1->food_18->foodHealth == 0)
				{
					lvl_1->food_18->dead = true;
					lvl_1->foodCol_18->destroyed = true;
				}
			}

			//IF FOOD 19 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_19->dead != true)
			{
				if(lvl_1->food_19->foodHealth == 0)
				{
					lvl_1->food_19->dead = true;
					lvl_1->foodCol_19->destroyed = true;
				}
			}

			//IF FOOD 20 HEALTH IS O DEAD TRUE//
			if(lvl_1->food_20->dead != true)
			{
				if(lvl_1->food_20->foodHealth == 0)
				{
					lvl_1->food_20->dead = true;
					lvl_1->foodCol_20->destroyed = true;
				}
			}

		}
	} //while loop	

	//if buttonpressed move the character//
	if(buttonState == 1)
		{	

			
			//IF THE BOSS HITS THE MAIN CHAR//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->bossCol_5->image,lvl_1->bossCol_5->xpos,lvl_1->bossCol_5->ypos) == 1 || SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->bossCol_5->image,lvl_1->bossCol_5->xpos,lvl_1->bossCol_5->ypos) == 1 || SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->bossCol_6->image,lvl_1->bossCol_6->xpos,lvl_1->bossCol_6->ypos) == 1 ||  SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->bossCol_7->image,lvl_1->bossCol_7->xpos,lvl_1->bossCol_7->ypos) == 1 ||  SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->bossCol_8->image,lvl_1->bossCol_8->xpos,lvl_1->bossCol_8->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
			}
			printf("timer %d\n", fps->get_ticks());
			
			//collison for the enemies//
			if(lvl_1->enemy1->dead != true)
			{
			//IF MAINCHAR COLLIDES WITH  1'st ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol->image,lvl_1->enemyCol->xpos,lvl_1->enemyCol->ypos) == 1 && charAttack == true)
			{
				lvl_1->hit->Draw_Sprite(screen);
				lvl_1->hit->Animate(0,20);
				lvl_1->enemy1->enemyHealth -= 10;
				//Plays the sound Once//
				if (fps->get_ticks() >= 100)
				{
					
					fps->reset();
					Mix_PlayChannel(2,enemyHit,0);
				}
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol->image,lvl_1->enemyCol->xpos,lvl_1->enemyCol->ypos) == 1)
			{
					
					lvl_1->mainChar->health -= 1;
					lvl_1->enemy1->hit = false;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}	

		if(lvl_1->enemy2->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 2 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_2->image,lvl_1->enemyCol_2->xpos,lvl_1->enemyCol_2->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy2->enemyHealth -= 10;
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_2->image,lvl_1->enemyCol_2->xpos,lvl_1->enemyCol_2->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}	

		if(lvl_1->enemy3->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 3 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_3->image,lvl_1->enemyCol_3->xpos,lvl_1->enemyCol_3->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy3->enemyHealth -= 10;
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_3->image,lvl_1->enemyCol_3->xpos,lvl_1->enemyCol_3->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
			

		if(lvl_1->enemy4->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 4 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_4->image,lvl_1->enemyCol_4->xpos,lvl_1->enemyCol_4->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy4->enemyHealth -= 10;
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_4->image,lvl_1->enemyCol_4->xpos,lvl_1->enemyCol_4->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
			

		if(lvl_1->enemy5->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 5 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_5->image,lvl_1->enemyCol_5->xpos,lvl_1->enemyCol_5->ypos) == 1 && charAttack == true)
			{

				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				//lowers Enemys Health//
				lvl_1->enemy5->enemyHealth -= 10;
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_5->image,lvl_1->enemyCol_5->xpos,lvl_1->enemyCol_5->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
			

		if(lvl_1->enemy6->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 6 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_6->image,lvl_1->enemyCol_6->xpos,lvl_1->enemyCol_6->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy6->enemyHealth -= 10;	
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_6->image,lvl_1->enemyCol_6->xpos,lvl_1->enemyCol_6->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
			
	
		if(lvl_1->enemy7->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 7 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_7->image,lvl_1->enemyCol_7->xpos,lvl_1->enemyCol_7->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy7->enemyHealth -= 10;
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_7->image,lvl_1->enemyCol_7->xpos,lvl_1->enemyCol_7->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
			

		if(lvl_1->enemy8->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 8 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_8->image,lvl_1->enemyCol_8->xpos,lvl_1->enemyCol_8->ypos) == 1 && charAttack == true)
			{
				
					//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy8->enemyHealth -= 10;
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_8->image,lvl_1->enemyCol_8->xpos,lvl_1->enemyCol_8->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
			
		}
		

		if(lvl_1->enemy9->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 9 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_9->image,lvl_1->enemyCol_9->xpos,lvl_1->enemyCol_9->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy9->enemyHealth -= 10;
					
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_9->image,lvl_1->enemyCol_9->xpos,lvl_1->enemyCol_9->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}

		if(lvl_1->enemy10->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 10 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_10->image,lvl_1->enemyCol_10->xpos,lvl_1->enemyCol_10->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy10->enemyHealth -= 10;		
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_10->image,lvl_1->enemyCol_10->xpos,lvl_1->enemyCol_10->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;	
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
			

		if(lvl_1->enemy11->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 11 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_11->image,lvl_1->enemyCol_11->xpos,lvl_1->enemyCol_11->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy11->enemyHealth -= 10;
			}
			else if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_11->image,lvl_1->enemyCol_11->xpos,lvl_1->enemyCol_11->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
			

		if(lvl_1->enemy12->dead != true)
		{
			//IF MAINCHAR COLLIDES WITH 12 ENEMY//
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_12->image,lvl_1->enemyCol_12->xpos,lvl_1->enemyCol_12->ypos) == 1 && charAttack == true)
			{
				//Plays the sound Once//
				if (fps->get_ticks() >= 500)
				{
					fps->start();
					Mix_PlayChannel(2,enemyHit,0);
				}
				lvl_1->enemy12->enemyHealth -= 10;
			}
			if(SDL_BoundingCollide(lvl_1->col->image,lvl_1->col->xpos,lvl_1->col->ypos,lvl_1->enemyCol_12->image,lvl_1->enemyCol_12->xpos,lvl_1->enemyCol_12->ypos) == 1)
			{
				lvl_1->mainChar->health -= 1;
				//plays the hit sound for the player//
				if(fps->get_ticks() >= 400)
				{
					fps->reset();
					Mix_PlayChannel(2,playerHit,0);
				}
			}
		}
	
		

		
			//IF THE ENEMYS HEALTH 1 DEAD TRUE//
			if (lvl_1->enemy1->dead != true)
			{
				if(lvl_1->enemy1->enemyHealth == 0)
				{
					lvl_1->enemy1->run_once = false;
					lvl_1->enemy1->dead = true;
					lvl_1->enemyCol->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 2 DEAD TRUE//
			if (lvl_1->enemy2->dead != true)
			{
				if(lvl_1->enemy2->enemyHealth == 0)
				{
					lvl_1->enemy2->dead = true;
					lvl_1->enemyCol_2->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 3 DEAD TRUE//
			if (lvl_1->enemy3->dead != true)
			{
				if(lvl_1->enemy3->enemyHealth == 0)
				{
					lvl_1->enemy3->dead = true;
					lvl_1->enemyCol_3->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 4 DEAD TRUE//
			if (lvl_1->enemy4->dead != true)
			{
				if(lvl_1->enemy4->enemyHealth == 0)
				{
					lvl_1->enemy4->dead = true;
					lvl_1->enemyCol_4->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 5 DEAD TRUE//
			if (lvl_1->enemy5->dead != true)
			{
				if(lvl_1->enemy5->enemyHealth == 0)
				{
					lvl_1->enemy5->dead = true;
					lvl_1->enemyCol_5->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 6 DEAD TRUE//
			if (lvl_1->enemy6->dead != true)
			{
				if(lvl_1->enemy6->enemyHealth == 0)
				{
					lvl_1->enemy6->dead = true;
					lvl_1->enemyCol_6->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 7 DEAD TRUE//
			if (lvl_1->enemy7->dead != true)
			{
				if(lvl_1->enemy7->enemyHealth == 0)
				{
					lvl_1->enemy7->dead = true;
					lvl_1->enemyCol_7->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 8 DEAD TRUE//
			if (lvl_1->enemy8->dead != true)
			{
				if(lvl_1->enemy8->enemyHealth == 0)
				{
					lvl_1->enemy8->dead = true;
					lvl_1->enemyCol_8->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 9 DEAD TRUE//
			if (lvl_1->enemy9->dead != true)
			{
				if(lvl_1->enemy9->enemyHealth == 0)
				{
					lvl_1->enemy9->dead = true;
					lvl_1->enemyCol_9->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 10 DEAD TRUE//
			if (lvl_1->enemy10->dead != true)
			{
				if(lvl_1->enemy10->enemyHealth == 0)
				{
					lvl_1->enemy10->dead = true;
					lvl_1->enemyCol_10->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 11 DEAD TRUE//
			if (lvl_1->enemy11->dead != true)
			{
				if(lvl_1->enemy11->enemyHealth == 0)
				{
					lvl_1->enemy11->dead = true;
					lvl_1->enemyCol_11->destroyed = true;
				}
			}

			//IF THE ENEMYS HEALTH 12 DEAD TRUE//
			if (lvl_1->enemy12->dead != true)
			{
				if(lvl_1->enemy12->enemyHealth == 0)
				{
					lvl_1->enemy12->dead = true;
					lvl_1->enemyCol_12->destroyed = true;
				}
			}








			
			//stores the mouse x and y  positions//		
			SDL_GetMouseState(&xMouse,&yMouse);

			
			
			
				

				//centers the point of rotation on the sprite//
				xVel = xMouse - lvl_1->mainChar->characterSprite->xpos  - 119; // - background->xpos
				yVel = yMouse - lvl_1->mainChar->characterSprite->ypos  - 113; // - background->ypos



				//calcs the distance between the mouse and sprite//
				dist = sqrt(pow(xVel, 2) + pow(yVel, 2));

				if (dist > 8 && dist < 100)
				{
					xVel = floor(xVel / dist * 10 + 0.5);
					yVel = floor(yVel / dist * 10 + 0.5);
				
					

					angle = atan2(xVel, yVel) * 180 / 3.14159 - 90;
					angle = angle < 0 ? angle + 360 : angle;
					lvl_1->mainChar->characterSprite->move(xVel,yVel);
					lvl_1->charCol->move(xVel,yVel);
					
				}
				else if(dist > 100 && dist < 200)
				{
					xVel = floor(xVel / dist * 15 + 0.5);
					yVel = floor(yVel / dist * 15 + 0.5);
					

					angle = atan2(xVel, yVel) * 180 / 3.14159 - 90;
					angle = angle < 0 ? angle + 360 : angle;
					lvl_1->mainChar->characterSprite->move(xVel,yVel);
					lvl_1->charCol->move(xVel,yVel);
					
				}
				else if(dist > 200 && dist < 400)
				{
					xVel = floor(xVel / dist * 17 + 0.5);
					yVel = floor(yVel / dist * 17 + 0.5);
					
					
					angle = atan2(xVel, yVel) * 180 / 3.14159 - 90;
					angle = angle < 0 ? angle + 360 : angle;
					lvl_1->mainChar->characterSprite->move(xVel,yVel);
					lvl_1->charCol->move(xVel,yVel);
					
				}
				else if(dist > 400 )
				{
					xVel = floor(xVel / dist * 20 + 0.5);
					yVel = floor(yVel / dist * 20 + 0.5);
					
					
					angle = atan2(xVel, yVel) * 180 / 3.14159 - 90;
					angle = angle < 0 ? angle + 360 : angle;
					lvl_1->mainChar->characterSprite->move(xVel,yVel);
					lvl_1->charCol->move(xVel,yVel);
					
				}
				else 
					lvl_1->mainChar->moving = false;


			//ANIMATES THE MAIN CHAR//
			
			if(lvl_1->mainChar->dead != true)
			{
				if( lvl_1->mainChar->eating == true)
				{
					lvl_1->mainChar->characterSprite->Animate(8,12);
				}
				else if ( charAttack == true)
				{
					lvl_1->mainChar->characterSprite->Animate(13,16);
				}
				else 
					lvl_1->mainChar->characterSprite->Animate(0,7);
		
			}
			
	
			

		
	}//end buttonState if statement//



			//KEEPS THE PLAYER ON SCREEN AND MOVES SPRITES//
			//top of the screen//
			if(	lvl_1->mainChar->characterSprite->ypos <= 250 && charAngle == 0 )
			{
	
				if(lvl_1->background->ypos == 0)
				{
					lvl_1->mainChar->characterSprite->move(0,-velocity);
					lvl_1->background->move(0,-velocity);
					lvl_1->charCol->move(0,-velocity);
					lvl_1->bossCol_1->move(0,-velocity);
					lvl_1->bossCol_2->move(0,-velocity);
					lvl_1->bossCol_3->move(0,-velocity);
					lvl_1->bossCol_4->move(0,-velocity);
					lvl_1->enemy1->enemySprite->move(0,-velocity);
					lvl_1->enemy2->enemySprite->move(0,-velocity);
					lvl_1->enemy3->enemySprite->move(0,-velocity);
					lvl_1->enemy4->enemySprite->move(0,-velocity);
					lvl_1->enemy5->enemySprite->move(0,-velocity);
					lvl_1->enemy6->enemySprite->move(0,-velocity);
					lvl_1->enemy7->enemySprite->move(0,-velocity);
					lvl_1->enemy8->enemySprite->move(0,-velocity);
					lvl_1->enemy9->enemySprite->move(0,-velocity);
					lvl_1->enemy10->enemySprite->move(0,-velocity);
					lvl_1->enemy11->enemySprite->move(0,-velocity);
					lvl_1->enemy12->enemySprite->move(0,-velocity);
					lvl_1->food_1->foodSprite->move(0,-velocity);
					lvl_1->food_2->foodSprite->move(0,-velocity);
					lvl_1->food_3->foodSprite->move(0,-velocity);
					lvl_1->food_4->foodSprite->move(0,-velocity);
					lvl_1->food_5->foodSprite->move(0,-velocity);
					lvl_1->food_6->foodSprite->move(0,-velocity);
					lvl_1->food_7->foodSprite->move(0,-velocity);
					lvl_1->food_8->foodSprite->move(0,-velocity);
					lvl_1->food_9->foodSprite->move(0,-velocity);
					lvl_1->food_10->foodSprite->move(0,-velocity);
					lvl_1->food_11->foodSprite->move(0,-velocity);
					lvl_1->food_12->foodSprite->move(0,-velocity);
					lvl_1->food_13->foodSprite->move(0,-velocity);
					lvl_1->food_14->foodSprite->move(0,-velocity);
					lvl_1->food_15->foodSprite->move(0,-velocity);
					lvl_1->food_16->foodSprite->move(0,-velocity);
					lvl_1->food_17->foodSprite->move(0,-velocity);
					lvl_1->food_18->foodSprite->move(0,-velocity);
					lvl_1->food_19->foodSprite->move(0,-velocity);
					lvl_1->food_20->foodSprite->move(0,-velocity);
					lvl_1->boss->enemySprite->move(0,-velocity);	
				}
				lvl_1->mainChar->characterSprite->move(0,-yVel);
				lvl_1->background->move(0,velocity);
				lvl_1->charCol->move(0,velocity);
				lvl_1->bossCol_1->move(0,velocity);
				lvl_1->bossCol_2->move(0,velocity);
				lvl_1->bossCol_3->move(0,velocity);
				lvl_1->bossCol_4->move(0,velocity);
				lvl_1->enemy1->enemySprite->move(0,velocity);
				lvl_1->enemy2->enemySprite->move(0,velocity);
				lvl_1->enemy3->enemySprite->move(0,velocity);
				lvl_1->enemy4->enemySprite->move(0,velocity);
				lvl_1->enemy5->enemySprite->move(0,velocity);
				lvl_1->enemy6->enemySprite->move(0,velocity);
				lvl_1->enemy7->enemySprite->move(0,velocity);
				lvl_1->enemy8->enemySprite->move(0,velocity);
				lvl_1->enemy9->enemySprite->move(0,velocity);
				lvl_1->enemy10->enemySprite->move(0,velocity);
				lvl_1->enemy11->enemySprite->move(0,velocity);
				lvl_1->enemy12->enemySprite->move(0,velocity);
				lvl_1->food_1->foodSprite->move(0,velocity);
				lvl_1->food_2->foodSprite->move(0,velocity);
				lvl_1->food_3->foodSprite->move(0,velocity);
				lvl_1->food_4->foodSprite->move(0,velocity);
				lvl_1->food_5->foodSprite->move(0,velocity);
				lvl_1->food_6->foodSprite->move(0,velocity);
				lvl_1->food_7->foodSprite->move(0,velocity);
				lvl_1->food_8->foodSprite->move(0,velocity);
				lvl_1->food_9->foodSprite->move(0,velocity);
				lvl_1->food_10->foodSprite->move(0,velocity);
				lvl_1->food_11->foodSprite->move(0,velocity);
				lvl_1->food_12->foodSprite->move(0,velocity);
				lvl_1->food_13->foodSprite->move(0,velocity);
				lvl_1->food_14->foodSprite->move(0,velocity);
				lvl_1->food_15->foodSprite->move(0,velocity);
				lvl_1->food_16->foodSprite->move(0,velocity);
				lvl_1->food_17->foodSprite->move(0,velocity);
				lvl_1->food_18->foodSprite->move(0,velocity);
				lvl_1->food_19->foodSprite->move(0,velocity);
				lvl_1->food_20->foodSprite->move(0,velocity);
				lvl_1->boss->enemySprite->move(0,velocity);
				
			}
			//bottom of the screen//
			else if( lvl_1->mainChar->characterSprite->ypos >= 300 && charAngle == 5 )
			{
				if(lvl_1->background->ypos == -5000)
				{
					lvl_1->mainChar->characterSprite->move(0,velocity);
					lvl_1->background->move(0,velocity);
					lvl_1->charCol->move(0,velocity);
					lvl_1->bossCol_1->move(0,velocity);
					lvl_1->bossCol_2->move(0,velocity);
					lvl_1->bossCol_3->move(0,velocity);
					lvl_1->bossCol_4->move(0,velocity);
					lvl_1->enemy1->enemySprite->move(0,velocity);
					lvl_1->enemy2->enemySprite->move(0,velocity);
					lvl_1->enemy3->enemySprite->move(0,velocity);
					lvl_1->enemy4->enemySprite->move(0,velocity);
					lvl_1->enemy5->enemySprite->move(0,velocity);
					lvl_1->enemy6->enemySprite->move(0,velocity);
					lvl_1->enemy7->enemySprite->move(0,velocity);
					lvl_1->enemy8->enemySprite->move(0,velocity);
					lvl_1->enemy9->enemySprite->move(0,velocity);
					lvl_1->enemy10->enemySprite->move(0,velocity);
					lvl_1->enemy11->enemySprite->move(0,velocity);
					lvl_1->enemy12->enemySprite->move(0,velocity);
					lvl_1->food_1->foodSprite->move(0,velocity);
					lvl_1->food_2->foodSprite->move(0,velocity);
					lvl_1->food_3->foodSprite->move(0,velocity);
					lvl_1->food_4->foodSprite->move(0,velocity);
					lvl_1->food_5->foodSprite->move(0,velocity);
					lvl_1->food_6->foodSprite->move(0,velocity);
					lvl_1->food_7->foodSprite->move(0,velocity);
					lvl_1->food_8->foodSprite->move(0,velocity);
					lvl_1->food_9->foodSprite->move(0,velocity);
					lvl_1->food_10->foodSprite->move(0,velocity);
					lvl_1->food_11->foodSprite->move(0,velocity);
					lvl_1->food_12->foodSprite->move(0,velocity);
					lvl_1->food_13->foodSprite->move(0,velocity);
					lvl_1->food_14->foodSprite->move(0,velocity);
					lvl_1->food_15->foodSprite->move(0,velocity);
					lvl_1->food_16->foodSprite->move(0,velocity);
					lvl_1->food_17->foodSprite->move(0,velocity);
					lvl_1->food_18->foodSprite->move(0,velocity);
					lvl_1->food_19->foodSprite->move(0,velocity);
					lvl_1->food_20->foodSprite->move(0,velocity);
					lvl_1->boss->enemySprite->move(0,velocity);	
				}
				
				lvl_1->mainChar->characterSprite->move(0,-yVel);
				lvl_1->background->move(0,-velocity);
				lvl_1->charCol->move(0,-velocity);
				lvl_1->bossCol_1->move(0,-velocity);
				lvl_1->bossCol_2->move(0,-velocity);
				lvl_1->bossCol_3->move(0,-velocity);
				lvl_1->bossCol_4->move(0,-velocity);
				lvl_1->enemy1->enemySprite->move(0,-velocity);
				lvl_1->enemy2->enemySprite->move(0,-velocity);
				lvl_1->enemy3->enemySprite->move(0,-velocity);
				lvl_1->enemy4->enemySprite->move(0,-velocity);
				lvl_1->enemy5->enemySprite->move(0,-velocity);
				lvl_1->enemy6->enemySprite->move(0,-velocity);
				lvl_1->enemy7->enemySprite->move(0,-velocity);
				lvl_1->enemy8->enemySprite->move(0,-velocity);
				lvl_1->enemy9->enemySprite->move(0,-velocity);
				lvl_1->enemy10->enemySprite->move(0,-velocity);
				lvl_1->enemy11->enemySprite->move(0,-velocity);
				lvl_1->enemy12->enemySprite->move(0,-velocity);
				lvl_1->food_1->foodSprite->move(0,-velocity);
				lvl_1->food_2->foodSprite->move(0,-velocity);
				lvl_1->food_3->foodSprite->move(0,-velocity);
				lvl_1->food_4->foodSprite->move(0,-velocity);
				lvl_1->food_5->foodSprite->move(0,-velocity);
				lvl_1->food_6->foodSprite->move(0,-velocity);
				lvl_1->food_7->foodSprite->move(0,-velocity);
				lvl_1->food_8->foodSprite->move(0,-velocity);
				lvl_1->food_9->foodSprite->move(0,-velocity);
				lvl_1->food_10->foodSprite->move(0,-velocity);
				lvl_1->food_11->foodSprite->move(0,-velocity);
				lvl_1->food_12->foodSprite->move(0,-velocity);
				lvl_1->food_13->foodSprite->move(0,-velocity);
				lvl_1->food_14->foodSprite->move(0,-velocity);
				lvl_1->food_15->foodSprite->move(0,-velocity);
				lvl_1->food_16->foodSprite->move(0,-velocity);
				lvl_1->food_17->foodSprite->move(0,-velocity);
				lvl_1->food_18->foodSprite->move(0,-velocity);
				lvl_1->food_19->foodSprite->move(0,-velocity);
				lvl_1->food_20->foodSprite->move(0,-velocity);
				lvl_1->boss->enemySprite->move(0,-velocity);
			}
			//left side of the screen//
			else if(lvl_1->mainChar->characterSprite->xpos <= 300 && charAngle == 7)
			{

				if(lvl_1->background->xpos == 0)
				{
					lvl_1->mainChar->characterSprite->move(-velocity,0);
					lvl_1->background->move(-velocity,0);
					lvl_1->charCol->move(-velocity,0);
					lvl_1->bossCol_1->move(-velocity,0);
					lvl_1->bossCol_2->move(-velocity,0);
					lvl_1->bossCol_3->move(-velocity,0);
					lvl_1->bossCol_4->move(-velocity,0);
					lvl_1->enemy1->enemySprite->move(-velocity,0);
					lvl_1->enemy2->enemySprite->move(-velocity,0);
					lvl_1->enemy3->enemySprite->move(-velocity,0);
					lvl_1->enemy4->enemySprite->move(-velocity,0);
					lvl_1->enemy5->enemySprite->move(-velocity,0);
					lvl_1->enemy6->enemySprite->move(-velocity,0);
					lvl_1->enemy7->enemySprite->move(-velocity,0);
					lvl_1->enemy8->enemySprite->move(-velocity,0);
					lvl_1->enemy9->enemySprite->move(-velocity,0);
					lvl_1->enemy10->enemySprite->move(-velocity,0);
					lvl_1->enemy11->enemySprite->move(-velocity,0);
					lvl_1->enemy12->enemySprite->move(-velocity,0);
					lvl_1->food_1->foodSprite->move(-velocity,0);
					lvl_1->food_2->foodSprite->move(-velocity,0);
					lvl_1->food_3->foodSprite->move(-velocity,0);
					lvl_1->food_4->foodSprite->move(-velocity,0);
					lvl_1->food_5->foodSprite->move(-velocity,0);
					lvl_1->food_6->foodSprite->move(-velocity,0);
					lvl_1->food_7->foodSprite->move(-velocity,0);
					lvl_1->food_8->foodSprite->move(-velocity,0);
					lvl_1->food_9->foodSprite->move(-velocity,0);
					lvl_1->food_10->foodSprite->move(-velocity,0);
					lvl_1->food_11->foodSprite->move(-velocity,0);
					lvl_1->food_12->foodSprite->move(-velocity,0);
					lvl_1->food_13->foodSprite->move(-velocity,0);
					lvl_1->food_14->foodSprite->move(-velocity,0);
					lvl_1->food_15->foodSprite->move(-velocity,0);
					lvl_1->food_16->foodSprite->move(-velocity,0);
					lvl_1->food_17->foodSprite->move(-velocity,0);
					lvl_1->food_18->foodSprite->move(-velocity,0);
					lvl_1->food_19->foodSprite->move(-velocity,0);
					lvl_1->food_20->foodSprite->move(-velocity,0);
					lvl_1->boss->enemySprite->move(-velocity,0);
				}

				lvl_1->mainChar->characterSprite->move(-xVel,0);
				lvl_1->background->move(velocity,0);
				lvl_1->charCol->move(velocity,0);
				lvl_1->bossCol_1->move(velocity,0);
				lvl_1->bossCol_2->move(velocity,0);
				lvl_1->bossCol_3->move(velocity,0);
				lvl_1->bossCol_4->move(velocity,0);
				lvl_1->enemy1->enemySprite->move(velocity,0);
				lvl_1->enemy2->enemySprite->move(velocity,0);
				lvl_1->enemy3->enemySprite->move(velocity,0);
				lvl_1->enemy4->enemySprite->move(velocity,0);
				lvl_1->enemy5->enemySprite->move(velocity,0);
				lvl_1->enemy6->enemySprite->move(velocity,0);
				lvl_1->enemy7->enemySprite->move(velocity,0);
				lvl_1->enemy8->enemySprite->move(velocity,0);
				lvl_1->enemy9->enemySprite->move(velocity,0);
				lvl_1->enemy10->enemySprite->move(velocity,0);
				lvl_1->enemy11->enemySprite->move(velocity,0);
				lvl_1->enemy12->enemySprite->move(velocity,0);
				lvl_1->food_1->foodSprite->move(velocity,0);
				lvl_1->food_2->foodSprite->move(velocity,0);
				lvl_1->food_3->foodSprite->move(velocity,0);
				lvl_1->food_4->foodSprite->move(velocity,0);
				lvl_1->food_5->foodSprite->move(velocity,0);
				lvl_1->food_6->foodSprite->move(velocity,0);
				lvl_1->food_7->foodSprite->move(velocity,0);
				lvl_1->food_8->foodSprite->move(velocity,0);
				lvl_1->food_9->foodSprite->move(velocity,0);
				lvl_1->food_10->foodSprite->move(velocity,0);
				lvl_1->food_11->foodSprite->move(velocity,0);
				lvl_1->food_12->foodSprite->move(velocity,0);
				lvl_1->food_13->foodSprite->move(velocity,0);
				lvl_1->food_14->foodSprite->move(velocity,0);
				lvl_1->food_15->foodSprite->move(velocity,0);
				lvl_1->food_16->foodSprite->move(velocity,0);
				lvl_1->food_17->foodSprite->move(velocity,0);
				lvl_1->food_18->foodSprite->move(velocity,0);
				lvl_1->food_19->foodSprite->move(velocity,0);
				lvl_1->food_20->foodSprite->move(velocity,0);
				lvl_1->boss->enemySprite->move(velocity,0);
			}
			//right side of the screen//
			else if(lvl_1->mainChar->characterSprite->xpos >= 350 && charAngle == 3)
			{

				if(lvl_1->background->xpos == -4720)
				{
					lvl_1->mainChar->characterSprite->move(velocity,0);
					lvl_1->background->move(velocity,0);
					lvl_1->charCol->move(velocity,0);
					lvl_1->bossCol_1->move(velocity,0);
					lvl_1->bossCol_2->move(velocity,0);
					lvl_1->bossCol_3->move(velocity,0);
					lvl_1->bossCol_4->move(velocity,0);
					lvl_1->enemy1->enemySprite->move(velocity,0);
					lvl_1->enemy2->enemySprite->move(velocity,0);
					lvl_1->enemy3->enemySprite->move(velocity,0);
					lvl_1->enemy4->enemySprite->move(velocity,0);
					lvl_1->enemy5->enemySprite->move(velocity,0);
					lvl_1->enemy6->enemySprite->move(velocity,0);
					lvl_1->enemy7->enemySprite->move(velocity,0);
					lvl_1->enemy8->enemySprite->move(velocity,0);
					lvl_1->enemy9->enemySprite->move(velocity,0);
					lvl_1->enemy10->enemySprite->move(velocity,0);
					lvl_1->enemy11->enemySprite->move(velocity,0);
					lvl_1->enemy12->enemySprite->move(velocity,0);
					lvl_1->food_1->foodSprite->move(velocity,0);
					lvl_1->food_2->foodSprite->move(velocity,0);
					lvl_1->food_3->foodSprite->move(velocity,0);
					lvl_1->food_4->foodSprite->move(velocity,0);
					lvl_1->food_5->foodSprite->move(velocity,0);
					lvl_1->food_6->foodSprite->move(velocity,0);
					lvl_1->food_7->foodSprite->move(velocity,0);
					lvl_1->food_8->foodSprite->move(velocity,0);
					lvl_1->food_9->foodSprite->move(velocity,0);
					lvl_1->food_10->foodSprite->move(velocity,0);
					lvl_1->food_11->foodSprite->move(velocity,0);
					lvl_1->food_12->foodSprite->move(velocity,0);
					lvl_1->food_13->foodSprite->move(velocity,0);
					lvl_1->food_14->foodSprite->move(velocity,0);
					lvl_1->food_15->foodSprite->move(velocity,0);
					lvl_1->food_16->foodSprite->move(velocity,0);
					lvl_1->food_17->foodSprite->move(velocity,0);
					lvl_1->food_18->foodSprite->move(velocity,0);
					lvl_1->food_19->foodSprite->move(velocity,0);
					lvl_1->food_20->foodSprite->move(velocity,0);
					lvl_1->boss->enemySprite->move(velocity,0);
				}
				
				lvl_1->mainChar->characterSprite->move(-xVel,0);
				lvl_1->charCol->move(-velocity,0);
				lvl_1->background->move(-velocity,0);
				lvl_1->bossCol_1->move(-velocity,0);
				lvl_1->bossCol_2->move(-velocity,0);
				lvl_1->bossCol_3->move(-velocity,0);
				lvl_1->bossCol_4->move(-velocity,0);
				lvl_1->enemy1->enemySprite->move(-velocity,0);
				lvl_1->enemy2->enemySprite->move(-velocity,0);
				lvl_1->enemy3->enemySprite->move(-velocity,0);
				lvl_1->enemy4->enemySprite->move(-velocity,0);
				lvl_1->enemy5->enemySprite->move(-velocity,0);
				lvl_1->enemy6->enemySprite->move(-velocity,0);
				lvl_1->enemy7->enemySprite->move(-velocity,0);
				lvl_1->enemy8->enemySprite->move(-velocity,0);
				lvl_1->enemy9->enemySprite->move(-velocity,0);
				lvl_1->enemy10->enemySprite->move(-velocity,0);
				lvl_1->enemy11->enemySprite->move(-velocity,0);
				lvl_1->enemy12->enemySprite->move(-velocity,0);
				lvl_1->food_1->foodSprite->move(-velocity,0);
				lvl_1->food_2->foodSprite->move(-velocity,0);
				lvl_1->food_3->foodSprite->move(-velocity,0);
				lvl_1->food_4->foodSprite->move(-velocity,0);
				lvl_1->food_5->foodSprite->move(-velocity,0);
				lvl_1->food_6->foodSprite->move(-velocity,0);
				lvl_1->food_7->foodSprite->move(-velocity,0);
				lvl_1->food_8->foodSprite->move(-velocity,0);
				lvl_1->food_9->foodSprite->move(-velocity,0);
				lvl_1->food_10->foodSprite->move(-velocity,0);
				lvl_1->food_11->foodSprite->move(-velocity,0);
				lvl_1->food_12->foodSprite->move(-velocity,0);
				lvl_1->food_13->foodSprite->move(-velocity,0);
				lvl_1->food_14->foodSprite->move(-velocity,0);
				lvl_1->food_15->foodSprite->move(-velocity,0);
				lvl_1->food_16->foodSprite->move(-velocity,0);
				lvl_1->food_17->foodSprite->move(-velocity,0);
				lvl_1->food_18->foodSprite->move(-velocity,0);
				lvl_1->food_19->foodSprite->move(-velocity,0);
				lvl_1->food_20->foodSprite->move(-velocity,0);
				lvl_1->boss->enemySprite->move(-velocity,0);
			}
			//lower right of the screen//
			else if(lvl_1->mainChar->characterSprite->xpos >= 400 && lvl_1->mainChar->characterSprite->ypos >= 300 && charAngle == 4  )
			{

				//stops the background from moving on an angle//
				if(lvl_1->background->xpos == -4720 && lvl_1->background->ypos == -5000 || lvl_1->background->xpos == -4720 || lvl_1->background->ypos == -5000)
				{
					lvl_1->mainChar->characterSprite->move(velocity,velocity);
					lvl_1->background->move(velocity,velocity);
					lvl_1->charCol->move(velocity,velocity);
					lvl_1->bossCol_1->move(velocity,velocity);
					lvl_1->bossCol_2->move(velocity,velocity);
					lvl_1->bossCol_3->move(velocity,velocity);
					lvl_1->bossCol_4->move(velocity,velocity);
					lvl_1->enemy1->enemySprite->move(velocity,velocity);
					lvl_1->enemy2->enemySprite->move(velocity,velocity);
					lvl_1->enemy3->enemySprite->move(velocity,velocity);
					lvl_1->enemy4->enemySprite->move(velocity,velocity);
					lvl_1->enemy5->enemySprite->move(velocity,velocity);
					lvl_1->enemy6->enemySprite->move(velocity,velocity);
					lvl_1->enemy7->enemySprite->move(velocity,velocity);
					lvl_1->enemy8->enemySprite->move(velocity,velocity);
					lvl_1->enemy9->enemySprite->move(velocity,velocity);
					lvl_1->enemy10->enemySprite->move(velocity,velocity);
					lvl_1->enemy11->enemySprite->move(velocity,velocity);
					lvl_1->enemy12->enemySprite->move(velocity,velocity);
					lvl_1->food_1->foodSprite->move(velocity,velocity);
					lvl_1->food_2->foodSprite->move(velocity,velocity);
					lvl_1->food_3->foodSprite->move(velocity,velocity);
					lvl_1->food_4->foodSprite->move(velocity,velocity);
					lvl_1->food_5->foodSprite->move(velocity,velocity);
					lvl_1->food_6->foodSprite->move(velocity,velocity);
					lvl_1->food_7->foodSprite->move(velocity,velocity);
					lvl_1->food_8->foodSprite->move(velocity,velocity);
					lvl_1->food_9->foodSprite->move(velocity,velocity);
					lvl_1->food_10->foodSprite->move(velocity,velocity);
					lvl_1->food_11->foodSprite->move(velocity,velocity);
					lvl_1->food_12->foodSprite->move(velocity,velocity);
					lvl_1->food_13->foodSprite->move(velocity,velocity);
					lvl_1->food_14->foodSprite->move(velocity,velocity);
					lvl_1->food_15->foodSprite->move(velocity,velocity);
					lvl_1->food_16->foodSprite->move(velocity,velocity);
					lvl_1->food_17->foodSprite->move(velocity,velocity);
					lvl_1->food_18->foodSprite->move(velocity,velocity);
					lvl_1->food_19->foodSprite->move(velocity,velocity);
					lvl_1->food_20->foodSprite->move(velocity,velocity);
					lvl_1->boss->enemySprite->move(velocity,velocity);
				}
				
				lvl_1->charCol->move(velocity,velocity);
				lvl_1->background->move(-velocity,-velocity);
				lvl_1->bossCol_1->move(-velocity,-velocity);
				lvl_1->bossCol_2->move(-velocity,-velocity);
				lvl_1->bossCol_3->move(-velocity,-velocity);
				lvl_1->bossCol_4->move(-velocity,-velocity);
				lvl_1->enemy1->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy2->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy3->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy4->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy5->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy6->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy7->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy8->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy9->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy10->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy11->enemySprite->move(-velocity,-velocity);
				lvl_1->enemy12->enemySprite->move(-velocity,-velocity);
				lvl_1->food_1->foodSprite->move(-velocity,-velocity);
				lvl_1->food_2->foodSprite->move(-velocity,-velocity);
				lvl_1->food_3->foodSprite->move(-velocity,-velocity);
				lvl_1->food_4->foodSprite->move(-velocity,-velocity);
				lvl_1->food_5->foodSprite->move(-velocity,-velocity);
				lvl_1->food_6->foodSprite->move(-velocity,-velocity);
				lvl_1->food_7->foodSprite->move(-velocity,-velocity);
				lvl_1->food_8->foodSprite->move(-velocity,-velocity);
				lvl_1->food_9->foodSprite->move(-velocity,-velocity);
				lvl_1->food_10->foodSprite->move(-velocity,-velocity);
				lvl_1->food_11->foodSprite->move(-velocity,-velocity);
				lvl_1->food_12->foodSprite->move(-velocity,-velocity);
				lvl_1->food_13->foodSprite->move(-velocity,-velocity);
				lvl_1->food_14->foodSprite->move(-velocity,-velocity);
				lvl_1->food_15->foodSprite->move(-velocity,-velocity);
				lvl_1->food_16->foodSprite->move(-velocity,-velocity);
				lvl_1->food_17->foodSprite->move(-velocity,-velocity);
				lvl_1->food_18->foodSprite->move(-velocity,-velocity);
				lvl_1->food_19->foodSprite->move(-velocity,-velocity);
				lvl_1->food_20->foodSprite->move(-velocity,-velocity);
				lvl_1->boss->enemySprite->move(-velocity,-velocity);
			}
			//upper left of the screen//
			else if(lvl_1->mainChar->characterSprite->xpos <= 400 && lvl_1->mainChar->characterSprite->ypos <= 300 && charAngle == 8  )
			{
				//stops the backgound from moving if on an angle//
				if(lvl_1->background->ypos == 0 && lvl_1->background->xpos == 0 || lvl_1->background->xpos == 0 || lvl_1->background->ypos == 0)
				{
					//lvl_1->mainChar->characterSprite->move(-velocity,-velocity);
					lvl_1->background->move(-velocity,-velocity);
					lvl_1->charCol->move(-velocity,-velocity);
					lvl_1->bossCol_1->move(-velocity,-velocity);
					lvl_1->bossCol_2->move(-velocity,-velocity);
					lvl_1->bossCol_3->move(-velocity,-velocity);
					lvl_1->bossCol_4->move(-velocity,-velocity);
					lvl_1->enemy1->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy2->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy3->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy4->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy5->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy6->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy7->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy8->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy9->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy10->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy11->enemySprite->move(-velocity,-velocity);
					lvl_1->enemy12->enemySprite->move(-velocity,-velocity);
					lvl_1->food_1->foodSprite->move(-velocity,-velocity);
					lvl_1->food_2->foodSprite->move(-velocity,-velocity);
					lvl_1->food_3->foodSprite->move(-velocity,-velocity);
					lvl_1->food_4->foodSprite->move(-velocity,-velocity);
					lvl_1->food_5->foodSprite->move(-velocity,-velocity);
					lvl_1->food_6->foodSprite->move(-velocity,-velocity);
					lvl_1->food_7->foodSprite->move(-velocity,-velocity);
					lvl_1->food_8->foodSprite->move(-velocity,-velocity);
					lvl_1->food_9->foodSprite->move(-velocity,-velocity);
					lvl_1->food_10->foodSprite->move(-velocity,-velocity);
					lvl_1->food_11->foodSprite->move(-velocity,-velocity);
					lvl_1->food_12->foodSprite->move(-velocity,-velocity);
					lvl_1->food_13->foodSprite->move(-velocity,-velocity);
					lvl_1->food_14->foodSprite->move(-velocity,-velocity);
					lvl_1->food_15->foodSprite->move(-velocity,-velocity);
					lvl_1->food_16->foodSprite->move(-velocity,-velocity);
					lvl_1->food_17->foodSprite->move(-velocity,-velocity);
					lvl_1->food_18->foodSprite->move(-velocity,-velocity);
					lvl_1->food_19->foodSprite->move(-velocity,-velocity);
					lvl_1->food_20->foodSprite->move(-velocity,-velocity);
					lvl_1->boss->enemySprite->move(-velocity,-velocity);
				}
				
				
				lvl_1->background->move(velocity,velocity);
				lvl_1->bossCol_1->move(velocity,velocity);
				lvl_1->bossCol_2->move(velocity,velocity);
				lvl_1->bossCol_3->move(velocity,velocity);
				lvl_1->bossCol_4->move(velocity,velocity);
				lvl_1->enemy1->enemySprite->move(velocity,velocity);
				lvl_1->enemy2->enemySprite->move(velocity,velocity);
				lvl_1->enemy3->enemySprite->move(velocity,velocity);
				lvl_1->enemy4->enemySprite->move(velocity,velocity);
				lvl_1->enemy5->enemySprite->move(velocity,velocity);
				lvl_1->enemy6->enemySprite->move(velocity,velocity);
				lvl_1->enemy7->enemySprite->move(velocity,velocity);
				lvl_1->enemy8->enemySprite->move(velocity,velocity);
				lvl_1->enemy9->enemySprite->move(velocity,velocity);
				lvl_1->enemy10->enemySprite->move(velocity,velocity);
				lvl_1->enemy11->enemySprite->move(velocity,velocity);
				lvl_1->enemy12->enemySprite->move(velocity,velocity);
				lvl_1->food_1->foodSprite->move(velocity,velocity);
				lvl_1->food_2->foodSprite->move(velocity,velocity);
				lvl_1->food_3->foodSprite->move(velocity,velocity);
				lvl_1->food_4->foodSprite->move(velocity,velocity);
				lvl_1->food_5->foodSprite->move(velocity,velocity);
				lvl_1->food_6->foodSprite->move(velocity,velocity);
				lvl_1->food_7->foodSprite->move(velocity,velocity);
				lvl_1->food_8->foodSprite->move(velocity,velocity);
				lvl_1->food_9->foodSprite->move(velocity,velocity);
				lvl_1->food_10->foodSprite->move(velocity,velocity);
				lvl_1->food_11->foodSprite->move(velocity,velocity);
				lvl_1->food_12->foodSprite->move(velocity,velocity);
				lvl_1->food_13->foodSprite->move(velocity,velocity);
				lvl_1->food_14->foodSprite->move(velocity,velocity);
				lvl_1->food_15->foodSprite->move(velocity,velocity);
				lvl_1->food_16->foodSprite->move(velocity,velocity);
				lvl_1->food_17->foodSprite->move(velocity,velocity);
				lvl_1->food_18->foodSprite->move(velocity,velocity);
				lvl_1->food_19->foodSprite->move(velocity,velocity);
				lvl_1->food_20->foodSprite->move(velocity,velocity);
				lvl_1->boss->enemySprite->move(velocity,velocity);
			}
			//upper right of the screen//
			else if(lvl_1->mainChar->characterSprite->xpos >= 400 && lvl_1->mainChar->characterSprite->ypos <= 300 && charAngle == 1  )
			{
				//stops the backgound from moving if on an angle//
				if(lvl_1->background->ypos == 0 && lvl_1->background->xpos == 0 || lvl_1->background->xpos == -4720 || lvl_1->background->ypos == -5000)
				{
					lvl_1->mainChar->characterSprite->move(velocity,-velocity);
					lvl_1->background->move(velocity,-velocity);
					lvl_1->charCol->move(velocity,-velocity);
					lvl_1->bossCol_1->move(velocity,-velocity);
					lvl_1->bossCol_2->move(velocity,-velocity);
					lvl_1->bossCol_3->move(velocity,-velocity);
					lvl_1->bossCol_4->move(velocity,-velocity);
					lvl_1->enemy1->enemySprite->move(velocity,-velocity);
					lvl_1->enemy2->enemySprite->move(velocity,-velocity);
					lvl_1->enemy3->enemySprite->move(velocity,-velocity);
					lvl_1->enemy4->enemySprite->move(velocity,-velocity);
					lvl_1->enemy5->enemySprite->move(velocity,-velocity);
					lvl_1->enemy6->enemySprite->move(velocity,-velocity);
					lvl_1->enemy7->enemySprite->move(velocity,-velocity);
					lvl_1->enemy8->enemySprite->move(velocity,-velocity);
					lvl_1->enemy9->enemySprite->move(velocity,-velocity);
					lvl_1->enemy10->enemySprite->move(velocity,-velocity);
					lvl_1->enemy11->enemySprite->move(velocity,-velocity);
					lvl_1->enemy12->enemySprite->move(velocity,-velocity);
					lvl_1->food_1->foodSprite->move(velocity,-velocity);
					lvl_1->food_2->foodSprite->move(velocity,-velocity);
					lvl_1->food_3->foodSprite->move(velocity,-velocity);
					lvl_1->food_4->foodSprite->move(velocity,-velocity);
					lvl_1->food_5->foodSprite->move(velocity,-velocity);
					lvl_1->food_6->foodSprite->move(velocity,-velocity);
					lvl_1->food_7->foodSprite->move(velocity,-velocity);
					lvl_1->food_8->foodSprite->move(velocity,-velocity);
					lvl_1->food_9->foodSprite->move(velocity,-velocity);
					lvl_1->food_10->foodSprite->move(velocity,-velocity);
					lvl_1->food_11->foodSprite->move(velocity,-velocity);
					lvl_1->food_12->foodSprite->move(velocity,-velocity);
					lvl_1->food_13->foodSprite->move(velocity,-velocity);
					lvl_1->food_14->foodSprite->move(velocity,-velocity);
					lvl_1->food_15->foodSprite->move(velocity,-velocity);
					lvl_1->food_16->foodSprite->move(velocity,-velocity);
					lvl_1->food_17->foodSprite->move(velocity,-velocity);
					lvl_1->food_18->foodSprite->move(velocity,-velocity);
					lvl_1->food_19->foodSprite->move(velocity,-velocity);
					lvl_1->food_20->foodSprite->move(velocity,-velocity);
					lvl_1->boss->enemySprite->move(velocity,-velocity);
				}
				
				lvl_1->background->move(-velocity,velocity);
				lvl_1->bossCol_1->move(-velocity,velocity);
				lvl_1->bossCol_2->move(-velocity,velocity);
				lvl_1->bossCol_3->move(-velocity,velocity);
				lvl_1->bossCol_4->move(-velocity,velocity);
				lvl_1->enemy1->enemySprite->move(-velocity,velocity);
				lvl_1->enemy2->enemySprite->move(-velocity,velocity);
				lvl_1->enemy3->enemySprite->move(-velocity,velocity);
				lvl_1->enemy4->enemySprite->move(-velocity,velocity);
				lvl_1->enemy5->enemySprite->move(-velocity,velocity);
				lvl_1->enemy6->enemySprite->move(-velocity,velocity);
				lvl_1->enemy7->enemySprite->move(-velocity,velocity);
				lvl_1->enemy8->enemySprite->move(-velocity,velocity);
				lvl_1->enemy9->enemySprite->move(-velocity,velocity);
				lvl_1->enemy10->enemySprite->move(-velocity,velocity);
				lvl_1->enemy11->enemySprite->move(-velocity,velocity);
				lvl_1->enemy12->enemySprite->move(-velocity,velocity);
				lvl_1->food_1->foodSprite->move(-velocity,velocity);
				lvl_1->food_2->foodSprite->move(-velocity,velocity);
				lvl_1->food_3->foodSprite->move(-velocity,velocity);
				lvl_1->food_4->foodSprite->move(-velocity,velocity);
				lvl_1->food_5->foodSprite->move(-velocity,velocity);
				lvl_1->food_6->foodSprite->move(-velocity,velocity);
				lvl_1->food_7->foodSprite->move(-velocity,velocity);
				lvl_1->food_8->foodSprite->move(-velocity,velocity);
				lvl_1->food_9->foodSprite->move(-velocity,velocity);
				lvl_1->food_10->foodSprite->move(-velocity,velocity);
				lvl_1->food_11->foodSprite->move(-velocity,velocity);
				lvl_1->food_12->foodSprite->move(-velocity,velocity);
				lvl_1->food_13->foodSprite->move(-velocity,velocity);
				lvl_1->food_14->foodSprite->move(-velocity,velocity);
				lvl_1->food_15->foodSprite->move(-velocity,velocity);
				lvl_1->food_16->foodSprite->move(-velocity,velocity);
				lvl_1->food_17->foodSprite->move(-velocity,velocity);
				lvl_1->food_18->foodSprite->move(-velocity,velocity);
				lvl_1->food_19->foodSprite->move(-velocity,velocity);
				lvl_1->food_20->foodSprite->move(-velocity,velocity);
				lvl_1->boss->enemySprite->move(-velocity,velocity);
			}

		
			
			
			
			
			
			
			
			
		//ENDS KEEPING THE PLAYER ON SCREEN AND MOVING SPRITES//
		//THE END OF THE MOVING OBJECTS SECTION//

		//DEATH ANIMATION SAME SPOT AS SPRITE//
			lvl_1->death->xpos = lvl_1->enemy1->enemySprite->xpos - 270;
			lvl_1->death->ypos = lvl_1->enemy1->enemySprite->ypos - 200;

			lvl_1->death_2->xpos = lvl_1->enemy2->enemySprite->xpos - 270;
			lvl_1->death_2->ypos = lvl_1->enemy2->enemySprite->ypos - 200;

			lvl_1->death_3->xpos = lvl_1->enemy3->enemySprite->xpos - 270;
			lvl_1->death_3->ypos = lvl_1->enemy3->enemySprite->ypos - 200;

			lvl_1->death_4->xpos = lvl_1->enemy4->enemySprite->xpos - 270;
			lvl_1->death_4->ypos = lvl_1->enemy4->enemySprite->ypos - 200;

			lvl_1->death_5->xpos = lvl_1->enemy5->enemySprite->xpos - 270;
			lvl_1->death_5->ypos = lvl_1->enemy5->enemySprite->ypos - 200;

			lvl_1->death_6->xpos = lvl_1->enemy6->enemySprite->xpos - 270;
			lvl_1->death_6->ypos = lvl_1->enemy6->enemySprite->ypos - 200;

			lvl_1->death_7->xpos = lvl_1->enemy7->enemySprite->xpos - 270;
			lvl_1->death_7->ypos = lvl_1->enemy7->enemySprite->ypos - 200;

			lvl_1->death_8->xpos = lvl_1->enemy8->enemySprite->xpos - 270;
			lvl_1->death_8->ypos = lvl_1->enemy8->enemySprite->ypos - 200;

			lvl_1->death_9->xpos = lvl_1->enemy9->enemySprite->xpos - 270;
			lvl_1->death_9->ypos = lvl_1->enemy9->enemySprite->ypos - 200;

			lvl_1->death_10->xpos = lvl_1->enemy10->enemySprite->xpos - 270;
			lvl_1->death_10->ypos = lvl_1->enemy10->enemySprite->ypos - 200;

			lvl_1->death_11->xpos = lvl_1->enemy11->enemySprite->xpos - 270;
			lvl_1->death_11->ypos = lvl_1->enemy11->enemySprite->ypos - 200;

			lvl_1->death_12->xpos = lvl_1->enemy12->enemySprite->xpos - 270;
			lvl_1->death_12->ypos = lvl_1->enemy12->enemySprite->ypos - 200;



		//HIT ANIMATION SAME SPOT AS SPRITE//
			lvl_1->hit->ypos = lvl_1->enemy1->enemySprite->ypos;
			lvl_1->hit->xpos = lvl_1->enemy1->enemySprite->xpos;

			//LOCKS COL BOX ONTO MAIN CHAR//
			lvl_1->col->xpos = lvl_1->mainChar->characterSprite->xpos + 80;
			lvl_1->col->ypos = lvl_1->mainChar->characterSprite->ypos + 80;

			lvl_1->health->xpos = lvl_1->mainChar->characterSprite->xpos;
			lvl_1->health->ypos = lvl_1->mainChar->characterSprite->ypos;




		//LOCKS COL 1 BOX ONTO BOSS//
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_1->destroyed != true)
			{
				lvl_1->bossCol_1->xpos = lvl_1->boss->enemySprite->xpos + 210;
				lvl_1->bossCol_1->ypos = lvl_1->boss->enemySprite->ypos + 120;
			}
		}

		//LOCKS COL 2 BOX ONTO BOSS//
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_2->destroyed != true)
			{
				lvl_1->bossCol_2->xpos = lvl_1->boss->enemySprite->xpos + 210;
				lvl_1->bossCol_2->ypos = lvl_1->boss->enemySprite->ypos + 300;
			}
		}

		//LOCKS COL 3 BOX ONTO BOSS//
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_3->destroyed != true)
			{
				lvl_1->bossCol_3->xpos = lvl_1->boss->enemySprite->xpos + 120;
				lvl_1->bossCol_3->ypos = lvl_1->boss->enemySprite->ypos + 210;
			}
		}

		//LOCKS COL 4 BOX ONTO BOSS/
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_4->destroyed != true)
			{
				lvl_1->bossCol_4->xpos = lvl_1->boss->enemySprite->xpos + 300;
				lvl_1->bossCol_4->ypos = lvl_1->boss->enemySprite->ypos + 210;
			}
		}

		//LOCKS COL 5 BOX ONTO BOSS/
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_5->destroyed != true)
			{
				lvl_1->bossCol_5->xpos = lvl_1->boss->enemySprite->xpos + 280;
				lvl_1->bossCol_5->ypos = lvl_1->boss->enemySprite->ypos + 100;
			}
		}

		//LOCKS COL 6 BOX ONTO BOSS/
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_6->destroyed != true)
			{
				lvl_1->bossCol_6->xpos = lvl_1->boss->enemySprite->xpos + 280;
				lvl_1->bossCol_6->ypos = lvl_1->boss->enemySprite->ypos + 280;
			}
		}

		//LOCKS COL 7 BOX ONTO BOSS/
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_7->destroyed != true)
			{
				lvl_1->bossCol_7->xpos = lvl_1->boss->enemySprite->xpos + 100;
				lvl_1->bossCol_7->ypos = lvl_1->boss->enemySprite->ypos + 100;
			}
		}

		//LOCKS COL 8 BOX ONTO BOSS/
		if(lvl_1->boss->dead != true)
		{
			if(lvl_1->bossCol_8->destroyed != true)
			{
				lvl_1->bossCol_8->xpos = lvl_1->boss->enemySprite->xpos + 100;
				lvl_1->bossCol_8->ypos = lvl_1->boss->enemySprite->ypos + 280;
			}
		}

	

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy1->dead != true)
			{
				if(lvl_1->enemyCol->destroyed != true)
				{
					lvl_1->enemyCol->xpos = lvl_1->enemy1->enemySprite->xpos + 80;
					lvl_1->enemyCol->ypos = lvl_1->enemy1->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy2->dead != true)
			{
				if(lvl_1->enemyCol_2->destroyed != true)
				{
					lvl_1->enemyCol_2->xpos = lvl_1->enemy2->enemySprite->xpos + 80;
					lvl_1->enemyCol_2->ypos = lvl_1->enemy2->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy3->dead != true)
			{
				if(lvl_1->enemyCol_3->destroyed != true)
				{
					lvl_1->enemyCol_3->xpos = lvl_1->enemy3->enemySprite->xpos + 80;
					lvl_1->enemyCol_3->ypos = lvl_1->enemy3->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy4->dead != true)
			{
				if(lvl_1->enemyCol_4->destroyed != true)
				{
					lvl_1->enemyCol_4->xpos = lvl_1->enemy4->enemySprite->xpos + 80;
					lvl_1->enemyCol_4->ypos = lvl_1->enemy4->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy5->dead != true)
			{
				if(lvl_1->enemyCol_5->destroyed != true)
				{
					lvl_1->enemyCol_5->xpos = lvl_1->enemy5->enemySprite->xpos + 80;
					lvl_1->enemyCol_5->ypos = lvl_1->enemy5->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy6->dead != true)
			{
				if(lvl_1->enemyCol_6->destroyed != true)
				{
					lvl_1->enemyCol_6->xpos = lvl_1->enemy6->enemySprite->xpos + 80;
					lvl_1->enemyCol_6->ypos = lvl_1->enemy6->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy7->dead != true)
			{
				if(lvl_1->enemyCol_7->destroyed != true)
				{
					lvl_1->enemyCol_7->xpos = lvl_1->enemy7->enemySprite->xpos + 80;
					lvl_1->enemyCol_7->ypos = lvl_1->enemy7->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy8->dead != true)
			{
				if(lvl_1->enemyCol_8->destroyed != true)
				{
					lvl_1->enemyCol_8->xpos = lvl_1->enemy8->enemySprite->xpos + 80;
					lvl_1->enemyCol_8->ypos = lvl_1->enemy8->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy9->dead != true)
			{
				if(lvl_1->enemyCol_9->destroyed != true)
				{
					lvl_1->enemyCol_9->xpos = lvl_1->enemy9->enemySprite->xpos + 80;
					lvl_1->enemyCol_9->ypos = lvl_1->enemy9->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy10->dead != true)
			{
				if(lvl_1->enemyCol_10->destroyed != true)
				{
					lvl_1->enemyCol_10->xpos = lvl_1->enemy10->enemySprite->xpos + 80;
					lvl_1->enemyCol_10->ypos = lvl_1->enemy10->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy11->dead != true)
			{
				if(lvl_1->enemyCol_11->destroyed != true)
				{
					lvl_1->enemyCol_11->xpos = lvl_1->enemy11->enemySprite->xpos + 80;
					lvl_1->enemyCol_11->ypos = lvl_1->enemy11->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE ENEMY IS DEAD & IF COLLISON IS DESTROYED//
			if (lvl_1->enemy12->dead != true)
			{
				if(lvl_1->enemyCol_12->destroyed != true)
				{
					lvl_1->enemyCol_12->xpos = lvl_1->enemy12->enemySprite->xpos + 80;
					lvl_1->enemyCol_12->ypos = lvl_1->enemy12->enemySprite->ypos + 80;
				}
			}

			//CHECKS IF THE FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_1->dead != true)
			{
				if(lvl_1->foodCol_1->destroyed != true)
				{
					lvl_1->foodCol_1->xpos = lvl_1->food_1->foodSprite->xpos + 40;
					lvl_1->foodCol_1->ypos = lvl_1->food_1->foodSprite->ypos + 40;
				}
			}
			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_2->dead != true)
			{
				if(lvl_1->foodCol_2->destroyed != true)
				{
					lvl_1->foodCol_2->xpos = lvl_1->food_2->foodSprite->xpos + 40;
					lvl_1->foodCol_2->ypos = lvl_1->food_2->foodSprite->ypos + 40;
				}
			}
			
			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_3->dead != true)
			{
				if(lvl_1->foodCol_3->destroyed != true)
				{
					lvl_1->foodCol_3->xpos = lvl_1->food_3->foodSprite->xpos + 40;
					lvl_1->foodCol_3->ypos = lvl_1->food_3->foodSprite->ypos + 40;
				}
			}
			
			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_4->dead != true)
			{
				if(lvl_1->foodCol_4->destroyed != true)
				{
					lvl_1->foodCol_4->xpos = lvl_1->food_4->foodSprite->xpos + 40;
					lvl_1->foodCol_4->ypos = lvl_1->food_4->foodSprite->ypos + 40;
				}
			}
			
			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_5->dead != true)
			{
				if(lvl_1->foodCol_5->destroyed != true)
				{
					lvl_1->foodCol_5->xpos = lvl_1->food_5->foodSprite->xpos + 40;
					lvl_1->foodCol_5->ypos = lvl_1->food_5->foodSprite->ypos + 40;
				}
			}
			
			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_6->dead != true)
			{
				if(lvl_1->foodCol_6->destroyed != true)
				{
					lvl_1->foodCol_6->xpos = lvl_1->food_6->foodSprite->xpos + 40;
					lvl_1->foodCol_6->ypos = lvl_1->food_6->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_7->dead != true)
			{
				if(lvl_1->foodCol_7->destroyed != true)
				{
					lvl_1->foodCol_7->xpos = lvl_1->food_7->foodSprite->xpos + 40;
					lvl_1->foodCol_7->ypos = lvl_1->food_7->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_8->dead != true)
			{
				if(lvl_1->foodCol_8->destroyed != true)
				{
					lvl_1->foodCol_8->xpos = lvl_1->food_8->foodSprite->xpos + 40;
					lvl_1->foodCol_8->ypos = lvl_1->food_8->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_9->dead != true)
			{
				if(lvl_1->foodCol_9->destroyed != true)
				{
					lvl_1->foodCol_9->xpos = lvl_1->food_9->foodSprite->xpos + 40;
					lvl_1->foodCol_9->ypos = lvl_1->food_9->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_10->dead != true)
			{
				if(lvl_1->foodCol_10->destroyed != true)
				{
					lvl_1->foodCol_10->xpos = lvl_1->food_10->foodSprite->xpos + 40;
					lvl_1->foodCol_10->ypos = lvl_1->food_10->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_11->dead != true)
			{
				if(lvl_1->foodCol_11->destroyed != true)
				{
					lvl_1->foodCol_11->xpos = lvl_1->food_11->foodSprite->xpos + 40;
					lvl_1->foodCol_11->ypos = lvl_1->food_11->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_12->dead != true)
			{
				if(lvl_1->foodCol_12->destroyed != true)
				{
					lvl_1->foodCol_12->xpos = lvl_1->food_12->foodSprite->xpos + 40;
					lvl_1->foodCol_12->ypos = lvl_1->food_12->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_13->dead != true)
			{
				if(lvl_1->foodCol_13->destroyed != true)
				{
					lvl_1->foodCol_13->xpos = lvl_1->food_13->foodSprite->xpos + 40;
					lvl_1->foodCol_13->ypos = lvl_1->food_13->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_14->dead != true)
			{
				if(lvl_1->foodCol_14->destroyed != true)
				{
					lvl_1->foodCol_14->xpos = lvl_1->food_14->foodSprite->xpos + 40;
					lvl_1->foodCol_14->ypos = lvl_1->food_14->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_15->dead != true)
			{
				if(lvl_1->foodCol_15->destroyed != true)
				{
					lvl_1->foodCol_15->xpos = lvl_1->food_15->foodSprite->xpos + 40;
					lvl_1->foodCol_15->ypos = lvl_1->food_15->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_16->dead != true)
			{
				if(lvl_1->foodCol_16->destroyed != true)
				{
					lvl_1->foodCol_16->xpos = lvl_1->food_16->foodSprite->xpos + 40;
					lvl_1->foodCol_16->ypos = lvl_1->food_16->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_17->dead != true)
			{
				if(lvl_1->foodCol_17->destroyed != true)
				{
					lvl_1->foodCol_17->xpos = lvl_1->food_17->foodSprite->xpos + 40;
					lvl_1->foodCol_17->ypos = lvl_1->food_17->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_18->dead != true)
			{
				if(lvl_1->foodCol_18->destroyed != true)
				{
					lvl_1->foodCol_18->xpos = lvl_1->food_18->foodSprite->xpos + 40;
					lvl_1->foodCol_18->ypos = lvl_1->food_18->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_19->dead != true)
			{
				if(lvl_1->foodCol_19->destroyed != true)
				{
					lvl_1->foodCol_19->xpos = lvl_1->food_19->foodSprite->xpos + 40;
					lvl_1->foodCol_19->ypos = lvl_1->food_19->foodSprite->ypos + 40;
				}
			}

			//CHECKS IF FOOD IS DEAD & IF COLLISION IS DESTROYED//
			if(lvl_1->food_20->dead != true)
			{
				if(lvl_1->foodCol_20->destroyed != true)
				{
					lvl_1->foodCol_20->xpos = lvl_1->food_20->foodSprite->xpos + 40;
					lvl_1->foodCol_20->ypos = lvl_1->food_20->foodSprite->ypos + 40;
				}
			}

			

	

	fps->pause();
	//animates the sprites//
	//CHECKS IF FOOD 1 IS DEAD//
	if(lvl_1->food_1->dead != true)	
	{
		lvl_1->food_1->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 2 IS DEAD//
	if(lvl_1->food_2->dead != true)
	{
		lvl_1->food_2->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 3 IS DEAD//
	if(lvl_1->food_3->dead != true)
	{
		lvl_1->food_3->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 4 IS DEAD//
	if(lvl_1->food_4->dead != true)
	{
		lvl_1->food_4->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 5 IS DEAD//
	if(lvl_1->food_5->dead != true)
	{
		lvl_1->food_5->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 6 IS DEAD//
	if(lvl_1->food_6->dead != true)
	{
		lvl_1->food_6->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 7 IS DEAD//
	if(lvl_1->food_7->dead != true)
	{
		lvl_1->food_7->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 8 IS DEAD//
	if(lvl_1->food_8->dead != true)
	{
		lvl_1->food_8->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 9 IS DEAD//
	if(lvl_1->food_9->dead != true)
	{
		lvl_1->food_9->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 10 IS DEAD//
	if(lvl_1->food_10->dead != true)
	{
		lvl_1->food_10->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 11 IS DEAD//
	if(lvl_1->food_11->dead != true)
	{
		lvl_1->food_11->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 12 IS DEAD//
	if(lvl_1->food_12->dead != true)
	{
		lvl_1->food_12->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 13 IS DEAD//
	if(lvl_1->food_13->dead != true)
	{
		lvl_1->food_13->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 14 IS DEAD//
	if(lvl_1->food_14->dead != true)
	{
		lvl_1->food_14->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 15 IS DEAD//
	if(lvl_1->food_15->dead != true)
	{
		lvl_1->food_15->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 16 IS DEAD//
	if(lvl_1->food_16->dead != true)
	{
		lvl_1->food_16->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 17 IS DEAD//
	if(lvl_1->food_17->dead != true)
	{
		lvl_1->food_17->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 18 IS DEAD//
	if(lvl_1->food_18->dead != true)
	{
		lvl_1->food_18->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 19 IS DEAD//
	if(lvl_1->food_19->dead != true)
	{
		lvl_1->food_19->foodSprite->Animate(0,3);
	}
	//CHECKS IF FOOD 20 IS DEAD//
	if(lvl_1->food_20->dead != true)
	{
		lvl_1->food_20->foodSprite->Animate(0,3);
	}

	
	
	

	//Animates the enemies if they are not dead//
	//CHECKS IF ENEMY 1 IS DEAD//
		if (lvl_1->enemy1->dead != true)
		{
			if(lvl_1->enemy1->hit != true)
			{
				lvl_1->enemy1->enemySprite->Animate(0,3);
			}
			else if(lvl_1->enemy1->hit == true)
			{
				lvl_1->hit->Draw_Sprite(screen);
				lvl_1->hit->Animate(0,20);
				lvl_1->enemy1->hit = false;
			}
		}
	
	
		

	
	//CHECKS IF ENEMY 2 IS DEAD//
	if (lvl_1->enemy2->dead != true)
	{
		lvl_1->enemy2->enemySprite->Animate(0,3);
	}
	
	//CHECKS IF ENEMY 3 IS DEAD//
	if (lvl_1->enemy3->dead != true)
	{
		lvl_1->enemy3->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 4 IS DEAD//
	if (lvl_1->enemy4->dead != true)
	{
		lvl_1->enemy4->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 5 IS DEAD//
	if (lvl_1->enemy5->dead != true)
	{
		lvl_1->enemy5->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 6 IS DEAD//
	if (lvl_1->enemy6->dead != true)
	{
		lvl_1->enemy6->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 7 IS DEAD//
	if (lvl_1->enemy7->dead != true)
	{
		lvl_1->enemy7->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 8 IS DEAD//
	if (lvl_1->enemy8->dead != true)
	{
		lvl_1->enemy8->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 9 IS DEAD//
	if (lvl_1->enemy9->dead != true)
	{
		lvl_1->enemy9->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 10 IS DEAD//
	if (lvl_1->enemy10->dead != true)
	{
		lvl_1->enemy10->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 11 IS DEAD//
	if (lvl_1->enemy11->dead != true)
	{
		lvl_1->enemy11->enemySprite->Animate(0,3);
	}
	//CHECKS IF ENEMY 1 IS DEAD//
	if (lvl_1->enemy12->dead != true)
	{
		lvl_1->enemy12->enemySprite->Animate(0,3);
	}




	

	//CHECKS IF THE BOSS IS DEAD//
	if (lvl_1->boss->dead != true)
	{
		if(lvl_1->boss->hit != true)
		{
			lvl_1->boss->enemySprite->Animate(0,14);
			lvl_1->boss->hit = false;
		}
		else if(lvl_1->boss->hit == true)
		{
			lvl_1->boss->enemySprite->Animate(0,7);
		}
	}




	
	//UPDATES THE SCREEN//
	lvl_1->Update(screen);

	


	//UPDATES THE BOSS SPRITE//
	if(lvl_1->boss->dead != true)
	{
		lvl_1->boss->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->boss->dead == true)
	{
		
		lvl_1->done = true;
	}





	//UPDATES THE FIRST FOOD SPRITES FOR DEATH//
	if(lvl_1->food_1->dead != true)
	{
		lvl_1->food_1->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_1->dead == true)
	{
		
	}

	//UPDATES THE SECOND FOOD FOR DEATH//
	if(lvl_1->food_2->dead != true)
	{
		lvl_1->food_2->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_2->dead == true)
	{
		
	}
	//UPDATES THE 3 FOOD FOR DEATH//
	if(lvl_1->food_3->dead != true)
	{
		lvl_1->food_3->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_3->dead == true)
	{
		
	}
	//UPDATES THE 4 FOOD FOR DEATH//
	if(lvl_1->food_4->dead != true)
	{
		lvl_1->food_4->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_4->dead == true)
	{
		
	}
	//UPDATES THE 5 FOOD FOR DEATH//
	if(lvl_1->food_5->dead != true)
	{
		lvl_1->food_5->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_5->dead == true)
	{
		
	}
	//UPDATES THE 6 FOOD FOR DEATH//
	if(lvl_1->food_6->dead != true)
	{
		lvl_1->food_6->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_6->dead == true)
	{
		
	}
	//UPDATES THE 7 FOOD FOR DEATH//
	if(lvl_1->food_7->dead != true)
	{
		lvl_1->food_7->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_7->dead == true)
	{
		
	}
	//UPDATES THE 8 FOOD FOR DEATH//
	if(lvl_1->food_8->dead != true)
	{
		lvl_1->food_8->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_8->dead == true)
	{
		
	}
	//UPDATES THE 9 FOOD FOR DEATH//
	if(lvl_1->food_9->dead != true)
	{
		lvl_1->food_9->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_9->dead == true)
	{
		
	}
	//UPDATES THE 10 FOOD FOR DEATH//
	if(lvl_1->food_10->dead != true)
	{
		lvl_1->food_10->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_10->dead == true)
	{
		
	}
	//UPDATES THE 11 FOOD FOR DEATH//
	if(lvl_1->food_11->dead != true)
	{
		lvl_1->food_11->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_11->dead == true)
	{
		
	}
	//UPDATES THE 12 FOOD FOR DEATH//
	if(lvl_1->food_12->dead != true)
	{
		lvl_1->food_12->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_12->dead == true)
	{
		
	}
	//UPDATES THE 10 FOOD FOR DEATH//
	if(lvl_1->food_13->dead != true)
	{
		lvl_1->food_13->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_13->dead == true)
	{
		
	}
	//UPDATES THE 14 FOOD FOR DEATH//
	if(lvl_1->food_14->dead != true)
	{
		lvl_1->food_14->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_14->dead == true)
	{
		
	}
	//UPDATES THE 15 FOOD FOR DEATH//
	if(lvl_1->food_15->dead != true)
	{
		lvl_1->food_15->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_15->dead == true)
	{
		
	}
	//UPDATES THE 16 FOOD FOR DEATH//
	if(lvl_1->food_16->dead != true)
	{
		lvl_1->food_16->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_16->dead == true)
	{
		
	}
	//UPDATES THE 17 FOOD FOR DEATH//
	if(lvl_1->food_17->dead != true)
	{
		lvl_1->food_17->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_17->dead == true)
	{
		
	}
	//UPDATES THE 18 FOOD FOR DEATH//
	if(lvl_1->food_18->dead != true)
	{
		lvl_1->food_18->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_18->dead == true)
	{
		
	}
	//UPDATES THE 19 FOOD FOR DEATH//
	if(lvl_1->food_19->dead != true)
	{
		lvl_1->food_19->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_19->dead == true)
	{
		
	}
	//UPDATES THE 20 FOOD FOR DEATH//
	if(lvl_1->food_20->dead != true)
	{
		lvl_1->food_20->foodSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->food_20->dead == true)
	{
		
	}


	
	//UPDATES THE FIRST ENEMY FOR DEATH//
	if(lvl_1->enemy1->dead != true)
	{
		lvl_1->enemy1->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy1->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR WHEN THE ENEMYS DIE//
		if(lvl_1->death->getCurrentFrame() != 7)
		{
			lvl_1->death->Draw_Sprite(screen);
			lvl_1->death->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 2 ENEMY FOR DEATH//
	if(lvl_1->enemy2->dead != true)
	{
		lvl_1->enemy2->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy2->dead == true)
	{
		
		if(lvl_1->death_2->getCurrentFrame() != 7)
		{
			lvl_1->death_2->Draw_Sprite(screen);
			lvl_1->death_2->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_2->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 3 ENEMY FOR DEATH//
	if(lvl_1->enemy3->dead != true)
	{
		lvl_1->enemy3->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy3->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_3->getCurrentFrame() != 7)
		{
			lvl_1->death_3->Draw_Sprite(screen);
			lvl_1->death_3->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_3->getCurrentFrame() == 7)
		{
			
		}
	}
	//UPDATES THE 4 ENEMY FOR DEATH//
	if(lvl_1->enemy4->dead != true)
	{
		lvl_1->enemy4->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy4->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_4->getCurrentFrame() != 7)
		{
			lvl_1->death_4->Draw_Sprite(screen);
			lvl_1->death_4->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_4->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 5 ENEMY FOR DEATH//
	if(lvl_1->enemy5->dead != true)
	{
		lvl_1->enemy5->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy5->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_5->getCurrentFrame() != 7)
		{
			lvl_1->death_5->Draw_Sprite(screen);
			lvl_1->death_5->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_5->getCurrentFrame() == 7)
		{
			
		}
	}
	//UPDATES THE 6 ENEMY FOR DEATH//
	if(lvl_1->enemy6->dead != true)
	{
		lvl_1->enemy6->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy6->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_6->getCurrentFrame() != 7)
		{
			lvl_1->death_6->Draw_Sprite(screen);
			lvl_1->death_6->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_6->getCurrentFrame() == 7)
		{
			
		}
	}
	//UPDATES THE 7 ENEMY FOR DEATH//
	if(lvl_1->enemy7->dead != true)
	{
		lvl_1->enemy7->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy7->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_7->getCurrentFrame() != 7)
		{
			lvl_1->death_7->Draw_Sprite(screen);
			lvl_1->death_7->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_7->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 8 ENEMY FOR DEATH//
	if(lvl_1->enemy8->dead != true)
	{
		lvl_1->enemy8->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy8->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_8->getCurrentFrame() != 7)
		{
			lvl_1->death_8->Draw_Sprite(screen);
			lvl_1->death_8->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_8->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 9 ENEMY FOR DEATH//
	if(lvl_1->enemy9->dead != true)
	{
		lvl_1->enemy9->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy9->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_9->getCurrentFrame() != 7)
		{
			lvl_1->death_9->Draw_Sprite(screen);
			lvl_1->death_9->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_9->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 10 ENEMY FOR DEATH//
	if(lvl_1->enemy10->dead != true)
	{
		lvl_1->enemy10->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy10->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_10->getCurrentFrame() != 7)
		{
			lvl_1->death_10->Draw_Sprite(screen);
			lvl_1->death_10->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_10->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 11 ENEMY FOR DEATH//
	if(lvl_1->enemy11->dead != true)
	{
		lvl_1->enemy11->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy11->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_11->getCurrentFrame() != 7)
		{
			lvl_1->death_11->Draw_Sprite(screen);
			lvl_1->death_11->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_11->getCurrentFrame() == 7)
		{
				
		}
	}
	//UPDATES THE 12 ENEMY FOR DEATH//
	if(lvl_1->enemy12->dead != true)
	{
		lvl_1->enemy12->enemySprite->Draw_Sprite(screen);
	}
	else if(lvl_1->enemy12->dead == true)
	{
		
		//DOES A SMALL ANIMATION FOR DEATH//
		if(lvl_1->death_12->getCurrentFrame() != 7)
		{
			lvl_1->death_12->Draw_Sprite(screen);
			lvl_1->death_12->Animate(0,7);
			Mix_PlayChannel(2,enemyDeath,0);
		}
		else if(lvl_1->death_12->getCurrentFrame() == 7)
		{
				
		}
	}

	
	//UPDATES THE MAIN CHAR//
	if(lvl_1->mainChar->dead != true)
	{
		lvl_1->mainChar->characterSprite->Draw_Sprite(screen);
	}
	else if(lvl_1->mainChar->dead == true)
	{
		
	}
	lvl_1->health->Draw_Sprite(screen);


	//UPDATES THE AI//
	//Enemy 1//
	if(lvl_1->enemy1->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy1->enemySprite);
	}
	else if(lvl_1->enemy1->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy1->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 2//
	if(lvl_1->enemy2->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy2->enemySprite);
	}
	else if(lvl_1->enemy2->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy2->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 3//
	if(lvl_1->enemy3->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy3->enemySprite);
	}
	else if(lvl_1->enemy3->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy3->enemySprite);
	}

	//UPDATES THE AI//
	//Enemy 4//
	if(lvl_1->enemy4->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy4->enemySprite);
	}
	else if(lvl_1->enemy4->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy4->enemySprite);
	}

	//UPDATES THE AI//
	//Enemy 5//
	if(lvl_1->enemy5->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy5->enemySprite);
	}
	else if(lvl_1->enemy5->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy5->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 6//
	if(lvl_1->enemy6->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy6->enemySprite);
	}
	else if(lvl_1->enemy6->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy6->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 7//
	if(lvl_1->enemy7->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy7->enemySprite);
	}
	else if(lvl_1->enemy7->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy7->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 8//
	if(lvl_1->enemy8->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy8->enemySprite);
	}
	else if(lvl_1->enemy8->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy8->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 9//
	if(lvl_1->enemy9->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy9->enemySprite);
	}
	else if(lvl_1->enemy9->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy9->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 10//
	if(lvl_1->enemy10->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy10->enemySprite);
	}
	else if(lvl_1->enemy10->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy10->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 11//
	if(lvl_1->enemy11->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy11->enemySprite);
	}
	else if(lvl_1->enemy11->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy11->enemySprite);
	}
	//UPDATES THE AI//
	//Enemy 12//
	if(lvl_1->enemy12->enemyHealth > 50)
	{
		checkAngle(lvl_1->mainChar->characterSprite,lvl_1->enemy12->enemySprite);
	}
	else if(lvl_1->enemy12->enemyHealth < 50)
	{
		patrol(lvl_1->mainChar->characterSprite,lvl_1->enemy12->enemySprite);
	}

	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_1->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_2->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_3->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_4->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_5->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_6->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_7->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_8->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_9->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_10->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_11->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_12->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_13->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_14->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_15->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_16->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_17->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_18->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_19->foodSprite);
	foodRun(lvl_1->mainChar->characterSprite,lvl_1->food_20->foodSprite);

	bossChase(lvl_1->mainChar->characterSprite,lvl_1->boss->enemySprite);

	//UPDATES THE MAIN CHAR HEALTH//
	lvl_1->mainChar->healthUpdate(lvl_1->health,lvl_1->mainChar);

}//END CONTROL LOOP//


void lvl_1_control::checkAngle(Sprite *sprite, Sprite *sprite2)
{

		angleVel = 5;
	

		spriteXpos = sprite->xpos;
		spriteYpos = sprite->ypos;

		enemyXpos = sprite2->xpos;
		enemyYpos = sprite2->ypos;

		xVel2 = spriteXpos - enemyXpos; 
		yVel2 = spriteYpos - enemyYpos;

		dist2 = sqrt(pow(xVel2,2) + pow(yVel2,2));

		xVel2 = floor(xVel2/dist2 * 13 + 0.5) * 0.98;
		yVel2 = floor(yVel2/dist2 * 13 + 0.5) * 0.98;

		angle2 = atan2(xVel2, yVel2) * 180 / 3.14159 - 90;
		angle2 = angle2 < 0 ? angle2 + 360 : angle2 ;

		
		
			
			//UPER LEFTHAND CORNER//
			if(angle2 >= 112.5 && angle2 < 157.5)
			{
				sprite2->rect.y = 1680;	
			}

			//THE UPWARD DIRECTION//
			else if(angle2 >= 67.5 && angle2 < 112.5)
			{
				sprite2->rect.y = 0;
			}
			//UPER RIGHTHAND CORNER//
			else if(angle2 >= 22.5 && angle2 < 67.5)
			{
				sprite2->rect.y = 240;
			}
			//LEFT SIDE//
			else if(angle2 >= 157.5 && angle2 < 202.5)
			{
				sprite2->rect.y = 1440;
			}
			//LOWER LEFTHAND CORNER//
			else if(angle2 >= 202.5 && angle2 < 247.5)
			{
				sprite2->rect.y = 1200;
			}
			//BOTTOM//
			else if(angle2 >= 247.5 && angle2 < 292.5)
			{
				sprite2->rect.y = 960;
			}
			//BOTTOM RIGHT HAND CORNER//
			else if(angle2 >= 292.5 && angle2 < 337.5)
			{
				sprite2->rect.y = 720;
			}
			//RIGHT//
			else
			{
				sprite2->rect.y = 480;
			}
		
		
			if(sprite2->xpos - sprite->xpos < 500 && sprite2->ypos - sprite->ypos < 500)
			{
				sprite2->move(xVel2,yVel2);
			}
		
			
		

}

void lvl_1_control::patrol(Sprite *sprite, Sprite *sprite3)
{
		spriteXpos = sprite->xpos;
		spriteYpos = sprite->ypos;

		enemyXpos = sprite3->xpos;
		enemyYpos = sprite3->ypos;

		xVel3 = spriteXpos - enemyXpos; 
		yVel3 = spriteYpos - enemyYpos;

		dist3 = sqrt(pow(xVel3,2) + pow(yVel3,2));

		xVel3 = floor(xVel3/dist3 * 10 + 0.5) * 0.98;
		yVel3 = floor(yVel3/dist3 * 10 + 0.5) * 0.98;

		angle3 = atan2(xVel3, yVel3) * 180 / 3.14159 - 90;
		angle3 = angle3 < 0 ? angle3 + 360 : angle3 ;

		

		//UPER LEFTHAND CORNER//
			if(angle3 >= 112.5 && angle3 < 157.5)
			{
				sprite3->rect.y = 720;
			}

			//THE UPWARD DIRECTION//
			else if(angle3 >= 67.5 && angle3 < 112.5)
			{
				sprite3->rect.y = 960;
			}
			//UPER RIGHTHAND CORNER//
			else if(angle3 >= 22.5 && angle3 < 67.5)
			{
				sprite3->rect.y = 1200;
			}
			//LEFT SIDE//
			else if(angle3 >= 157.5 && angle3 < 202.5)
			{
				sprite3->rect.y = 480;
			}
			//LOWER LEFTHAND CORNER//
			else if(angle3 >= 202.5 && angle3 < 247.5)
			{
				sprite3->rect.y = 240;
			}
			//BOTTOM//
			else if(angle3 >= 247.5 && angle3 < 292.5)
			{
				sprite3->rect.y = 0;	
			}
			//BOTTOM RIGHT HAND CORNER//
			else if(angle3 >= 292.5 && angle3 < 337.5)
			{
				sprite3->rect.y = 1680;
			}
			//RIGHT//
			else
			{
				sprite3->rect.y = 1440;
			}



		
			
			sprite3->move(-xVel3,-yVel3);
			
		
			


		
}

void lvl_1_control::bossChase(Sprite *sprite, Sprite *sprite2)
{

		spriteXpos = sprite->xpos;
		spriteYpos = sprite->ypos;

		enemyXpos = sprite2->xpos;
		enemyYpos = sprite2->ypos;

		xVel2 = spriteXpos - enemyXpos; 
		yVel2 = spriteYpos - enemyYpos;

		dist2 = sqrt(pow(xVel2,2) + pow(yVel2,2));

		xVel2 = floor(xVel2/dist2 * 8 + 0.5) * 0.98;
		yVel2 = floor(yVel2/dist2 * 8 + 0.5) * 0.98;

		angle2 = atan2(xVel2, yVel2) * 180 / 3.14159 - 90;
		angle2 = angle2 < 0 ? angle2 + 360 : angle2 ;

		
		
		
			if(sprite2->xpos - sprite->xpos < 500 && sprite2->ypos - sprite->ypos < 500)
			{
				sprite2->move(xVel2,yVel2);
			}


}


void lvl_1_control::foodRun(Sprite *sprite, Sprite *sprite3)
{
		spriteXpos = sprite->xpos;
		spriteYpos = sprite->ypos;

		enemyXpos = sprite3->xpos;
		enemyYpos = sprite3->ypos;

		xVel3 = spriteXpos - enemyXpos; 
		yVel3 = spriteYpos - enemyYpos;

		dist3 = sqrt(pow(xVel3,2) + pow(yVel3,2));

		xVel3 = floor(xVel3/dist3 * 3 + 0.5) * 0.98;
		yVel3 = floor(yVel3/dist3 * 3 + 0.5) * 0.98;

		angle3 = atan2(xVel3, yVel3) * 180 / 3.14159 - 90;
		angle3 = angle3 < 0 ? angle3 + 360 : angle3 ;

		

		//UPER LEFTHAND CORNER//
			if(angle3 >= 112.5 && angle3 < 157.5)
			{
				sprite3->rect.y = 100;
			}

			//THE UPWARD DIRECTION//
			else if(angle3 >= 67.5 && angle3 < 112.5)
			{
				sprite3->rect.y = 300;
			}
			//UPER RIGHTHAND CORNER//
			else if(angle3 >= 22.5 && angle3 < 67.5)
			{
				sprite3->rect.y = 400;
			}
			//LEFT SIDE//
			else if(angle3 >= 157.5 && angle3 < 202.5)
			{
				sprite3->rect.y = 0;
			}
			//LOWER LEFTHAND CORNER//
			else if(angle3 >= 202.5 && angle3 < 247.5)
			{
				sprite3->rect.y = 600;
			}
			//BOTTOM//
			else if(angle3 >= 247.5 && angle3 < 292.5)
			{
				sprite3->rect.y = 700;	
			}
			//BOTTOM RIGHT HAND CORNER//
			else if(angle3 >= 292.5 && angle3 < 337.5)
			{
				sprite3->rect.y = 500;
			}
			//RIGHT//
			else
			{
				sprite3->rect.y = 400;
			}

			if(sprite->xpos - sprite3->xpos < 20 && sprite->ypos - sprite3->ypos < 20 || sprite3->xpos - sprite->xpos < 20 && sprite3->ypos - sprite->ypos < 20)
			{
				
			}
					
}



#endif