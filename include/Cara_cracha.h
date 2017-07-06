#ifndef CARA_CRACHA
#define CARA_CRACHA

#include "EventManager.h"
#include "Texto.h"

#define EXPEDIENTE_ALMO_INICIO 660
#define EXPEDIENTE_ALMO_FIM 840
#define EXPEDIENTE_JANT_INICIO 1020
#define EXPEDIENTE_JANT_FIM 1140

class Cara_cracha {
	SDL_Window* g_window;		// Janela principal
	SDL_Rect window_pos_size;	// Tamanho da janela
	SDL_Renderer* g_renderer;	// Renderizador principal
	bool game_quit;				// Responsavel pelo loop principal
	EventManager event;			// Eventos

	int tela_id;
		// tela_id == 0 (inicial/instruções)
		// tela_id == 1 (jogo rodando, sem ver carteirinha)
		// tela_id == 2 (jogo rodando, vendo carteirinha)
		// tela_id == 3 (fim de jogo, game over)
		// tela_id == 4 (jogo pausado)

	short int max_fps;
	unsigned int curr_fr;
	unsigned int last_fr;

	double hora;
	Texto t_hora;
	Texto t_dia;
	std::string dias_semana[7];

	int count_criterios[4];
	Texto t_count_criterios[4];
	int pontua_prov;
	Texto t_pontua_prov;
	Texto t_pontua_fin;

	Queue<SDL_Texture*> g_bg;	// Plano de fundo
	SDL_Rect bg_quad;			// Retângulo do plano de fundo
	Objeto infos;

	Queue<GeoA::Vetor> fila_pos;
	Queue<Pessoa*> fila_dentro;
	Queue<Pessoa*> fila_fora;
	Pessoa player;
	Objeto catraca;

	Texto t_instrucoes[13];
	Texto t_jogo_pausado;
	Texto t_controles[3];
	Objeto o_controles[2];
	Texto t_tela_fin[3];


	double convertM2H(double);

	bool initSDL();
	Cara_cracha* initVars();
	Cara_cracha* initInstrucoes();
	Cara_cracha* initInfos();
	Cara_cracha* initBg();

	Cara_cracha* incrementaHora();
	Cara_cracha* checaFimDeJogo();
	Cara_cracha* updateFilaSize();
	bool entraAlguem();
	Cara_cracha* updateFilaPos();
	Cara_cracha* renderizaNoite();
	Cara_cracha* telasForaJogo();
	Cara_cracha* limitFPS();

	public:

		Cara_cracha();
		~Cara_cracha();

		bool init();
		bool update();
		Cara_cracha* render();
};

#endif