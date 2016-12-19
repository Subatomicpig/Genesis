#ifndef ATTACKS_H
#define ATTACKS_H

#include "SDL.h"
#include "Sprite.h"
#include "SDL_Mixer.h"
#include "SDL_image.h"


class Attacks
{
public:

	Sprite *sonarDrop;
	Sprite *electricDrop;
	Sprite *bubbleDrop;
	Sprite *shieldDrop;

	Sprite *sonar;
	Sprite *electric;
	Sprite *bubble;
	Sprite *shield;

	Sprite *barG;
	Sprite *bar;

	Mix_Chunk *pickup;
	Mix_Chunk *bubbleSound;
	Mix_Chunk *sonarSound;
	Mix_Chunk *shieldSound;
	Mix_Chunk *electricSound;

	bool pickedUp;
	
	Attacks();
	~Attacks();
	void useAttack(int type, int direction,SDL_Surface *screeneen,int px, int py);
	void update(SDL_Surface *screeneen);
	
};

Attacks::Attacks()
{


	bubble = new Sprite("bubbleATCK.png",0,0,260,260,0,0);
	shield = new Sprite("shield.png",0,0,214,214,0,0);

	
	pickedUp = false;
}

void Attacks::useAttack(int type, int direction,SDL_Surface *screeneen, int px, int py)
{
	
	if ( type == 1); //Sonar
	if ( type == 2); //Electric
	if ( type == 3)//Bubble
	{
		if (direction == 1)
		{
			bubble->rect.y = 260;
			bubble->Animate(0,7);
		}
	
		else if (direction == 2)
		{
			bubble->rect.y = 0;
			bubble->Animate(0,7);
		}

		else if (direction == 3)
		{
			bubble->rect.y = 1820;
			bubble->Animate(0,7);
		}
		else if (direction == 4)
		{
			bubble->rect.y = 1560;
			bubble->Animate(0,7);
		}
		else if (direction == 5)
		{
			bubble->rect.y = 1300;
			bubble->Animate(0,7);
		}
		else if (direction == 6)
		{
			bubble->rect.y = 1040;
			bubble->Animate(0,7);
		}
		else if (direction == 7)
		{
			bubble->rect.y = 780;
			bubble->Animate(0,7);
		}
		else 
		{
			bubble->rect.y = 520;
			bubble->Animate(0,7);
		}
	}
	if ( type == 4) //Shield
	{
		
	}
}

void Attacks::update(SDL_Surface *screeneen)
{
	
}

Attacks::~Attacks()
{
}
#endif