#ifndef SPRITE_H
#define SPRITE_H
#include "SDL.h"
#include "SDL_image.h"





class Sprite {
	private:

		
		
		
	public:
		SDL_Surface *image;
		SDL_Rect rect;
		int width, height;
		int xpos, ypos;
		int xWidth, yHeight;
		int y;
		int xMouse, yMouse;
		enum Sprite_Direction{R,L};

		const char* filename;
		int offset,direction;
		int velocity;
		int frame;
		int status;
		int Sprite_Size;
		int startPos;
		int getYPos();
		int Sprite::getXpos();
		void setYPos(int y);
		void Sprite::setXPos(int x);
		bool destroyed;
		int deltaY;
		int deltaX;
		int gravity;
		int endPos;
		bool moving;
		int maxVelocity;
		int curVelocity;
		double angle;

		
		
		int getX();
		int getY();
		int getW();
		int getH();
		int wXpos;
		int wYpos;

		Uint16 getCurrentFrame();
		
		
		Sprite(const char* filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight);
		void Draw_Sprite( SDL_Surface *dst_surf );
		void Sprite::Animate(Uint16 current_frame, Uint16 end_frame);
		void setCurrentFrame( Uint16 frame );
		void Load_Sprite( const char* filename );
		int Get_Direction();
		void setDirection(int d);
	
		
		void Sprite::Scrolling(bool scrool, int xpos);
		void Sprite::move(int deltaX, int deltaY);
		bool getBGScroll();
		bool isVisible();
		void setBGScroll(bool scroll);
		void Sprite::setAlpha(int alphaValue);
		void Sprite::setVisible(bool visible);

	

		unsigned int worldXpos(int pX);
		unsigned int worldYpos(int pY);

		int Sprite::getXMouse( int xMouse);
		int Sprite::getYMouse( int yMouse);

		~Sprite();
		


		
};








#endif