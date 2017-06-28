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
	bool window_shown;
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
		Queue<GeoA::Vetor> fila_pos;

		Cara_cracha():g_window(NULL), window_shown(false), g_renderer(NULL), game_quit(false), game_play(false), event(&this->game_quit, &this->game_play, &this->mouse_pressed, &this->window_size, &this->window_shown), mouse_pressed(false), hour(630), tela_id(0) {
		};

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
					this->event.update();

					this->g_bg = SDL_CreateTextureFromSurface(this->g_renderer, IMG_Load("../media/img/1.jpg"));
					if (this->g_bg == NULL) {
						SDL_Log("Erro Img: %s", SDL_GetError());
					}

					for (int i = 0; i < 10; i++){
						this->fila.enqueue(new Pessoa());
					}

					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5, this->window_size.y*3/4, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5-50, this->window_size.y*3/4.3, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5, this->window_size.y*3/4.6, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5+50, this->window_size.y*3/4.9, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5, this->window_size.y*3/5.2, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5-50, this->window_size.y*3/5.4, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5-100, this->window_size.y*3/5.6, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5-50, this->window_size.y*3/5.7, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5, this->window_size.y*3/5.8, 0));
					this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5+50, this->window_size.y*3/5.85, 0));

					for (int i = 0; i < this->fila.getSize(); i++){
						this->fila[i]->pos = this->fila_pos[i];
						this->fila[i]->initTextures(this->g_renderer);
					}

					this->tela_id = 1;

					return true;
				}
			}

			return false;

		}

		bool update() {

			this->event.update();

			if (this->window_shown) {
				// Limpa a tela
				SDL_RenderClear(this->g_renderer);


				// Renderiza o background
				int iw, ih; // Vari�veis para calcular o tamanho e posi��o da imagem sem distor�o
				SDL_QueryTexture(this->g_bg, NULL, NULL, &iw, &ih); // Get the image size
				SDL_Rect bg_quad = getFillSize(iw, ih, this->window_size.x, this->window_size.y);
				SDL_RenderCopy(this->g_renderer, this->g_bg, NULL, &bg_quad);
				
				switch (this->tela_id) {
					case 1:
						this->tela_id = 2;
						break;
					case 2:
						this->fila[0]->cart.render();
						break;
				}

				/*if (this->mouse_pressed)
					for (int i = 0; i < this->fila.getSize(); i++)
						this->fila[i]->applyForce(this->fila[i]->arrive(new GeoA::Vetor()));*/

				for (int i = this->fila.getSize() - 1; i >= 0; i--)
						this->fila[i]->update()->render();

				SDL_RenderPresent(this->g_renderer);
			}

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