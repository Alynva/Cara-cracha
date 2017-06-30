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

	short int max_fps;
	unsigned int curr_fr;
	unsigned int last_fr;

	double hour;

	public:
		int tela_id;
		Pessoa user;
		Queue<Pessoa*> fila;
		Queue<GeoA::Vetor> fila_pos;

		Cara_cracha():
			g_window(NULL),
			g_renderer(NULL),
			game_quit(false),
			game_play(false),
			event(&this->game_quit, &this->game_play, &this->mouse_pressed, &this->window_size),
			mouse_pressed(false),
			max_fps(60),
			curr_fr(0),
			last_fr(0),
			hour(630),
			tela_id(0),
			user(Pessoa(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
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
			//SDL_Init(SDL_INIT_VIDEO);
			this->g_window = SDL_CreateWindow("Cara crachá", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, -1, -1, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
			if (this->g_window == NULL) {
				SDL_Log("Window could not be created. SDL Error: %s", SDL_GetError());
				return false;
			} else {
				// Cria o renderizador
				this->g_renderer = SDL_CreateRenderer(this->g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (this->g_renderer == NULL) {
					SDL_Log("Renderer could not be created. SDL Error: %s", SDL_GetError());
					return false;
				} else {

					// Inicializa a cor do renderizador
					SDL_SetRenderDrawColor(this->g_renderer, 255, 0, 0, 255);

					// Inicializa o carregamento de PNG
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						SDL_Log("SDL could not initialize image. SDL Error: %s", IMG_GetError());
						return false;
					}

					// Do samething....
					this->event.update();

					this->g_bg = SDL_CreateTextureFromSurface(this->g_renderer, IMG_Load("../media/img/background.png"));
					if (this->g_bg == NULL) {
						SDL_Log("Erro Img: %s", SDL_GetError());
					}

					for (int i = 0; i < 10; i++){
						this->fila.enqueue(new Pessoa());
					}

					this->updateFilaPos();

					for (int i = 0; i < this->fila.getSize(); i++){
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

			// Limpa a tela
			SDL_RenderClear(this->g_renderer);

			SDL_Rect bg_quad; 
			bg_quad.x = this->window_size.x / 2 - 1350;
			bg_quad.y = this->window_size.y / 2 - 1240;
			bg_quad.w = 3198;
			bg_quad.h = 2800;
			SDL_RenderCopy(this->g_renderer, this->g_bg, NULL, &bg_quad);
			
			if (this->tela_id == 1) {
				this->tela_id = 2;
			}

			/*if (this->mouse_pressed)
				for (int i = 0; i < this->fila.getSize(); i++)
					this->fila[i]->applyForce(this->fila[i]->arrive(new GeoA::Vetor()));*/
			
			this->updateFilaPos();

			for (int i = this->fila.getSize() - 1; i >= 0; i--)
				this->fila[i]->update()->render();

			if (this->tela_id == 2) {
				this->fila[0]->cart.pos = GeoA::Vetor(this->window_size.x*2/3, this->window_size.y*2/3, 0);
				this->fila[0]->cart.update()->render();
			}

			SDL_RenderPresent(this->g_renderer);
			this->limitFPS();

			return !this->game_quit;
		}

		Cara_cracha* updateFilaPos() {
			this->fila_pos.clear();

			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 11, this->window_size.y*0.5 + 160, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 128, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 + 96, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 64, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 + 32, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 203, this->window_size.y*0.5 + 64, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 0, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 203, this->window_size.y*0.5 + 0, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 267, this->window_size.y*0.5 + 32, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 - 32, 0));

			for (int i = 0; i < this->fila.getSize(); i++)
				this->fila[i]->pos = this->fila_pos[i];

			return this;
		}

		Cara_cracha* play() {

			for (int i = 0; i < this->fila.getSize(); i++) {

				this->fila[i]->render();
			
			}

			return this;

		}

		Cara_cracha* limitFPS() {
			this->curr_fr = SDL_GetTicks();
			int sleep = this->last_fr + this->max_fps - this->curr_fr;
			if (sleep > 0)
				SDL_Delay(sleep);
			this->last_fr = this->curr_fr;

			return this;
		}
};

#endif
