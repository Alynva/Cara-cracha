#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "data_structures.h"
#include "Pessoa.h"

class EventManager {
	SDL_Event handler;
	bool* quit;
	bool* play;
	bool* mouse_pressed;
	SDL_Point* window_size;
	int* tela_id;
	Queue<Pessoa*>* fila;
	
	public:
		EventManager(bool*, bool*, bool*, SDL_Point*, int*, Queue<Pessoa*>*);
	
		void update();
		void mouseMove();
		void mouseDown(SDL_MouseButtonEvent&);
		void mouseUp();
		void windowResized(int, int);
};

#endif
