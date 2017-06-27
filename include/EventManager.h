#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "SDL2/SDL.h"

class EventManager {
	SDL_Event handler;
	bool* t_fullscreen;
	bool* quit;
	bool* play;
	SDL_Point* window_size;
	bool mouse_pressed;

	public:
		EventManager(bool*, bool*, bool*, SDL_Point*);
	
		void update();
		void mouseMove();
		void mouseLeftDown();
		void mouseLeftUp();
		void addLogo(Textura*);
		void clearLogo();
		void addStack(PilhaInteligente*);
		void clearStacks();
		void addButton(Button*);
		void clearButtons();
		void windowResized(int, int);
};

#endif
