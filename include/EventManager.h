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
	int* tela_id;
	Queue<Pessoa*>* fila;
	double* catraca_estado;
	int* count_criterios;
	
	public:
		EventManager(bool*, bool*, bool*, int*, Queue<Pessoa*>*, double*, int*);
	
		void update();
		void mouseMove();
		void mouseDown(SDL_MouseButtonEvent&);
		void mouseUp();
		void keyDown(SDL_KeyboardEvent&);
		bool checaCart(const Pessoa *);
};

#endif
