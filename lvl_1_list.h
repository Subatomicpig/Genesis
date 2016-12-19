#ifndef LVL_1_LIST_H
#define LVL_1_LIST_H
#include "lvl_1_enemy.h"
#include "lvl_1_food.h"
#include "lvl_1_character.h"
#include "SDL_mixer.h"
#include "Sprite.h"
#include "timer.h"
#include <iostream>
#include <vector>
using namespace std;



class lvl_1_objects
{


	public:
		
		//backgroud and powerups//
		Sprite *background;
		Sprite *health;
		Sprite *power;
		Sprite *charCol;
		Sprite *hit;
		
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
		Sprite *death;
		Sprite *death_2;
		Sprite *death_3;
		Sprite *death_4;
		Sprite *death_5;
		Sprite *death_6;
		Sprite *death_7;
		Sprite *death_8;
		Sprite *death_9;
		Sprite *death_10;
		Sprite *death_11;
		Sprite *death_12;
		
		//food and enemies//
		lvl_1_food *food_1;
		lvl_1_food *food_2;
		lvl_1_food *food_3;
		lvl_1_food *food_4;
		lvl_1_food *food_5;
		lvl_1_food *food_6;
		lvl_1_food *food_7;
		lvl_1_food *food_8;
		lvl_1_food *food_9;
		lvl_1_food *food_10;
		lvl_1_food *food_11;
		lvl_1_food *food_12;
		lvl_1_food *food_13;
		lvl_1_food *food_14;
		lvl_1_food *food_15;
		lvl_1_food *food_16;
		lvl_1_food *food_17;
		lvl_1_food *food_18;
		lvl_1_food *food_19;
		lvl_1_food *food_20;
		
		lvl_1_character *mainChar;

		lvl_1_enemy *enemy1;
		lvl_1_enemy *enemy2;
		lvl_1_enemy *enemy3;
		lvl_1_enemy *enemy4;
		lvl_1_enemy *enemy5;
		lvl_1_enemy *enemy6;
		lvl_1_enemy *enemy7;
		lvl_1_enemy *enemy8;
		lvl_1_enemy *enemy9;
		lvl_1_enemy *enemy10;
		lvl_1_enemy *enemy11;
		lvl_1_enemy *enemy12;
		lvl_1_enemy *boss;

		//COLLISION BOXES FOR IF THE PLAYER HITS THE BOSS//
		Sprite *bossCol_1;
		Sprite *bossCol_2;
		Sprite *bossCol_3;
		Sprite *bossCol_4;

		//COLLISION BOXES FOR IF THE BOSS HITS THE PLAYER
		Sprite *bossCol_5;
		Sprite *bossCol_6;
		Sprite *bossCol_7;
		Sprite *bossCol_8;

	
		
		vector<Sprite*> objects;
		lvl_1_objects();
		~lvl_1_objects();
		void Update(SDL_Surface *screen);

		bool draw;
		bool done;
};

