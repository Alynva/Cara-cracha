#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class EventManager {
	SDL_Event handler;
	bool* quit;
	bool* play;
	bool* mouse_pressed;
	
	public:
		EventManager(bool*, bool*, bool*);
	
		void update();
		void mouseMove();
		void mouseLeftDown();
		void mouseLeftUp();
};

#endif
