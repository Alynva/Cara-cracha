#ifndef CARA_CRACHA
#define CARA_CRACHA

#include "EventManager.h"
#include "data_structures.h"
#include "Pessoa.h"

#include <iostream>
using namespace std;

class Cara_cracha {
	SDL_Window* g_window; // Janela principal
	SDL_Renderer* g_renderer; // Renderizador principal
	SDL_Texture* g_bg; // Plano de fundo
	bool game_quit; // Responsavel pelo loop principal
	bool game_play; // Respons�vel por come�ar o jogo
	EventManager event; // Eventos
	bool mouse_pressed;

	public:
		int tela_id;
		Queue<Pessoa*> fila;

		Cara_cracha():g_window(NULL), g_renderer(NULL), game_quit(false), game_play(false), event(&this->game_quit, &this->game_play, &this->mouse_pressed) {};

		~Cara_cracha() {
			SDL_DestroyRenderer(this->g_renderer);
			SDL_DestroyWindow(this->g_window);
			this->g_renderer = NULL;
			this->g_window = NULL;

			IMG_Quit();
			SDL_Quit();
		}

		bool init() {

			this->g_window = SDL_CreateWindow("Cara crachá", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
			if (this->g_window == NULL) {
				SDL_Log("Window could not be created. SDL Error: %s", SDL_GetError());
				return false;
			} else {
				// Cria o renderizador
				this->g_renderer = SDL_CreateRenderer(this->g_window, -1, SDL_RENDERER_ACCELERATED);
				if (this->g_renderer == NULL) {
					SDL_Log("Renderer could not be created. SDL Error: %s", SDL_GetError());
					return false;
				} else {

					// Inicializa a cor do renderizador
					SDL_SetRenderDrawColor(this->g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

					// Inicializa o carregamento de PNG
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						SDL_Log("SDL could not initialize image. SDL Error: %s", IMG_GetError());
						return false;
					}

					// Do samething....

					for (int i = 0; i < 10; i++){
						this->fila.enqueue(new Pessoa());
					}

					return true;
				}
			}

			return false;

		}

		Cara_cracha* update() {
			return this;
		}

		Cara_cracha* play() {

			Pessoa* p_temp = nullptr;

			for (int i = 0; i < this->fila.getSize(); i++) {
				this->fila.dequeue(p_temp);

				cout << p_temp->sexo << " " << p_temp->rosto << endl;

				this->fila.enqueue(p_temp);
			}

			return this;

		}
};

#endif