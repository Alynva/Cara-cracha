#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include "Carteirinha.h"

class Pessoa {
	Textura t_rosto;
	Textura t_oculos;
	Textura t_cabelo;
	Textura t_barba;
	Textura t_corpo;
	Textura t_blusa;
	Textura t_calca;
	Textura t_tenis;

	public:
		GeoA::Vetor pos;
		GeoA::Vetor target;
		GeoA::Vetor vel;
		GeoA::Vetor acc;
		double max_speed;
		double max_force;

		bool sexo;
		int rosto;
		int cor_do_rosto;
		int oculos;
		int cor_do_oculos;
		int cabelo;
		int cor_do_cabelo;
		int barba;
		int cor_da_barba;
		int blusa;
		int cor_da_blusa;
		int calca;
		int cor_da_calca;
		int tenis;
		int cor_do_tenis;
		Carteirinha cart;
		
		Pessoa();
		Pessoa(bool, int, int, int, int, int, int, int, int, int, int, int, int, int, int);

		void initTextures(SDL_Renderer*);
		Pessoa* update();

		Pessoa* applyForce(const GeoA::Vetor*);
		GeoA::Vetor* arrive(const GeoA::Vetor*);

		Pessoa* render();
};

Pessoa::Pessoa() {
	this->pos = GeoA::Vetor(GeoA::random(0, 1000), GeoA::random(0, 700), 0);

	this->sexo = GeoA::random() > 0.5;

	this->rosto = GeoA::random(1, 4);
	this->cor_do_rosto = GeoA::random(1, 4);
	this->oculos = GeoA::random(1, 4);
	this->cor_do_oculos = GeoA::random(1, 4);
	this->cabelo = GeoA::random(1, 4);
	this->cor_do_cabelo = GeoA::random(1, 4);
	this->barba = GeoA::random(1, 4);
	this->cor_da_barba = this->cor_do_cabelo;
	this->blusa = GeoA::random(1, 4);
	this->cor_da_blusa = GeoA::random(1, 4);
	this->calca = GeoA::random(1, 4);
	this->cor_da_calca = GeoA::random(1, 4);
	this->tenis = GeoA::random(1, 4);
	this->cor_do_tenis = GeoA::random(1, 4);

	if (GeoA::random() > 0.05) {
		Carteirinha cart_temp(this->sexo, this->rosto, this->cor_do_rosto, this->oculos, this->cor_do_oculos, this->cabelo, this->cor_do_cabelo, this->barba, this->cor_da_barba);
		this->cart = cart_temp;
	}

	//this->initTextures(nullptr);
}

Pessoa::Pessoa(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pb, int pcb, int pba, int pcba, int pca, int pcca, int pt, int pct):sexo(ps), rosto(pr), cor_do_rosto(pcr), oculos(po), cor_do_oculos(pco), cabelo(pc), cor_do_cabelo(pcc), barba(pba), cor_da_barba(pcba), blusa(pb), cor_da_blusa(pcb), calca(pca), cor_da_calca(pcca), tenis(pt), cor_do_tenis(pct) {

	//this->initTextures(nullptr);
}

void Pessoa::initTextures(SDL_Renderer* renderer) {
	string path_imgs = "../media/avatar/";
	
	string path_corpo = path_imgs+"body/corpo_c"+std::to_string(this->cor_do_rosto)+".png";
	this->t_corpo = Textura(path_corpo, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);

	string path_rosto = path_imgs+"head/"+std::to_string(this->sexo)+"_t"+std::to_string(this->rosto)+"_c"+std::to_string(this->cor_do_rosto)+".png";
	this->t_rosto = Textura(path_rosto, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	string path_cabelo = path_imgs+"head/cabelo_"+std::to_string(this->sexo)+"_t"+std::to_string(this->cabelo)+"_c"+std::to_string(this->cor_do_cabelo)+".png";
	this->t_cabelo = Textura(path_cabelo, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	string path_barba = path_imgs+"head/barba_"+std::to_string(this->sexo)+"_t"+std::to_string(this->barba)+"_c"+std::to_string(this->cor_da_barba)+".png";
	this->t_barba = Textura(path_barba, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	string path_oculos = path_imgs+"head/oculos_t"+std::to_string(this->oculos)+"_c"+std::to_string(this->cor_do_oculos)+".png";
	this->t_oculos = Textura(path_oculos, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//string path_blusa = path_imgs+"body/blusa_"+std::to_string(this->sexo)+"_t"+std::to_string(this->blusa)+"_c"+std::to_string(this->cor_da_blusa)+".png";
	string path_blusa = path_imgs+"body/blusa_"+std::to_string(this->sexo)+"_t1_c2.png";
	this->t_blusa = Textura(path_blusa, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//string path_calca = path_imgs+"body/calca_"+std::to_string(this->sexo)+"_t"+std::to_string(this->calca)+"_c"+std::to_string(this->cor_da_calca)+".png";
	string path_calca = path_imgs+"body/calca_"+std::to_string(this->sexo)+"_t3_c1.png";
	this->t_calca = Textura(path_calca, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//string path_tenis = path_imgs+"body/tenis_"+std::to_string(this->sexo)+"_t"+std::to_string(this->tenis)+"_c"+std::to_string(this->cor_do_tenis)+".png";
	string path_tenis = path_imgs+"body/tenis_"+std::to_string(this->sexo)+"_t1_c3.png";
	this->t_tenis = Textura(path_tenis, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);

	this->cart.initTextures(renderer);
}

Pessoa* Pessoa::update() {
	this->pos.add(&this->vel);
	this->vel.add(&this->acc);
	this->acc.mult(0);

	return this;
}

Pessoa* Pessoa::applyForce(const GeoA::Vetor* force) {
	this->acc.add(force);
	
	return this;
}

GeoA::Vetor* Pessoa::arrive(const GeoA::Vetor* target) {
	GeoA::Vetor* desired = GeoA::Vetor::sub(target, &this->pos);
	int d = desired->mag();
	double speed = this->max_speed;
	if (d < 100)
		speed = GeoA::map(d, 0, 100, 0, this->max_speed);
	desired->setMag(speed);
	GeoA::Vetor* steer = GeoA::Vetor::sub(desired, &this->vel);
	steer->limit(this->max_force);
	return steer;
}

Pessoa* Pessoa::render() {
	this->initTextures(this->t_rosto.getRenderer());

	this->t_corpo.render();
	this->t_rosto.render();
	this->t_cabelo.render();
	this->t_barba.render();
	this->t_oculos.render();
	this->t_blusa.render();
	this->t_calca.render();
	this->t_tenis.render();

	return this;
}

#endif