#ifndef CARA_CRACHA
#define CARA_CRACHA

#include "EventManager.h"
#include "get_fill_size.hpp"
#include "Texto.h"

#define EXPEDIENTE_ALMO_INICIO 660
#define EXPEDIENTE_ALMO_FIM 840
#define EXPEDIENTE_JANT_INICIO 1020
#define EXPEDIENTE_JANT_FIM 1140

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
	Texto t_dia;
	Objeto janela;

	public:
		int tela_id;
		Pessoa player;
		Queue<Pessoa*> fila_dentro;
		Queue<Pessoa*> fila_fora;
		Queue<GeoA::Vetor> fila_pos;
		Objeto catraca;

		Cara_cracha():
			g_window(NULL),
			g_renderer(NULL),
			game_quit(false),
			game_play(false),
			event(&this->game_quit, &this->game_play, &this->mouse_pressed, &this->window_size, &tela_id, &fila_dentro, &this->catraca.estado),
			mouse_pressed(false),
			max_fps(60),
			curr_fr(0),
			last_fr(0),
			hora(630),
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
					this->janela.tex_fundo_0 = Textura("../media/img/box.png", this->g_renderer, this->janela.pos.x, this->janela.pos.y, 213, 350);

					this->t_hora = Texto("../media/font/Volter_Goldfish.ttf", this->g_renderer, 31, {255, 82, 0, 0}, {0, 0, 0}, std::to_string(this->hora));
					this->t_hora.setAncora(1);
					this->t_dia = Texto("../media/font/Volter_Goldfish.ttf", this->g_renderer, 17, {62, 82, 0, 0}, {0, 0, 0}, "Dia "+std::to_string(this->hora));
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
					tx_temp = SDL_CreateTextureFromSurface(this->g_renderer, IMG_Load("../media/img/background (frente)(porta).png"));
					if (tx_temp == NULL) {
						SDL_Log("Erro Img: %s", SDL_GetError());
					}
					this->g_bg.enqueue(tx_temp);
					tx_temp = SDL_CreateTextureFromSurface(this->g_renderer, IMG_Load("../media/img/background (frente)(catraca).png"));
					if (tx_temp == NULL) {
						SDL_Log("Erro Img: %s", SDL_GetError());
					}
					this->g_bg.enqueue(tx_temp);


					player.pos = GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 192, 0);
					player.initTextures(this->g_renderer);
					SDL_SetTextureColorMod(player.t_corpo.getTexture(), 241, 214, 147);


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

			
			// Atualiza quantidade de pessoas na fila
			this->updateFilaSize();
			// Atualiza a posição das pessoas que estão na fila
			this->updateFilaPos();

			// Atualiza e renderiza as pessoas de fora
			for (int i = this->fila_fora.getSize() - 1; i >= 0; i--)
				this->fila_fora[i]->behaviors()->update()->render();

			// Renderiza a carteirinha
			if (this->tela_id == 2 && this->fila_dentro.getSize()) {
				this->fila_dentro[0]->cart.pos = GeoA::Vetor(this->window_size.x*2/3, this->window_size.y*2/3, 0);
				this->fila_dentro[0]->cart.update()->render();
			}


			// Renderiza a parte da frente da catraca
			this->catraca.tex_frente.render();


			// Renderiza a porta de vidro
			if (((int)this->hora % 1440 < EXPEDIENTE_ALMO_INICIO || (int)this->hora % 1440 > EXPEDIENTE_JANT_FIM) ||
				 ((int)this->hora % 1440 > EXPEDIENTE_ALMO_FIM && (int)this->hora % 1440 < EXPEDIENTE_JANT_INICIO))
				SDL_RenderCopy(this->g_renderer, this->g_bg[2], NULL, &bg_quad);


			// Atualiza e renderiza as pessoas de dentro
			for (int i = this->fila_dentro.getSize() - 1; i >= 0; i--)
				this->fila_dentro[i]->behaviors()->update()->render();


			// Renderiza os itens do cenário que podem estar na frente das pessoas
			SDL_RenderCopy(this->g_renderer, this->g_bg[1], NULL, &bg_quad);


			// Renderiza o jogador
			player.update()->render();


			// Renderiza cenário da parte da catraca
			SDL_RenderCopy(this->g_renderer, this->g_bg[3], NULL, &bg_quad);


			// Altera e renderiza o dia e hora
			this->janela.tex_fundo_0.render();
			this->t_dia.setText("Dia "+std::to_string((int)(this->hora / 60) / 24 + 1));
			this->t_dia.render();
			this->hora = this->hora + (((int)this->hora % 1440 > EXPEDIENTE_ALMO_INICIO && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM) ||				 ((int)this->hora % 1440 > EXPEDIENTE_JANT_INICIO && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM) ? 0.1 : 0.5);
			this->t_hora.setText(((int)(this->hora / 60) % 24 >= 10 ? "" : "0")+std::to_string((int)(this->hora/60) % 24)+((int) this->hora % 60 >= 10 ? ":" : ":0")+std::to_string((int) this->hora % 60));
			this->t_hora.render();

			SDL_RenderPresent(this->g_renderer);
			// Aplica o delay necessário para manter a 60fps
			this->limitFPS();

			return !this->game_quit;
		}

		Cara_cracha* updateFilaPos() {
			this->fila_pos.clear();

			if 	(((int)this->hora % 1440 > EXPEDIENTE_ALMO_INICIO && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM + 60) || // 11:00 ~ 15:00
				 ((int)this->hora % 1440 > EXPEDIENTE_JANT_INICIO && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM + 60)) { // 17:00 ~ 20:00
				this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 11, this->window_size.y*0.5 + 160, 0));
				this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 128, 0));
			}
			if 	(((int)this->hora % 1440 > EXPEDIENTE_ALMO_INICIO && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM) || // 11:00 ~ 14:00
				 ((int)this->hora % 1440 > EXPEDIENTE_JANT_INICIO && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM)) { // 17:00 ~ 19:00
				this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 + 96, 0));
				this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 64, 0));
			}
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 + 32, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 203, this->window_size.y*0.5 + 64, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 75, this->window_size.y*0.5 + 0, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 203, this->window_size.y*0.5 + 0, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 267, this->window_size.y*0.5 + 32, 0));
			this->fila_pos.enqueue(GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 - 32, 0));

			Pessoa* pessoa_temp;
			if 	(((int)this->hora % 1440 > EXPEDIENTE_ALMO_INICIO && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM) || // 11:00 ~ 14:00
				 ((int)this->hora % 1440 > EXPEDIENTE_JANT_INICIO && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM)) { // 17:00 ~ 19:00
				while (this->fila_dentro.getSize() < 2 && this->fila_fora.getSize()) {
					this->fila_fora.dequeue(pessoa_temp);
					this->fila_dentro.enqueue(pessoa_temp);
				}
			} else if (((int)this->hora % 1440 >= EXPEDIENTE_JANT_FIM + 60) || // 19:30 ~ 10:30
					   ((int)this->hora % 1440 >= EXPEDIENTE_ALMO_FIM + 60 && (int)this->hora % 1440 < EXPEDIENTE_JANT_INICIO)) { // 14:30 ~ 16:30
				while (this->fila_dentro.getSize()) {
					this->fila_dentro.dequeue(pessoa_temp);
					this->fila_fora.enqueue(pessoa_temp);
				}
			}
			pessoa_temp = nullptr;

			for (int i = 0; i < this->fila_dentro.getSize(); i++) {
				this->fila_dentro[i]->target = this->fila_pos[i];
			}
			for (int i = 0; i < this->fila_fora.getSize(); i++) {
				this->fila_fora[i]->target = this->fila_pos[i+2];
			}

			return this;
		}

		double convertM2H(double minute) {
			return ((int)(minute / 60) % 24) + GeoA::map((int)minute % 60, 0, 60, 0, 1);
		}

		bool entraAlguem() {
			double comeca_almo, para_almo, a_almo, b_almo, c_almo, comeca_jant, para_jant, a_jant, b_jant, c_jant, x;

			x = this->convertM2H(this->hora);

			comeca_almo = this->convertM2H(EXPEDIENTE_ALMO_INICIO - 60);
			para_almo	= this->convertM2H(EXPEDIENTE_ALMO_FIM - 30);
			comeca_jant = this->convertM2H(EXPEDIENTE_JANT_INICIO);
			para_jant	= this->convertM2H(EXPEDIENTE_JANT_FIM - 30);

			a_almo		= -1;
			b_almo		= comeca_almo + para_almo;
			c_almo		= comeca_almo * para_almo * -1;

			a_jant		= -1;
			b_jant		= comeca_jant + para_jant;
			c_jant		= comeca_jant * para_jant * -1;

			return GeoA::random(100) < (a_almo*x*x + b_almo*x + c_almo) || GeoA::random(100) < (a_jant*x*x + b_jant*x + c_jant) * 3;
		}

		Cara_cracha* updateFilaSize() {
			

			if 	(((int)this->hora % 1440 > EXPEDIENTE_ALMO_INICIO - 30 && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM) || // 10:30 ~ 14:00
				 ((int)this->hora % 1440 > EXPEDIENTE_JANT_INICIO && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM)) { // 17:00 ~ 19:00
				if 	(this->entraAlguem()) {
					this->fila_fora.enqueue(new Pessoa());
					this->fila_fora[this->fila_fora.getSize()-1]->initTextures(this->g_renderer)->pos = GeoA::Vetor(this->window_size.x*0.5 - 139, this->window_size.y*0.5 - 32, 0);
				}
			} else {
				/*Queue<Pessoa*> fila_temp;
				Pessoa *pessoa_temp, *temp;

				if (((int)this->hora % 1440 >= EXPEDIENTE_ALMO_FIM + 30 && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM + 90) || // 14:30 ~ 15:30
					((int)this->hora % 1440 >= EXPEDIENTE_JANT_FIM + 30 && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM + 90)) { // 19:30 ~ 20:30
					if (this->fila.getSize()) {
						this->fila.dequeue(pessoa_temp);
						fila_temp.enqueue(pessoa_temp);
					}
					if (this->fila.getSize()) {
						this->fila.dequeue(pessoa_temp);
						fila_temp.enqueue(pessoa_temp);
					}
				}*/
				
				if (((int)this->hora % 1440 < EXPEDIENTE_ALMO_INICIO - 60 || (int)this->hora % 1440 >= EXPEDIENTE_JANT_FIM + 30) || // 19:30 ~ 10:30
					((int)this->hora % 1440 >= EXPEDIENTE_ALMO_FIM + 30 && (int)this->hora % 1440 < EXPEDIENTE_JANT_INICIO)) // 14:30 ~ 16:30
					this->fila_fora.clear();

				/*if (((int)this->hora % 1440 >= EXPEDIENTE_ALMO_FIM + 30 && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM + 90) || // 14:30 ~ 15:30
					((int)this->hora % 1440 >= EXPEDIENTE_JANT_FIM + 30 && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM + 90)) { // 19:30 ~ 20:30
					if (this->fila.getSize()) {
						fila_temp.dequeue(pessoa_temp);
						this->fila.enqueue(pessoa_temp);
					}
					if (this->fila.getSize()) {
						fila_temp.dequeue(pessoa_temp);
						this->fila.enqueue(pessoa_temp);
					}
				}
				
				pessoa_temp = temp = nullptr;*/
			}

			return this;
		}

		Cara_cracha* play() {

			/*for (int i = 0; i < this->fila.getSize(); i++) {

				this->fila[i]->render();
			
			}*/

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
