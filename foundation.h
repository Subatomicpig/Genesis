#ifndef FOUNDATION_H
#define FOUNDATION_H
#include "SDL.h"
#include "SDL_mixer.h"
#include "Sprite.h"

#include "lvl_2_control.h"
#include "lvl_1_control.h"
#include "lvl_3_control.h"
#include <cmath>





class Foundation
{
	
private:
	
	Sprite *menu;
	Sprite *background;
	Sprite *pauseImage;
	Sprite *gameOver;
	Sprite *loading;
	Sprite *tutorial;
	Sprite *level2_Start;
	Sprite *level3_Start;
	Sprite *menuSelect;
	lvl_1_control *control_1;
	lvl_2_control *control_2;
	lvl_3_control *control_3;
	Sprite *lvl1Complete;
	Sprite *lvl2Complete;
	Sprite *lvl3Complete;
	Sprite *lvl_1_complete;
	Sprite *lvl_2_complete;
	Sprite *lvl_3_complete;
	

public:

	int tX,tY;
	int levelN;
	int game_load;
	int game_state; // dictates the current game state defined by the gState enum
	int pX,pY; //player x and y positions, completly global and accessible to every class
	int xState;//mouse x and y states
	int yState;//mouse x and y states

	SDL_Event event;
	Uint8 *keys;

	double r, angle;
	

	bool lvl_1_done;
	bool lvl_2_done;
	bool lvl_3_done;
	bool restart;
	bool quit;

	enum gstate{RUNNING_GAME,MENU,CREDITS,QUIT,PAUSE,DEAD,LOADING,LEVEL_COMPLETE,INTRO,DEAD1,DEAD2};
	enum gload{LEVEL_1,LEVEL_2,LEVEL_3,ONE_START,TWO_START,THREE_START};
	Foundation();


	void god_loop(SDL_Surface *screen);
	void menu_loop(SDL_Surface *screen);
	void game_loop(SDL_Surface *screen);
	void credits();
	void quit_Game();
	void control_loop(SDL_Surface *screen);
	void pause_loop(SDL_Surface *screen);
	void death_loop(SDL_Surface *screen);
	void load_loop(SDL_Surface *screen);
	void level_2_Start(SDL_Surface *screen);
	void lvl_1_init();
	void lvl_1_delete();
	void lvl_2_delete();
	void lvl_2_init();
	void lvl_3_init();
	void lvl_3_delete();
	void initAudio();
	int pauseCount;
	int deathCount;
	
	~Foundation();
};



Foundation::Foundation()
{
	levelN = 1;
	game_load = LEVEL_1;
	game_state = INTRO;
	background = new Sprite("background.png",0,0,1280,800,0,0);
	menu = new Sprite("menu.bmp",0,0,1280,800,0,0);
	pauseImage = new Sprite("pauseScreen_01.png",0,0,1280,800,0,0);
	gameOver = new Sprite("gameOver.png",0,0,1280,800,0,0);
	loading = new Sprite("loading.png",0,0,1280,800,0,0);
	level2_Start = new Sprite("startLvL_2.png",0,0,1280,800,0,0);
	level3_Start = new Sprite("StartLvl3.png",0,0,1280,800,0,0);
	tutorial = new Sprite("tutorial.png",0,0,1280,800,0,0);
	menuSelect = new Sprite("selection.png",330,410,100,100,0,0);
	lvl_1_complete = new Sprite("level1complete.png",0,0,1280,800,0,0);
	lvl_2_complete = new Sprite("level2complete.png",0,0,1280,800,0,0);
	lvl_3_complete = new Sprite("level3complete.png",0,0,1280,800,0,0);
	lvl_1_done = false;
	lvl_2_done = false;
	lvl_3_done = false;
	restart = false;
	pauseCount = 1;
	deathCount = 1;
	quit = false;
	
}

Foundation::~Foundation()
{
}

