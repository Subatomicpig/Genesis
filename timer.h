#ifndef TIMER_H
#define TIMER_H
#include "SDL.h"
#include <string>
#include <sstream>

class Timer
{
    private:
  
    
    bool paused;
    bool started;    
    public:  
	int startTicks;
    int pausedTicks; 
    Timer(); 
    void start();
	void reset();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();
	void slow();
	bool slowed;
	void unslow();
	
};

Timer::Timer()
{
    
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;    
}

void Timer::reset()
{
	this->startTicks = 0;
}
void Timer::slow()
{
	slowed  = true;
}
void Timer::unslow()
{
	slowed = false;
}
void Timer::start()
{
    
    started = true;
    paused = false;
	startTicks = SDL_GetTicks(); 

}

void Timer::stop()
{
    
    started = false;
   
   
    paused = false;    
}

void Timer::pause()
{
   SDL_Delay(18);
    if( ( started == true ) && ( paused == false ) )
    {
       
        paused = true;
    
        
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    
    if( paused == true )
    {
        
        paused = false;
    
       
        startTicks = SDL_GetTicks() - pausedTicks;
        
        
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
	
    if( started == true )
    {
      
        if( paused == true )
        {
           
            return pausedTicks;
        }
        else
        {
           
            return SDL_GetTicks() - startTicks;
        }    
    }
    
    return 0;    
}

bool Timer::is_started()
{
    return started;    
}

bool Timer::is_paused()
{
    return paused;    
}


	


#endif 