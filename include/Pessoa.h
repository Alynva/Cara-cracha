#ifndef PESSOA_H
#define PESSOA_H

#include "Carteirinha.h"

#define CHANCE_N_OCULOS 0.75 // Chance da pessoa não possuir óculos
#define CHANCE_N_BARBA 0.8 // Chance da pessoa não possuir barba
#define CHANCE_CART_DIF 0.5 // Chance da carteirinha ser de uma pessoa diferente

class Pessoa {

	public:
		GeoA::Vetor pos;
		GeoA::Vetor target;
		GeoA::Vetor vel;
		GeoA::Vetor acc;
		double max_speed;
		double max_force;

		int direcao;

		bool sexo;
		int olhos;
		int cor_do_rosto;
		//int oculos;
		//int cor_do_oculos;
		int cabelo;
		int cor_do_cabelo;
		//int barba;
		//int cor_da_barba;
		int blusa;
		int cor_da_blusa;
		int calca;
		int cor_da_calca;
		int tenis;
		int cor_do_tenis;

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
		Textura t_calca;
		Textura t_tenis;
		
		Carteirinha cart;

		static Textura tex;
		
		Pessoa();
		Pessoa(bool, int, /*int, int, */int, int, int, int, /*int, int, */int, int, int, int, int);

		Pessoa* initTextures(SDL_Renderer*);
		Pessoa* update();
		Pessoa* updateTexPos();

		Pessoa* applyForce(const GeoA::Vetor*);
		Pessoa* behaviors();
		GeoA::Vetor* arrive(const GeoA::Vetor*);

		Pessoa* render();
};

#endif