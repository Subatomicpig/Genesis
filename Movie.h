#ifndef MOVIE_H
#define MOVIE_H

#include "SDL.h"
#include "smpeg.h"

typedef struct {
	SMPEG *mpeg;
	SMPEG_Info info;
	SDL_Surface *tmp_surf;
	SDL_Rect rect;
	int volume;
} Movie;

Movie m;
SDL_Surface * screen = NULL;

void Movie_Update(SDL_Surface * buffer, Sint32 x, Sint32 y, Uint32 w, Uint32 h)
{
	SDL_BlitSurface(m.tmp_surf, NULL, screen, &m.rect);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

int Movie_Load(const char *filename, int x, int y)
{
	Uint32 rmask, gmask, bmask, amask;
	m.mpeg = SMPEG_new(filename, &m.info, 1);

	if (SMPEG_error(m.mpeg)) 
	{
		fprintf(stderr, "%s: %s\n", filename, SMPEG_error(m.mpeg));
		SMPEG_delete(m.mpeg);
		return 1;
	}

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff0000ff;
#endif

	m.tmp_surf = SDL_CreateRGBSurface(SDL_SWSURFACE, m.info.width,m.info.height, 32, rmask, gmask, bmask,amask);
	printf("width %d\n", m.info.width);
	printf("height %d\n", m.info.height);
	
	if (m.tmp_surf == NULL) 
	{
		fprintf(stderr, "Failed to create RGB surface\n");
		return 1;
	}

	m.rect.x = x;
	m.rect.y = y;
	m.rect.w = 0;
	m.rect.h = 0;

	return 0;
}


void Movie_SetDisplay()
{
	SMPEG_setdisplay(m.mpeg, m.tmp_surf, NULL, Movie_Update);
}

void Movie_Play()
{
	SMPEG_play(m.mpeg);
}

int Movie_Playing()
{
	return (SMPEG_status(m.mpeg) == SMPEG_PLAYING);
}

void Movie_Pause()
{
	SMPEG_pause(m.mpeg);
}

void Movie_Delete()
{
	SMPEG_delete(m.mpeg);
}

#endif