void Foundation::lvl_3_init()
{
	printf("level two has been deleted\n");
	control_3 = new lvl_3_control();
	printf("level three has been loaded\n");
}
void Foundation::lvl_3_delete()
{
	delete control_3;
}
void Foundation::lvl_1_delete()
{
	delete control_1;
}

void Foundation::lvl_2_delete()
{
	delete control_2;
}
void Foundation::initAudio()
{
	
}

void Foundation::lvl_1_init()
{
		
	control_1 = new lvl_1_control();
	printf("Level one has been loaded\n");
}
void Foundation::lvl_2_init()
{
	printf("Level one has be deleted\n");
	control_2 = new lvl_2_control();
	printf("Level two has been loaded\n");

}
void Foundation::quit_Game()
{
	SDL_Quit();
}

void Foundation::level_2_Start(SDL_Surface *screen)
{
	level2_Start->Draw_Sprite(screen);
}

void Foundation::load_loop(SDL_Surface *screen)
{
	if(game_load == LEVEL_1 && lvl_1_done == false)
	{
		loading->Draw_Sprite(screen);
		loading->Animate(0,2);
		SDL_Flip(screen);
		lvl_1_init();
		this->game_load = ONE_START;
		
	}
	else if(game_load == LEVEL_2 && lvl_1_done == true)
	{
		loading->Draw_Sprite(screen);
		loading->Animate(0,2);
		SDL_Flip(screen);
		lvl_1_delete();
		lvl_2_init();
		this->game_load = TWO_START;
	}
	else if(game_load == LEVEL_3 && lvl_2_done == true)
	{
		loading->Draw_Sprite(screen);
		loading->Animate(0,2);
		SDL_Flip(screen);
		lvl_2_delete();
		lvl_3_init();
		this->game_load = THREE_START;
	}
	else if(game_load == ONE_START)
	{
		tutorial->Draw_Sprite(screen);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				this->game_state = RUNNING_GAME;
			}
		}
	}
	else if(game_load == TWO_START)
	{
		level2_Start->Draw_Sprite(screen);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				this->game_state = RUNNING_GAME;
			}
		}
	}
	else if(game_load == THREE_START)
	{
		level3_Start->Draw_Sprite(screen);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				this->game_state = RUNNING_GAME;
			}
		}
	}

}
void Foundation::god_loop(SDL_Surface *screen)
{
	while (game_state != QUIT)
	{
		control_loop(screen);
		if (game_state == INTRO)
		{
			game_state =MENU;
			initAudio();
		}
		if (game_state == MENU)menu_loop(screen);
		if(game_state == RUNNING_GAME)game_loop(screen);
		if(game_state == PAUSE) pause_loop(screen);
		if(game_state == DEAD) death_loop(screen);
		if(game_state == DEAD1) death_loop(screen);
		if(game_state == DEAD2) death_loop(screen);
		if(game_state == LOADING) load_loop(screen);
		if(game_state == QUIT) quit_Game();

	}

}
void Foundation::menu_loop(SDL_Surface *screen)
{
	menu->Draw_Sprite(screen);
	menuSelect->Draw_Sprite(screen);
	SDL_Flip(screen);
}

void Foundation::death_loop(SDL_Surface *screen)
{
	background->Draw_Sprite(screen);
	gameOver->Draw_Sprite(screen);
	SDL_Flip(screen);
}

void Foundation::pause_loop(SDL_Surface *screen)
{
	background->Draw_Sprite(screen);
	pauseImage->Draw_Sprite(screen);
	SDL_Flip(screen);
}
void Foundation::game_loop(SDL_Surface *screen)
{
	while (game_state == RUNNING_GAME)
	{
		control_loop(screen);
		SDL_Flip(screen);
	}
}



void Foundation::credits()
{
}




