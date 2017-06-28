#ifndef CARTEIRINHA_H
#define CARTEIRINHA_H

#include "GeoA.h"
#include "Textura.h"

class Carteirinha {
	Textura t_fundo;
	Textura t_rosto;
	Textura t_oculos;
	Textura t_cabelo;
	Textura t_barba;

	public:
		GeoA::Vetor pos;
		bool sexo;
		int rosto;
		int cor_do_rosto;
		int oculos;
		int cor_do_oculos;
		int cabelo;
		int cor_do_cabelo;
		int barba;
		int cor_da_barba;
		
		Carteirinha();
		Carteirinha(bool, int, int, int, int, int, int, int, int);
		
		void initTextures(SDL_Renderer*);
		void render();
};

Carteirinha::Carteirinha() {
	
	this->sexo = GeoA::random() > 0.5;

	this->rosto = GeoA::random(1, 4);
	this->cor_do_rosto = GeoA::random(1, 4);
	this->oculos = GeoA::random(1, 4);
	this->cor_do_oculos = GeoA::random(1, 4);
	this->cabelo = GeoA::random(1, 4);
	this->cor_do_cabelo = GeoA::random(1, 4);
	this->barba = GeoA::random(1, 4);
	this->cor_da_barba = GeoA::random(1, 4);

}

Carteirinha::Carteirinha(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pb, int pcb):sexo(ps), rosto(pr), cor_do_rosto(pcr), oculos(po), cor_do_oculos(pco), cabelo(pc), cor_do_cabelo(pcc), barba(pb), cor_da_barba(pcb) {

}

void Carteirinha::initTextures(SDL_Renderer* renderer) {
	string path_imgs = "../media/img/";
	
	string path_fundo = path_imgs+"fundo_cart.png";
	this->t_fundo = Textura(path_fundo, renderer, this->pos.x, this->pos.y, 300, 200);
}

void Carteirinha::render() {
	this->initTextures(this->t_fundo.getRenderer());

	this->t_fundo.render();
}

#endif