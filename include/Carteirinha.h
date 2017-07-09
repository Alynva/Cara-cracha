#ifndef CARTEIRINHA_H
#define CARTEIRINHA_H

#include "GeoA.h"
#include "Textura.h"

class Carteirinha {
	Textura t_fundo_t;
	Textura t_fundo_f;

	Textura t_corpo;
	Textura t_braco_e;
	Textura t_braco_d;
	Textura t_cabeca;
	Textura t_nariz_boca;
	Textura t_olhos;
	//Textura t_oculos;
	Textura t_cabelo;
	//Textura t_barba;
	Textura t_blusa;
	Textura t_blusa_b_e;
	Textura t_blusa_b_d;

	static Textura tex;

	public:
		GeoA::Vetor pos;
		bool sexo;
		int olhos;
		int cor_do_rosto;
		int cabelo;
		int cor_do_cabelo;
		//int barba;
		//int cor_da_barba;
		int blusa;
		int cor_da_blusa;
		
		Carteirinha();
		Carteirinha(bool, int, int, int);
		
		void initTextures(SDL_Renderer*);
		Carteirinha* update();
		Carteirinha* updateTexPos();
		void render();
};

#endif