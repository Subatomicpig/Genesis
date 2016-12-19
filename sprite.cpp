#include "Sprite.h"


Sprite::~Sprite()
{
	SDL_FreeSurface(this->image);
}
Sprite::Sprite(const char* filename, int xpos, int ypos, int width, int height, int xWidth, int yHeight)
{
	this->rect.h = height;
	this->rect.w = width;
	this->rect.x = xWidth;
	this->rect.y = yHeight;
	this->xpos = xpos;
	this->ypos = ypos;
	this->Load_Sprite(filename);
	
	this->maxVelocity = 20;
	this->velocity = 0;
	this->curVelocity = this->velocity;
	this->destroyed = false;
	
	
}

void Sprite::Load_Sprite( const char* filename )
{
	image = IMG_Load(filename);
	if( image == NULL )
	{
		printf("Error Loading Bitmap %s\n", filename);
	}
//	SDL_SetColorKey(this->image, SDL_SRCCOLORKEY, SDL_MapRGB(this->image->format, 255, 0, 255));
}

void Sprite::Draw_Sprite( SDL_Surface *dst_surf)
{
	SDL_Rect dest = {this->xpos, this->ypos, 0, 0};
	SDL_BlitSurface(this->image, &this->rect, dst_surf, &dest);
}

bool Sprite::isVisible()
{
	return 0;
}

void Sprite::setAlpha(int alphaValue)
{
	SDL_SetAlpha(this->image, SDL_SRCALPHA, alphaValue);
}

void Sprite::setVisible(bool visible)
{
	
}


void Sprite::Animate( Uint16 start_frame, Uint16 end_frame)
{
		
		Uint16 current_frame = this->getCurrentFrame();
		if(current_frame < start_frame || current_frame > end_frame )
			current_frame = start_frame;
		else{
			++current_frame;
		
		if(current_frame > end_frame)
			current_frame = start_frame;
			}

		this->setCurrentFrame(current_frame);

	
	

}

Uint16 Sprite::getCurrentFrame()
{
	if(!this->rect.w)
		return 0;
	return
		this->rect.x/this->rect.w;
}

void Sprite::setCurrentFrame(Uint16 frame)
{
	if(!this->rect.w)
		return;
	
	this->rect.x  = this->rect.w * frame;
}


void Sprite::move(int deltaX, int deltaY)
{
	
	this->xpos += deltaX;
	this->ypos += deltaY;
}



void Sprite::Scrolling(bool scroll, int xpos)
{
	
}

int Sprite::getYPos()
{
	return this->ypos;
}

int Sprite::getXpos()
{
	return this->xpos;
}
void Sprite::setYPos(int y)
{
	this->ypos = y;
}

void Sprite::setXPos(int x)
{
	this->xpos = x;
}



int Sprite::getX()
{
	return this->xpos;

}

int Sprite::getY()
{
	return this->ypos;

}

int Sprite::getW()
{
	return this->xWidth;

}

int Sprite::getH()
{
	return this->yHeight;

}

int Sprite::Get_Direction()
{
	return direction;
}

void Sprite::setDirection(int d)
{
	if ( d == 0 || d == 1)	direction = d;
	
}
unsigned int Sprite::worldXpos(int pX)
{
	wXpos = xpos-pX;
	
	return wXpos;
}

unsigned int Sprite::worldYpos(int pY)
{
	wYpos =  pY;
	return wYpos;
}


enum Sprite_Direction {R,L};
int Sprite::getXMouse( int xMouse)
{

	return this->xMouse;
}

int Sprite::getYMouse( int yMouse)
{
	return this->yMouse;
}