void Foundation::control_loop(SDL_Surface *screen)
{
	//MENU CONTROL TO START THE GAME//
	if (this->game_state == MENU)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				//starts the game if the correct sprite is shown//
				if(event.key.keysym.sym == SDLK_RETURN && menuSelect->rect.x == 0)
				{
					this->game_state = LOADING;
				}
				//quits the game if the correct sprite is shown//
				if(event.key.keysym.sym == SDLK_RETURN && menuSelect->rect.x == 110)
				{
					this->game_state = QUIT;
				}
				//changes the frame on the sprite//
				if(event.key.keysym.sym == SDLK_DOWN && menuSelect->rect.x == 0)
				{
					menuSelect->rect.x = 110;
				}
				//changes the frame on the sprite//
				if(event.key.keysym.sym == SDLK_UP && menuSelect->rect.x == 110)
				{
					menuSelect->rect.x = 0;
				}
			}
		}
	}
	//CONTROL FOR THE GAME LOOP//
	else if (this->game_state == this->RUNNING_GAME)
	{
			//FLAG FOR IF LVL 1 IS DONE//
			if(lvl_1_done != true)
			{
				//CHECKS IF THE BOSS IS DEAD AND LVL IS FINISHED//
				if(control_1->lvl_1->boss->dead == true)
				{
					Mix_HaltMusic();
					Mix_FreeMusic(control_1->tonal);
					background->Draw_Sprite(screen);
					lvl_1_complete->Draw_Sprite(screen);
					SDL_Flip(screen);
					SDL_Delay(5000);
					lvl_1_done = true;
					this->game_state = LOADING;
					this->game_load = LEVEL_2;
				}
			
				//CHECKS IF THE CHAR IS DEAD//
				if(control_1->lvl_1->mainChar->dead == true)
				{
					this->game_state = DEAD;
				}
				control_1->micro_control(screen);
				//SWITCHES THE GAME STATE TO A PAUSE MENU//
				if(control_1->escape == true)
				{
					this->game_state = PAUSE;
				}
			}
		
		//IF LVL 1 IS DONE START LVL 2//
		else if(lvl_1_done == true && lvl_2_done == false)
		{ 
			if(control_2->lvl_2->boss->dead == true)
			{
				Mix_HaltMusic();
				Mix_FreeMusic(control_2->tonal);
				background->Draw_Sprite(screen);
				lvl_2_complete->Draw_Sprite(screen);
				SDL_Flip(screen);
				SDL_Delay(5000);
				lvl_2_done = true;
				this->game_state = LOADING;
				this->game_load = LEVEL_3;
			}
				//CHECKS IF THE CHAR IS DEAD//
				if(control_2->lvl_2->mainChar->dead == true)
				{
					this->game_state = DEAD1;
				}


				//RUNS THE CONTROL FOR THE SECOND LVL//
				control_2->micro_control(screen);
				
				if(control_2->escape == true)
				{
					this->game_state = PAUSE;
				}

		}
		else if(lvl_2_done == true && lvl_3_done == false)
		{
			control_3->micro_control(screen);
			
			if(control_3->lvl_3->boss->dead == true)
			{
				Mix_HaltMusic();
				Mix_FreeMusic(control_3->tonal);
				background->Draw_Sprite(screen);
				lvl_3_complete->Draw_Sprite(screen);
				SDL_Flip(screen);
				SDL_Delay(5000);
				lvl_3_done = true;
				lvl_3_delete();
				this->game_state = MENU;
			}



			//CHECKS IF THE CHAR IS DEAD//
				if(control_3->lvl_3->mainChar->dead == true)
				{
					this->game_state = DEAD2;
					Mix_HaltMusic();
					Mix_FreeMusic(control_3->tonal);
				}

			if(control_2->escape == true)
			{
				this->game_state = PAUSE;
			}
		}
		
	}
	//CONTROLS FOR THE PAUSE MENU OF THE GAME//
	else if (this->game_state == this->PAUSE)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				if(lvl_1_done == false)
				{
					if(event.key.keysym.sym == SDLK_RETURN && pauseCount == 1)
					{
						this->game_state = RUNNING_GAME;
						control_1->escape = false;
					}
					if(event.key.keysym.sym == SDLK_RETURN && pauseCount == 3)
					{
						this->game_state = MENU;
						control_1->done = true;
						control_1->escape = false;
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						pauseCount++;
						if (pauseCount > 3) pauseCount = 1;
					}
				
					if(event.key.keysym.sym == SDLK_UP)
					{
						pauseCount--;
						if (pauseCount < 1) pauseCount = 3;
					}
				}
				else if(lvl_2_done == false)
				{
					if(event.key.keysym.sym == SDLK_RETURN && pauseCount == 1)
					{
						this->game_load = LEVEL_2;
						control_2->escape = false;
					}
					if(event.key.keysym.sym == SDLK_RETURN && pauseCount == 3)
					{
						this->game_state = MENU;
						control_2->escape = false;
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						pauseCount++;
						if (pauseCount > 3) pauseCount = 1;
					}
				
					if(event.key.keysym.sym == SDLK_UP)
					{
						pauseCount--;
						if (pauseCount < 1) pauseCount = 3;
					}
				}
			}
		}
			if(pauseCount == 1)
			{
				pauseImage->rect.x = 0;
			}
			else if(pauseCount == 2)
			{
				pauseImage->rect.x = 2560;
			}
			else if(pauseCount == 3)
			{
				pauseImage->rect.x = 5120;
			}
		}
	
	//CHECKS IF THE PLAYER IS DEAD//
	else if(this->game_state == DEAD)
	{
		if(lvl_1_done == false)
		{
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_RETURN && deathCount == 1)
					{
						lvl_1_delete();
						this->game_state = LOADING;
						this->game_load = LEVEL_1;
					}
					else if(event.key.keysym.sym == SDLK_RETURN && deathCount == 2)
					{
						this->game_state = MENU;
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						deathCount++;
						if (deathCount > 2) deathCount = 1;
					}
				
					if(event.key.keysym.sym == SDLK_UP)
					{
						deathCount--;
						if (deathCount < 1) deathCount = 2;
					}
				}
				if( deathCount == 1 )
				{
					gameOver->rect.x = 1280;
				}
				else if( deathCount == 2)
				{
					gameOver->rect.x = 0;
				}
			}
		}


	}//END OF DEAD GAME STATE LOOP//

	else if(this->game_state == DEAD1)
	{
		if(lvl_2_done == false)
		{
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_RETURN && deathCount == 1)
					{
						lvl_2_delete();
						this->game_state = LOADING;
						this->game_load = LEVEL_2;
					}
					else if(event.key.keysym.sym == SDLK_RETURN && deathCount == 2)
					{
						this->game_state = MENU;
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						deathCount++;
						if (deathCount > 2) deathCount = 1;
					}
				
					if(event.key.keysym.sym == SDLK_UP)
					{
						deathCount--;
						if (deathCount < 1) deathCount = 2;
					}
				}
				if( deathCount == 1 )
				{
					gameOver->rect.x = 1280;
				}
				else if( deathCount == 2)
				{
					gameOver->rect.x = 0;
				}
			}
		}


	}//END OF DEAD GAME STATE LOOP//

	else if(this->game_state == DEAD2)
	{
		if(lvl_3_done == false)
		{
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_RETURN && deathCount == 1)
					{
						lvl_3_delete();
						this->game_state = LOADING;
						this->game_load = LEVEL_3;
					}
					else if(event.key.keysym.sym == SDLK_RETURN && deathCount == 2)
					{
						this->game_state = MENU;
					}
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						deathCount++;
						if (deathCount > 2) deathCount = 1;
					}
				
					if(event.key.keysym.sym == SDLK_UP)
					{
						deathCount--;
						if (deathCount < 1) deathCount = 2;
					}
				}
				if( deathCount == 1 )
				{
					gameOver->rect.x = 1280;
				}
				else if( deathCount == 2)
				{
					gameOver->rect.x = 0;
				}
			}
		}


	}//END OF DEAD GAME STATE LOOP//
	
}
#endif


