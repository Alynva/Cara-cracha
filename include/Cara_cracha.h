#ifndef CARA_CRACHA
#define CARA_CRACHA

#include "EventManager.h"
#include "get_fill_size.hpp"
#include "Texto.h"

class Cara_cracha {
	SDL_Window* g_window; // Janela principal
	SDL_Point window_size; // Tamanho da janela
	SDL_Renderer* g_renderer; // Renderizador principal
	Queue<SDL_Texture*> g_bg; // Plano de fundo
	bool game_quit; // Responsavel pelo loop principal
	bool game_play; // Respons�vel por come�ar o jogo
	EventManager event; // Eventos
	bool mouse_pressed;

	short int max_fps;
	unsigned int curr_fr;
	unsigned int last_fr;

	double hora;
	Texto t_hora;
	int dia;
	Texto t_dia;
	Objeto janela;

	public:
		int tela_id;
		Pessoa player;
		Queue<Pessoa*> fila;
		Queue<GeoA::Vetor> fila_pos;
		Objeto catraca;

		Cara_cracha():
			g_window(NULL),
			g_renderer(NULL),
			game_quit(false),
			game_play(false),
			event(&this->game_quit, &this->game_play, &this->mouse_pressed, &this->window_size, &tela_id, &fila, &this->catraca.estado),
			mouse_pressed(false),
			max_fps(60),
			curr_fr(0),
			last_fr(0),
			hora(630),
			dia(1),
			tela_id(0),
			player(Pessoa(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
		};

		~Cara_cracha() {
			SDL_DestroyRenderer(this->g_renderer);
			SDL_DestroyWindow(this->g_window);
			this->g_renderer = NULL;
			this->g_window = NULL;

			IMG_Quit();
			TTF_Quit();
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

					if(TTF_Init() == -1) {
						SDL_Log("TTF_Init: %s\n", TTF_GetError());
						return false;
					}

					// Do samething....
					this->event.update();

					this->janela.pos = GeoA::Vetor(50, 50, 0);
					this->janela.tex_fundo_0 = Textura("../media/img/box.png", this->g_renderer, this->janela.pos.x, this->janela.pos.y, 213, 191);

					this->t_hora = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 25, {250, 82, 0, 0}, {0, 0, 0}, std::to_string(this->hora));
					this->t_hora.setAncora(1);
					this->t_dia = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 25, {62, 82, 0, 0}, {0, 0, 0}, "Dia "+std::to_string(this->dia));
					this->t_dia.setAncora(-1);


					SDL_Texture* tx_temp = SDL_CreateTextureFromSurface(this->g_renderer, IMG_Load("../media/img/background (fundo).png"));
					if (tx_temp == NULL) {
						SDL_Log("Erro Img: %s", SDL_GetError());
					}
					this->g_bg.enqueue(tx_temp);
					tx_temp = SDL_CreateTextureFromSurface(this->g_renderer, IMG_Load("../media/img/background (frente).png"));
					if (tx_temp == NULL) {
						SDL_Log("Erro Img: %s", SDL_GetError());
					}
					this->g_bg.enqueue(tx_temp);


					player.pos = GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 192, 0);
					player.initTextures(this->g_renderer);
					SDL_SetTextureColorMod(player.t_corpo.getTexture(), 0, 255, 0);


					for (int i = 0; i < 10; i++){
						this->fila.enqueue(new Pessoa());
					}

					this->updateFilaPos();

					for (int i = 0; i < this->fila.getSize(); i++){
						this->fila[i]->initTextures(this->g_renderer)->pos = GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 - 32, 0);
					}

					this->catraca.pos = GeoA::Vetor(this->window_size.x*0.5 - 16, this->window_size.y*0.5 + 52, 0);
					this->catraca.estado = 0;
					this->catraca.tex_fundo_0 = Textura("../media/img/sentido_unico (tras).png", this->g_renderer, this->catraca.pos.x, this->catraca.pos.y, 148, 160);
					this->catraca.tex_fundo_1 = Textura("../media/img/sentido_unico (aberto).png", this->g_renderer, this->catraca.pos.x, this->catraca.pos.y, 148, 160);
					this->catraca.tex_frente = Textura("../media/img/sentido_unico (frente).png", this->g_renderer, this->catraca.pos.x, this->catraca.pos.y, 148, 160);

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


			// Calcula posição do fundo
			SDL_Rect bg_quad; 
			bg_quad.x = this->window_size.x / 2 - 1350;
			bg_quad.y = this->window_size.y / 2 - 1240;
			bg_quad.w = 3198;
			bg_quad.h = 2800;

			// Renderiza o fundo
			SDL_RenderCopy(this->g_renderer, this->g_bg[0], NULL, &bg_quad);


			// Renderiza a catraca
			if (this->catraca.estado == 0)
				this->catraca.tex_fundo_0.render();
			else
				this->catraca.tex_fundo_1.render();

			//Animação da catraca
			if (this->catraca.estado > 0.05) this->catraca.estado -= 0.05;
			else this->catraca.estado = 0;

			
			// Atualiza a posição das pessoas que estão na fila
			this->updateFilaPos();

			// Atualiza e renderiza as pessoas
			for (int i = this->fila.getSize() - 1; i >= 0; i--)
				this->fila[i]->behaviors()->update()->render();

			// Renderiza a carteirinha
			if (this->tela_id == 2) {
				this->fila[0]->cart.pos = GeoA::Vetor(this->window_size.x*2/3, this->window_size.y*2/3, 0);
				this->fila[0]->cart.update()->render();
			}


			// Renderiza o jogador
			player.update()->render();


			// Renderiza a parte da frente da catraca
			this->catraca.tex_frente.render();


			// Renderiza os itens do cenário que podem estar na frente das pessoas
			SDL_RenderCopy(this->g_renderer, this->g_bg[1], NULL, &bg_quad);


			// Altera e renderiza o dia e hora
			this->janela.tex_fundo_0.render();
			if (this->hora >= 1440) {
				this->dia++;
				this->t_dia.setText("Dia "+std::to_string(this->dia));
			}
			this->t_dia.render();
			this->hora = (this->hora >= 1440 ? 0 : this->hora + (((this->hora > 660 && this->hora < 840) || (this->hora > 1020 && this->hora < 1140)) ? 0.1 : 0.5));
			this->t_hora.setText(((int) this->hora / 60 >= 10 ? "" : "0")+std::to_string((int) this->hora/60)+((int) this->hora % 60 >= 10 ? ":" : ":0")+std::to_string((int) this->hora % 60));
			this->t_hora.render();

			SDL_RenderPresent(this->g_renderer);
			// Aplica o delay necessário para manter a 60fps
			this->limitFPS();

			return !this->game_quit;
		}

		Cara_cracha* updateFilaPos() {
			//this->fila_pos.clear();

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
				this->fila[i]->target = this->fila_pos[i];

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
