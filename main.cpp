#include "Sprite.h"
#include "timer.h"
#include "lvl_1_enemy.h"
#include "lvl_1_list.h"
#include "lvl_1_character.h"
#include "lvl_1_food.h"
#include "lvl_1_control.h"
#include "lvl_2_control.h"
#include "lvl_2_list.h"
#include "lvl_3_character.h"
#include "lvl_3_enemy.h"
#include "lvl_3_food.h"
#include "lvl_3_list.h"
#include "foundation.h"


#include "SDL_Collide.h"
#include "SDL.h"
#include "sdl_mixer.h"
#include "SDL_image.h"

#include <vector>
#include <cmath>
#include <stdio.h> 
#include <sstream>
#include <string>
#include <iostream>

using namespace std;



int main(int argc, char* args[])
{

	SDL_Event *event;
	SDL_Surface *screen;
	SDL_Init(SDL_INIT_EVERYTHING);
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 2048;
	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) 
	{
		fprintf(stderr, "Unable to open audio!\n", Mix_GetError());
	}
	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(800,600,32,SDL_DOUBLEBUF|SDL_SWSURFACE);


	SDL_WM_SetCaption( "GENESIS", NULL );

	Foundation app;
	
			while (app.game_state != 4) // 4 is equal to quit in the enum
			{
				app.god_loop(screen);	
			}


		


	

	
	
	
	return 0;
}

















