#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class EventManager {
	SDL_Event handler;
	bool* quit;
	bool* play;
	bool* mouse_pressed;
	SDL_Point* window_size;
	bool* window_shown;
	
	public:
		EventManager(bool*, bool*, bool*, SDL_Point*, bool*);
	
		void update();
		void mouseMove();
		void mouseLeftDown();
		void mouseLeftUp();
		void windowResized(int, int);
};

#endif