lvl_1_objects::lvl_1_objects()
{

	draw = false;

	

	//initializes and loads the image files for sprites//
	mainChar = new lvl_1_character("MainChar_Micro.png",60,60,240,240,0,0);
	charCol = new Sprite("charCol.png",0,0,240,240,0,0);
	background = new Sprite("bglvl1.jpg",0,0,6000,6000,0,0);
	health = new Sprite("health bar.png",mainChar->characterSprite->xpos,mainChar->characterSprite->ypos, 240, 240,0,0);
	power = new Sprite("power.png",1000,730, 272,68,0,0);
	death = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_2 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_3 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_4 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_5 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_6 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_7 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_8 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_9 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_10 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_11 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);
	death_12 = new Sprite("deathBoom5.png", 50,50,800,600,0,0);

	//ENEMY SPRITES//
	//enemy1 = new lvl_1_enemy("micro_enemy1_sprite.png",1000,1000,240,240,0,0);
	enemy1 = new lvl_1_enemy("micro_enemy1_sprite.png",500,500,240,240,0,0);
	enemy2 = new lvl_1_enemy("micro_enemy1_sprite.png",1500,2300,240,240,0,0);
	enemy3 = new lvl_1_enemy("micro_enemy1_sprite.png",3000,1200,240,240,0,0);
	enemy4 = new lvl_1_enemy("micro_enemy1_sprite.png",4700,1800,240,240,0,0);
	enemy5 = new lvl_1_enemy("micro_enemy1_sprite.png",4000,3200,240,240,0,0);
	enemy6 = new lvl_1_enemy("micro_enemy1_sprite.png",900,5400,240,240,0,0);
	enemy7 = new lvl_1_enemy("micro_enemy1_sprite.png",4500,5400,240,240,0,0);
	enemy8 = new lvl_1_enemy("micro_enemy1_sprite.png",500,3400,240,240,0,0);
	enemy9 = new lvl_1_enemy("micro_enemy1_sprite.png",3200,4700,240,240,0,0);
	enemy10 = new lvl_1_enemy("micro_enemy1_sprite.png",5300,4000,240,240,0,0);
	enemy11 = new lvl_1_enemy("micro_enemy1_sprite.png",2200,3350,240,240,0,0);
	enemy12 = new lvl_1_enemy("micro_enemy1_sprite.png",200,800,240,240,0,0);
	//boss = new lvl_1_enemy("boss1_micro.png",0,0,480,480,0,0);
	boss = new lvl_1_enemy("boss1_micro.png",3000,3500,480,480,0,0);
	
	
	//FOOD SPRITES//
	food_1 = new lvl_1_food("MicroFood2.png", 500,900, 100,100,0,0);
	food_2 = new lvl_1_food("MicroFood2.png", 300,300, 100,100,0,0);
	food_3 = new lvl_1_food("MicroFood2.png", 3000,500, 100,100,0,0);
	food_4 = new lvl_1_food("MicroFood2.png", 300,5000, 100,100,0,0);
	food_5 = new lvl_1_food("MicroFood2.png", 5500,5500, 100,100,0,0);
	food_6 = new lvl_1_food("MicroFood2.png", 1000,4500, 100,100,0,0);
	food_7 = new lvl_1_food("MicroFood2.png", 2400,4300, 100,100,0,0);
	food_8 = new lvl_1_food("MicroFood2.png", 1500,1500, 100,100,0,0);
	food_9 = new lvl_1_food("MicroFood2.png", 900,2300, 100,100,0,0);
	food_10 = new lvl_1_food("MicroFood2.png", 4100,2500, 100,100,0,0);
	food_11 = new lvl_1_food("MicroFood2.png", 5000,3500, 100,100,0,0);
	food_12 = new lvl_1_food("MicroFood2.png", 4000,4900, 100,100,0,0);
	food_13 = new lvl_1_food("MicroFood2.png", 2900,2700, 100,100,0,0);
	food_14 = new lvl_1_food("MicroFood2.png", 5500,2300, 100,100,0,0);
	food_15 = new lvl_1_food("MicroFood2.png", 2800,5300, 100,100,0,0);
	food_16 = new lvl_1_food("MicroFood2.png", 5100,4400, 100,100,0,0);
	food_17 = new lvl_1_food("MicroFood2.png", 3600,3600, 100,100,0,0);
	food_18 = new lvl_1_food("MicroFood2.png", 1500,3100, 100,100,0,0);
	food_19 = new lvl_1_food("MicroFood2.png", 3200,1700, 100,100,0,0);
	food_20 = new lvl_1_food("MicroFood2.png", 1600,5500, 100,100,0,0);
	
	//images to base collision off of//
	col = new Sprite("colBox.bmp", 10, 10, 80,81,0,0);
	enemyCol = new Sprite("colBox.bmp", enemy1->enemySprite->xpos + 100, enemy1->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_2 = new Sprite("colBox.bmp", enemy2->enemySprite->xpos + 100, enemy2->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_3 = new Sprite("colBox.bmp", enemy3->enemySprite->xpos + 100, enemy3->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_4 = new Sprite("colBox.bmp", enemy4->enemySprite->xpos + 100, enemy4->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_5 = new Sprite("colBox.bmp", enemy5->enemySprite->xpos + 100, enemy5->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_6 = new Sprite("colBox.bmp", enemy6->enemySprite->xpos + 100, enemy6->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_7 = new Sprite("colBox.bmp", enemy7->enemySprite->xpos + 100, enemy7->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_8 = new Sprite("colBox.bmp", enemy8->enemySprite->xpos + 100, enemy8->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_9 = new Sprite("colBox.bmp", enemy9->enemySprite->xpos + 100, enemy9->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_10 = new Sprite("colBox.bmp", enemy10->enemySprite->xpos + 100, enemy10->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_11 = new Sprite("colBox.bmp", enemy11->enemySprite->xpos + 100, enemy11->enemySprite->ypos + 100, 80,81,0,0);
	enemyCol_12 = new Sprite("colBox.bmp", enemy12->enemySprite->xpos + 100, enemy12->enemySprite->ypos + 100, 80,81,0,0);
	foodCol_1 = new Sprite("colFood.bmp", food_1->foodSprite->xpos, food_1->foodSprite->ypos,20,20,0,0);
	foodCol_2 = new Sprite("colFood.bmp", food_2->foodSprite->xpos, food_2->foodSprite->ypos,20,20,0,0);
	foodCol_3 = new Sprite("colFood.bmp", food_3->foodSprite->xpos, food_3->foodSprite->ypos,20,20,0,0);
	foodCol_4 = new Sprite("colFood.bmp", food_4->foodSprite->xpos, food_4->foodSprite->ypos,20,20,0,0);
	foodCol_5 = new Sprite("colFood.bmp", food_5->foodSprite->xpos, food_5->foodSprite->ypos,20,20,0,0);
	foodCol_6 = new Sprite("colFood.bmp", food_6->foodSprite->xpos, food_6->foodSprite->ypos,20,20,0,0);
	foodCol_7 = new Sprite("colFood.bmp", food_7->foodSprite->xpos, food_7->foodSprite->ypos,20,20,0,0);
	foodCol_8 = new Sprite("colFood.bmp", food_8->foodSprite->xpos, food_8->foodSprite->ypos,20,20,0,0);
	foodCol_9 = new Sprite("colFood.bmp", food_9->foodSprite->xpos, food_9->foodSprite->ypos,20,20,0,0);
	foodCol_10 = new Sprite("colFood.bmp", food_10->foodSprite->xpos, food_10->foodSprite->ypos,20,20,0,0);
	foodCol_11 = new Sprite("colFood.bmp", food_11->foodSprite->xpos, food_11->foodSprite->ypos,20,20,0,0);
	foodCol_12 = new Sprite("colFood.bmp", food_12->foodSprite->xpos, food_12->foodSprite->ypos,20,20,0,0);
	foodCol_13 = new Sprite("colFood.bmp", food_13->foodSprite->xpos, food_13->foodSprite->ypos,20,20,0,0);
	foodCol_14 = new Sprite("colFood.bmp", food_14->foodSprite->xpos, food_14->foodSprite->ypos,20,20,0,0);
	foodCol_15 = new Sprite("colFood.bmp", food_15->foodSprite->xpos, food_15->foodSprite->ypos,20,20,0,0);
	foodCol_16 = new Sprite("colFood.bmp", food_16->foodSprite->xpos, food_16->foodSprite->ypos,20,20,0,0);
	foodCol_17 = new Sprite("colFood.bmp", food_17->foodSprite->xpos, food_17->foodSprite->ypos,20,20,0,0);
	foodCol_18 = new Sprite("colFood.bmp", food_18->foodSprite->xpos, food_18->foodSprite->ypos,20,20,0,0);
	foodCol_19 = new Sprite("colFood.bmp", food_19->foodSprite->xpos, food_19->foodSprite->ypos,20,20,0,0);
	foodCol_20 = new Sprite("colFood.bmp", food_20->foodSprite->xpos, food_20->foodSprite->ypos,20,20,0,0);

	//ASSINGS THE COL BOXES FOR THE BOSS IF THE PLAYER HITS//
	bossCol_1 = new Sprite("bossCol.bmp", boss->enemySprite->xpos, boss->enemySprite->ypos, 60,60,0,0);
	bossCol_2 = new Sprite("bossCol.bmp", 0 , 0, 60,60,0,0);
	bossCol_3 = new Sprite("bossCol.bmp", boss->enemySprite->xpos, boss->enemySprite->ypos, 60,60,0,0);
	bossCol_4 = new Sprite("bossCol.bmp", 0,0, 60,60,0,0);

	//ASSINGS THE COL BOXES FOR IF THE PLAYER GETS HIT BY BOSS//
	bossCol_5 = new Sprite("bossCol.bmp",0,0,100,100,0,0);
	bossCol_6 = new Sprite("bossCol.bmp",60,60,100,100,0,0);
	bossCol_7 = new Sprite("bossCol.bmp",120,120,100,100,0,0);
	bossCol_8 = new Sprite("bossCol.bmp",190,190,100,100,0,0);

	hit = new Sprite("deathHit.png",50,50,270,270,0,0);
}

void lvl_1_objects::Update(SDL_Surface *screen)
{
	//draws the background for the first lvl//
	background->Draw_Sprite(screen);
	
	
}

lvl_1_objects::~lvl_1_objects()
{

		//background and powerups//
		 delete background;
		 delete health;
		 delete power;
		 delete charCol;
		 delete hit;
		
		//collision boxes//
		 delete col;
		 delete enemyCol;
		 delete enemyCol_2;
		 delete enemyCol_3;
		 delete enemyCol_4;
		 delete enemyCol_5;
		 delete enemyCol_6;
		 delete enemyCol_7;
		 delete enemyCol_8;
		 delete enemyCol_9;
		 delete enemyCol_10;
		 delete enemyCol_11;
		 delete enemyCol_12;
		 delete foodCol_1;
		 delete foodCol_2;
		 delete foodCol_3;
		 delete foodCol_4;
		 delete foodCol_5;
		 delete foodCol_6;
		 delete foodCol_7;
		 delete foodCol_8;
		 delete foodCol_9;
		 delete foodCol_10;
		 delete foodCol_11;
		 delete foodCol_12;
		 delete foodCol_13;
		 delete foodCol_14;
		 delete foodCol_15;
		 delete foodCol_16;
		 delete foodCol_17;
		 delete foodCol_18;
		 delete foodCol_19;
		 delete foodCol_20;
		 delete death;
		 delete death_2;
		 delete death_3;
		 delete death_4;
		 delete death_5;
		 delete death_6;
		 delete death_7;
		 delete death_8;
		 delete death_9;
		 delete death_10;
		 delete death_11;
		 delete death_12;
		
		//food and enemies//
		 delete food_1;
		 delete food_2;
		 delete food_3;
		 delete food_4;
		 delete food_5;
		 delete food_6;
		 delete food_7;
		 delete food_8;
		 delete food_9;
		 delete food_10;
		 delete food_11;
		 delete food_12;
		 delete food_13;
		 delete food_14;
		 delete food_15;
		 delete food_16;
		 delete food_17;
		 delete food_18;
		 delete food_19;
		 delete food_20;
		
		delete mainChar;

		 delete enemy1;
		 delete enemy2;
		 delete enemy3;
		 delete enemy4;
		 delete enemy5;
		 delete enemy6;
		 delete enemy7;
		 delete enemy8;
		 delete enemy9;
		 delete enemy10;
		 delete enemy11;
		 delete enemy12;
		 delete boss;

		//COLLISION BOXES FOR IF THE PLAYER HITS THE BOSS//
		delete bossCol_1;
		delete bossCol_2;
		delete bossCol_3;
		delete bossCol_4;

		//COLLISION BOXES FOR IF THE BOSS HITS THE PLAYER
		delete bossCol_5;
		delete bossCol_6;
		delete bossCol_7;
		delete bossCol_8;

	
}

#endif