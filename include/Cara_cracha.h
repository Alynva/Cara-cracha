#ifndef CARA_CRACHA
#define CARA_CRACHA

#include "EventManager.h"
#include "data_structures.h"
#include "Pessoa.h"
#include "get_fill_size.hpp"

#include <iostream>
using namespace std;

class Cara_cracha {
	SDL_Window* g_window; // Janela principal
	SDL_Point window_size; // Tamanho da janela
	SDL_Renderer* g_renderer; // Renderizador principal
	SDL_Texture* g_bg; // Plano de fundo
	bool game_quit; // Responsavel pelo loop principal
	bool game_play; // Respons�vel por come�ar o jogo
	EventManager event; // Eventos
	bool mouse_pressed;
	double hour;

	public:
		int tela_id;
		Queue<Pessoa*> fila;

		Cara_cracha():g_window(NULL), g_renderer(NULL), game_quit(false), game_play(false), event(&this->game_quit, &this->game_play, &this->mouse_pressed, &this->window_size), mouse_pressed(false), hour(630) {};

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
					SDL_SetRenderDrawColor(this->g_renderer, 0, 0, 0, 255);

					// Inicializa o carregamento de PNG
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						SDL_Log("SDL could not initialize image. SDL Error: %s", IMG_GetError());
						return false;
					}

					// Do samething....

					this->g_bg = SDL_CreateTextureFromSurface(this->g_renderer, IMG_Load("../media/img/1.jpg"));
					if (this->g_bg == NULL) {
						SDL_Log("Erro Img: %s", SDL_GetError());
					}

					for (int i = 0; i < 10; i++){
						this->fila.enqueue(new Pessoa());
					}

					for (int i = 0; i < this->fila.getSize(); i++)
						this->fila[i]->initTextures(this->g_renderer);

					return true;
				}
			}

			return false;

		}

		bool update() {

			this->event.update();

			// Limpa a tela
			SDL_RenderClear(this->g_renderer);

			// Renderiza o background
			int iw, ih; // Vari�veis para calcular o tamanho e posi��o da imagem sem distor�o
			SDL_QueryTexture(this->g_bg, NULL, NULL, &iw, &ih); // Get the image size
			SDL_Rect bg_quad = getFillSize(iw, ih, this->window_size.x, this->window_size.y);
			SDL_RenderCopy(this->g_renderer, this->g_bg, NULL, &bg_quad);

			if (this->mouse_pressed)
				for (int i = 0; i < this->fila.getSize(); i++)
					this->fila[i]->arrive(this->fila[i]->pos.add(GeoA::Vetor::random2D()->mult(50)));

			for (int i = 0; i < this->fila.getSize(); i++)
					this->fila[i]->update()->render();

			SDL_RenderPresent(this->g_renderer);

			return !this->game_quit;
		}

		Cara_cracha* play() {

			for (int i = 0; i < this->fila.getSize(); i++) {

				this->fila[i]->render();
			
			}

			return this;

		}
};

#endif