#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "data_structures.h"
#include "Pessoa.h"
#include "Objeto.h"

class EventManager {
	SDL_Event handler;
	bool* quit;
	bool* play;
	bool* mouse_pressed;
	SDL_Point* window_size;
	int* tela_id;
	Queue<Pessoa*>* fila;
	int* catraca_estado;
	
	public:
		EventManager(bool*, bool*, bool*, SDL_Point*, int*, Queue<Pessoa*>*, int*);
	
		void update();
		void mouseMove();
		void mouseDown(SDL_MouseButtonEvent&);
		void mouseUp();
		void windowResized(int, int);
};

#endif
