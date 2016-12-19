#ifndef LVL_3_LIST_H
#define LVL_3_LIST_H
#include "lvl_3_enemy.h"
#include "lvl_3_food.h"
#include "lvl_3_character.h"
#include "SDL_mixer.h"
#include "Sprite.h"
#include "timer.h"
#include <iostream>
#include <vector>
using namespace std;



class lvl_3_objects
{


	public:
		Sprite *test;
		
		
		
		//background and powerups//
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
		lvl_3_enemy *enemy13;
		lvl_3_enemy *enemy14;
		lvl_3_enemy *enemy15;

		lvl_3_enemy *boss;

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
		lvl_3_objects();
		~lvl_3_objects();
		void Update(SDL_Surface *screen);

		bool draw;
		bool done;
};

lvl_3_objects::lvl_3_objects()
{

	draw = false;

	

	//initializes and loads the image files for sprites//
	mainChar = new lvl_3_character("lvl3_mainChar.png",0,0,400,400,0,0);
	charCol = new Sprite("charCol.png",0,0,240,240,0,0);
    background = new Sprite("level3.jpg",0,0,9000,9000,0,0);
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
	//enemy1 = new lvl_3_enemy("micro_enemy1_sprite.png",1000,1000,240,240,0,0);
	enemy1 = new lvl_3_enemy("enem3.png",1276,1316,350,350,0,0);
	enemy2 = new lvl_3_enemy("enem3.png",2384,2384,350,350,0,0);
	enemy3 = new lvl_3_enemy("enem3.png",4388,420,350,350,0,0);
	enemy4 = new lvl_3_enemy("enem3.png",760,4836,350,350,0,0);
	enemy5 = new lvl_3_enemy("enem3.png",2000,5994,350,350,0,0);
	enemy6 = new lvl_3_enemy("enem3.png",4760,6240,350,350,0,0);
	enemy7 = new lvl_3_enemy("enem3.png",4672,7068,350,350,0,0);
	enemy8 = new lvl_3_enemy("enem3.png",6556,1992,350,350,0,0);
	enemy9 = new lvl_3_enemy("enem3.png",6796,3696,350,350,0,0);
	enemy10 = new lvl_3_enemy("enem3.png",6891,5790,350,350,0,0);
	enemy11 = new lvl_3_enemy("enem3.png",6850,8000,350,350,0,0);
	enemy12 = new lvl_3_enemy("enem3.png",7383,8100,350,350,0,0);
	boss = new lvl_3_enemy("boss3.png",6837,6576,600,600,0,0);
	
	
	//FOOD SPRITES//
	food_1 = new lvl_3_food("food3.png", 1332,1272, 110,110,0,0);
	food_2 = new lvl_3_food("food3.png", 2424,156, 110,110,0,0);
	food_3 = new lvl_3_food("food3.png", 2232,3600, 110,110,0,0);
	food_4 = new lvl_3_food("food3.png", 6468,1356, 110,110,0,0);
	food_5 = new lvl_3_food("food3.png", 5784,3360, 110,110,0,0);
	food_6 = new lvl_3_food("food3.png", 3252,1158, 110,110,0,0);
	food_7 = new lvl_3_food("food3.png", 1000,5500, 110,110,0,0);
	food_8 = new lvl_3_food("food3.png", 4812,7860, 110,110,0,0);
	food_9 = new lvl_3_food("food3.png", 900,2300, 110,110,0,0);
	food_10 = new lvl_3_food("food3.png", 5496,6048, 110,110,0,0);
	food_11 = new lvl_3_food("food3.png", 6840,5784, 110,110,0,0);
	food_12 = new lvl_3_food("food3.png", 7884,7380, 110,110,0,0);
	food_13 = new lvl_3_food("food3.png", 7608,6912, 110,110,0,0);
	food_14 = new lvl_3_food("food3.png", 612,2964, 110,110,0,0);
	food_15 = new lvl_3_food("food3.png", 6132,6804, 110,110,0,0);
	food_16 = new lvl_3_food("food3.png", 6336,6156, 110,110,0,0);
	food_17 = new lvl_3_food("food3.png", 7296,6180, 110,110,0,0);
	food_18 = new lvl_3_food("food3.png", 6780,6144, 110,110,0,0);
	food_19 = new lvl_3_food("food3.png", 2892,1440, 110,110,0,0);
	food_20 = new lvl_3_food("food3.png", 2712,7068, 110,110,0,0);
	
	
	//images to base collision off of//
	col = new Sprite("colBox.bmp", 10, 10, 150,150,0,0);
	enemyCol = new Sprite("colBox.bmp", enemy1->enemySprite->xpos + 100, enemy1->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_2 = new Sprite("colBox.bmp", enemy2->enemySprite->xpos + 100, enemy2->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_3 = new Sprite("colBox.bmp", enemy3->enemySprite->xpos + 100, enemy3->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_4 = new Sprite("colBox.bmp", enemy4->enemySprite->xpos + 100, enemy4->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_5 = new Sprite("colBox.bmp", enemy5->enemySprite->xpos + 100, enemy5->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_6 = new Sprite("colBox.bmp", enemy6->enemySprite->xpos + 100, enemy6->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_7 = new Sprite("colBox.bmp", enemy7->enemySprite->xpos + 100, enemy7->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_8 = new Sprite("colBox.bmp", enemy8->enemySprite->xpos + 100, enemy8->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_9 = new Sprite("colBox.bmp", enemy9->enemySprite->xpos + 100, enemy9->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_10 = new Sprite("colBox.bmp", enemy10->enemySprite->xpos + 100, enemy10->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_11 = new Sprite("colBox.bmp", enemy11->enemySprite->xpos + 100, enemy11->enemySprite->ypos + 100, 150,150,0,0);
	enemyCol_12 = new Sprite("colBox.bmp", enemy12->enemySprite->xpos + 100, enemy12->enemySprite->ypos + 100, 150,150,0,0);
	foodCol_1 = new Sprite("colFood.bmp", food_1->foodSprite->xpos, food_1->foodSprite->ypos,50,50,0,0);
	foodCol_2 = new Sprite("colFood.bmp", food_2->foodSprite->xpos, food_2->foodSprite->ypos,50,50,0,0);
	foodCol_3 = new Sprite("colFood.bmp", food_3->foodSprite->xpos, food_3->foodSprite->ypos,50,50,0,0);
	foodCol_4 = new Sprite("colFood.bmp", food_4->foodSprite->xpos, food_4->foodSprite->ypos,50,50,0,0);
	foodCol_5 = new Sprite("colFood.bmp", food_5->foodSprite->xpos, food_5->foodSprite->ypos,50,50,0,0);
	foodCol_6 = new Sprite("colFood.bmp", food_6->foodSprite->xpos, food_6->foodSprite->ypos,50,50,0,0);
	foodCol_7 = new Sprite("colFood.bmp", food_7->foodSprite->xpos, food_7->foodSprite->ypos,50,50,0,0);
	foodCol_8 = new Sprite("colFood.bmp", food_8->foodSprite->xpos, food_8->foodSprite->ypos,50,50,0,0);
	foodCol_9 = new Sprite("colFood.bmp", food_9->foodSprite->xpos, food_9->foodSprite->ypos,50,50,0,0);
	foodCol_10 = new Sprite("colFood.bmp", food_10->foodSprite->xpos, food_10->foodSprite->ypos,50,50,0,0);
	foodCol_11 = new Sprite("colFood.bmp", food_11->foodSprite->xpos, food_11->foodSprite->ypos,50,50,0,0);
	foodCol_12 = new Sprite("colFood.bmp", food_12->foodSprite->xpos, food_12->foodSprite->ypos,50,50,0,0);
	foodCol_13 = new Sprite("colFood.bmp", food_13->foodSprite->xpos, food_13->foodSprite->ypos,50,50,0,0);
	foodCol_14 = new Sprite("colFood.bmp", food_14->foodSprite->xpos, food_14->foodSprite->ypos,50,50,0,0);
	foodCol_15 = new Sprite("colFood.bmp", food_15->foodSprite->xpos, food_15->foodSprite->ypos,50,50,0,0);
	foodCol_16 = new Sprite("colFood.bmp", food_16->foodSprite->xpos, food_16->foodSprite->ypos,50,50,0,0);
	foodCol_17 = new Sprite("colFood.bmp", food_17->foodSprite->xpos, food_17->foodSprite->ypos,50,50,0,0);
	foodCol_18 = new Sprite("colFood.bmp", food_18->foodSprite->xpos, food_18->foodSprite->ypos,50,50,0,0);
	foodCol_19 = new Sprite("colFood.bmp", food_19->foodSprite->xpos, food_19->foodSprite->ypos,50,50,0,0);
	foodCol_20 = new Sprite("colFood.bmp", food_20->foodSprite->xpos, food_20->foodSprite->ypos,50,50,0,0);

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

void lvl_3_objects::Update(SDL_Surface *screen)
{
	//draws the background for the first lvl//
	background->Draw_Sprite(screen);
	
}

lvl_3_objects::~lvl_3_objects()
{

}

#endif