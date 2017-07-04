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
			// tela_id == 0 (inicial/instruções)
			// tela_id == 1 (jogo rodando, sem ver carteirinha)
			// tela_id == 2 (jogo rodando, vendo carteirinha)
			// tela_id == 3 (fim de jogo, game over)
			// tela_id == 4 (jogo pausado)
		int tela_id;
		Pessoa player;
		Queue<Pessoa*> fila_dentro;
		Queue<Pessoa*> fila_fora;
		Queue<GeoA::Vetor> fila_pos;
		Objeto catraca;
		int count_criterios[4];
		Texto t_count_criterios[4];
		int pontua_prov;
		Texto t_pontua_prov;

		Texto t_instrucoes[12];
		Texto t_jogo_pausado;

		Cara_cracha():
			g_window(NULL),
			g_renderer(NULL),
			game_quit(false),
			game_play(false),
			event(&this->game_quit, &this->game_play, &this->mouse_pressed, &tela_id, &fila_dentro, &this->catraca.estado, count_criterios),
			mouse_pressed(false),
			max_fps(60),
			curr_fr(0),
			last_fr(0),
			hora(540),
			tela_id(0),
			player(Pessoa(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)),
			pontua_prov(0) {
				for (int i = 0; i < 4; i++) {
					this->count_criterios[i] = 0;
				}
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
					SDL_SetRenderDrawColor(this->g_renderer, 0, 0, 0, 255);

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


					SDL_GetWindowSize(this->g_window, &this->window_size.x, &this->window_size.y);


					this->t_instrucoes[0] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 50, {this->window_size.x/2, this->window_size.y/2 - 250, 0, 0}, {220, 220, 220}, "Instruções");

					// Aqui você é um estagiário de um restaurante, situado em uma universidade federal, o qual está passando por uma crise ética das pessoas que o utilizam. Algumas delas estão utilizando cartões de acesso doutras pessoas, por n motivos. Você foi encarregado de verificar TODOS aqueles que quiserem utilizar o restaurante. Exiga que entreguem os cartões de acesso caso necessário, tenha certeza que só entrará aqueles que possuírem seus próprios cartões de acesso. Você estará sendo monitorado a todo instante, olhe atentamente à foto presente no cartão de acesso. Porém, você precisa ser rápido. Não deixe que a fila se acomule. Seu expediente é das 11:00 às 14:00 e das 17:00 às 19:00. 

					this->t_instrucoes[1] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 - 100, 0, 0}, {220, 220, 220}, "Aqui você é um estagiário de um restaurante, situado em uma universidade federal,");
					this->t_instrucoes[2] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 - 80, 0, 0}, {220, 220, 220}, "o qual está passando por uma crise ética das pessoas que o utilizam. Algumas delas");
					this->t_instrucoes[3] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 - 60, 0, 0}, {220, 220, 220}, "estão utilizando cartões de acesso doutras pessoas, por n motivos. Você foi encar-");
					this->t_instrucoes[4] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 - 40, 0, 0}, {220, 220, 220}, "regado de verificar TODOS aqueles que quiserem utilizar o restaurante. Exija que");
					this->t_instrucoes[5] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 - 20, 0, 0}, {220, 220, 220}, "entreguem os cartões de acesso caso necessário, tenha certeza que só entrará a-");
					this->t_instrucoes[6] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2, 0, 0}, {220, 220, 220}, "queles que possuírem seus próprios cartões de acesso. Você estará sendo monito-");
					this->t_instrucoes[7] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 + 20, 0, 0}, {220, 220, 220}, "rado a todo instante, olhe atentamente à foto presente no cartão de acesso. Po-");
					this->t_instrucoes[8] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 + 40, 0, 0}, {220, 220, 220}, "rém, você precisa ser rápido. Não deixe que a fila se acumule. Seu expediente é das");
					this->t_instrucoes[9] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y/2 + 60, 0, 0}, {220, 220, 220}, "11:00 às 14:00 e das 17:00 às 19:00.");

					this->t_instrucoes[10] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {20, this->window_size.y - 40, 0, 0}, {220, 220, 220}, "Precione ENTER para começar");
					this->t_instrucoes[10].setAncora(-1);
					this->t_instrucoes[11] = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x - 20, this->window_size.y - 40, 0, 0}, {220, 220, 220}, "Durante o jogo, precione ESC para pausar/retornar");
					this->t_instrucoes[11].setAncora(1);


					this->t_jogo_pausado = Texto("../media/font/Ubuntu-R.ttf", this->g_renderer, 18, {this->window_size.x/2, this->window_size.y - 20, 0, 0}, {220, 220, 220}, "Jogo pausado");


					this->janela.pos = GeoA::Vetor(50, 50, 0);
					this->janela.tex_fundo_0 = Textura("../media/img/box.png", this->g_renderer, this->janela.pos.x, this->janela.pos.y, 213, 350);

					this->t_hora = Texto("../media/font/Volter_Goldfish.ttf", this->g_renderer, 31, {254, 82, 0, 0}, {0, 0, 0}, ((int)(this->hora / 60) % 24 >= 10 ? "" : "0")+std::to_string((int)(this->hora/60) % 24)+((int) this->hora % 60 >= 10 ? ":" : ":0")+std::to_string((int) this->hora % 60));
					this->t_hora.setAncora(1);
					this->t_dia = Texto("../media/font/Volter_Goldfish.ttf", this->g_renderer, 17, {64, 82, 0, 0}, {0, 0, 0}, "Dia "+std::to_string((int)(this->hora / 60) / 24 + 1));
					this->t_dia.setAncora(-1);


					for (int i = 0; i < 4; i++) {
						this->t_count_criterios[i] = Texto("../media/font/Volter_Goldfish.ttf", this->g_renderer, 21, {251, 140 + 50*i, 0 , 0}, {0, 0, 0}, std::to_string(this->count_criterios[i]));
						this->t_count_criterios[i].setAncora(1);
					}

					this->t_pontua_prov = Texto("../media/font/Volter_Goldfish.ttf", this->g_renderer, 28, {210, 363, 0, 0}, {0, 0, 0}, std::to_string(this->pontua_prov));


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

					//this->tela_id = 1;

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

			if (this->tela_id == 1 || this->tela_id == 2) {
				//Animação da catraca
				if (this->catraca.estado > 0.05) this->catraca.estado -= 0.05;
				else this->catraca.estado = 0;
			}

			
			if (this->tela_id == 1 || this->tela_id == 2) {
				// Atualiza quantidade de pessoas na fila
				this->updateFilaSize();
				// Atualiza a posição das pessoas que estão na fila
				this->updateFilaPos();
			}

			if (this->tela_id == 1 || this->tela_id == 2) {
				// Atualiza as pessoas de fora
				for (int i = this->fila_fora.getSize() - 1; i >= 0; i--)
					this->fila_fora[i]->behaviors()->update();
			}
			// Renderiza as pessoas de fora
			for (int i = this->fila_fora.getSize() - 1; i >= 0; i--)
					this->fila_fora[i]->render();

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


			if (this->tela_id == 1 || this->tela_id == 2) {
				// Atualiza as pessoas de dentro
				for (int i = this->fila_dentro.getSize() - 1; i >= 0; i--)
					this->fila_dentro[i]->behaviors()->update();
			}
			// Renderiza as pessoas de dentro
			for (int i = this->fila_dentro.getSize() - 1; i >= 0; i--)
				this->fila_dentro[i]->render();


			// Renderiza os itens do cenário que podem estar na frente das pessoas
			SDL_RenderCopy(this->g_renderer, this->g_bg[1], NULL, &bg_quad);


			// Renderiza o jogador
			player.update()->render();


			// Renderiza cenário da parte da catraca
			SDL_RenderCopy(this->g_renderer, this->g_bg[3], NULL, &bg_quad);


			// Altera e renderiza o dia, a hora e os pontos
			this->janela.tex_fundo_0.render();

			if (this->tela_id == 1 || this->tela_id == 2) {
				// Atualiza o texto do dia
				this->t_dia.setText("Dia "+std::to_string((int)(this->hora / 60) / 24 + 1));

				// Incrementa a hora
				if (((int)this->hora % 1440 > EXPEDIENTE_ALMO_INICIO && (int)this->hora % 1440 < EXPEDIENTE_ALMO_FIM) || ((int)this->hora % 1440 > EXPEDIENTE_JANT_INICIO && (int)this->hora % 1440 < EXPEDIENTE_JANT_FIM))
					this->hora = this->hora + 0.1;
				else if ((int)this->hora % 1440 > EXPEDIENTE_ALMO_FIM && (int)this->hora % 1440 < EXPEDIENTE_JANT_INICIO)
					this->hora = this->hora + 0.5;
				else
					this->hora = this->hora + 1;
				// Atualiza o texto da hora incrementada
				this->t_hora.setText(((int)(this->hora / 60) % 24 >= 10 ? "" : "0")+std::to_string((int)(this->hora/60) % 24)+((int) this->hora % 60 >= 10 ? ":" : ":0")+std::to_string((int) this->hora % 60));

				// Atualiza os contadores de critérios para pontos
				for (int i = 0; i < 4; i++)
					this->t_count_criterios[i].setText(std::to_string(this->count_criterios[i]));

				// Atualiza a pontuação provisória
				this->pontua_prov = this->count_criterios[0]*10 + this->count_criterios[1]*-20 + this->count_criterios[2]*-10 + this->count_criterios[3]*5;
				this->t_pontua_prov.setText(std::to_string(this->pontua_prov));
			}
			// Renderiza o texto do dia
			this->t_dia.render();
			// Renderiza o texto da hora
			this->t_hora.render();

			// Renderiza os contadores de critérios para pontos
			for (int i = 0; i < 4; i++)
				this->t_count_criterios[i].render();
			// Renderiza a pontuação provisória
			this->t_pontua_prov.render();


			if (this->tela_id == 0 || this->tela_id == 3 || this->tela_id == 4) { // Renderiza o retângulo opaco
				SDL_SetRenderDrawBlendMode(this->g_renderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(this->g_renderer, 0, 0, 0, 200);
				SDL_Rect rectangle;
				rectangle.x = rectangle.y = 0;
				rectangle.w = this->window_size.x;
				rectangle.h = this->window_size.y;
				SDL_RenderFillRect(this->g_renderer, &rectangle);
				SDL_SetRenderDrawBlendMode(this->g_renderer, SDL_BLENDMODE_NONE);

				switch (this->tela_id) {
					case 0: // Renderiza as instruções
					for (int i = 0 ; i < 12; i++)
						this->t_instrucoes[i].render();
					break;
					case 3: // Renderiza a tela de fim de jogo
					break;
					case 4: // Renderiza mensagem "PAUSADO"
					this->t_jogo_pausado.render();
					break;
				}
			}


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
				
				if (((int)this->hora % 1440 < EXPEDIENTE_ALMO_INICIO - 60 || (int)this->hora % 1440 >= EXPEDIENTE_JANT_FIM + 30) || // 19:30 ~ 10:30
					((int)this->hora % 1440 >= EXPEDIENTE_ALMO_FIM + 30 && (int)this->hora % 1440 < EXPEDIENTE_JANT_INICIO)) // 14:30 ~ 16:30
					this->fila_fora.clear();
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
