#ifndef CARTEIRINHA_H
#define CARTEIRINHA_H

#include "GeoA.h"
#include "Textura.h"

class Carteirinha {
	Textura t_fundo;
	Textura t_corpo;
	Textura t_rosto;
	Textura t_oculos;
	Textura t_cabelo;
	Textura t_barba;
	Textura t_blusa;

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
		int blusa;
		int cor_da_blusa;
		
		Carteirinha();
		Carteirinha(bool, int, int, int, int, int, int, int, int, int, int);
		
		void initTextures(SDL_Renderer*);
		Carteirinha* update();
		Carteirinha* updateTexPos();
		void render();
};

inline Carteirinha::Carteirinha() {
	
	this->sexo = GeoA::random() > 0.5;

	this->rosto = GeoA::random(1, 4);
	this->cor_do_rosto = GeoA::random(1, 4);
	this->oculos = GeoA::random() > 0.75 ? GeoA::random(1, 4) : 0;
	this->cor_do_oculos = GeoA::random(1, 4);
	this->cabelo = GeoA::random(1, 4);
	this->cor_do_cabelo = GeoA::random(1, 4);
	this->barba = GeoA::random() > 0.8 ? GeoA::random(1, 4) : 0;
	this->cor_da_barba = GeoA::random(1, 4);
	this->blusa = GeoA::random(1, 4);
	this->cor_da_blusa = GeoA::random(1, 4);

}

inline Carteirinha::Carteirinha(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pb, int pcb, int pbl, int pcbl):sexo(ps), rosto(pr), cor_do_rosto(pcr), oculos(po), cor_do_oculos(pco), cabelo(pc), cor_do_cabelo(pcc), barba(pb), cor_da_barba(pcb), blusa(pbl), cor_da_blusa(pcbl) {

}

inline void Carteirinha::initTextures(SDL_Renderer* renderer) {
	std::string path_imgs = "../media/";
	
	std::string path_fundo = path_imgs+"img/fundo_cart.png";
	this->t_fundo = Textura(path_fundo, renderer, this->pos.x - 150, this->pos.y - 100, 300, 200);

	std::string path_corpo = path_imgs+"avatar/body/corpo_c"+std::to_string(this->cor_do_rosto)+".png";
	this->t_corpo = Textura(path_corpo, renderer, this->pos.x - 12, this->pos.y + 45, 128, 220);

	std::string path_rosto = path_imgs+"avatar/head/"+std::to_string(this->sexo)+"_t"+std::to_string(this->rosto)+"_c"+std::to_string(this->cor_do_rosto)+".png";
	this->t_rosto = Textura(path_rosto, renderer, this->pos.x - 12, this->pos.y + 45, 128, 220);
	
	std::string path_cabelo = path_imgs+"avatar/head/cabelo_"+std::to_string(this->sexo)+"_t"+std::to_string(this->cabelo)+"_c"+std::to_string(this->cor_do_cabelo)+".png";
	this->t_cabelo = Textura(path_cabelo, renderer, this->pos.x - 12, this->pos.y + 45, 128, 220);
	
	std::string path_barba = this->barba > 0 ? path_imgs+"avatar/head/barba_"+std::to_string(this->sexo)+"_t"+std::to_string(this->barba)+"_c"+std::to_string(this->cor_da_barba)+".png" : path_imgs+"avatar/0.png";
	this->t_barba = Textura(path_barba, renderer, this->pos.x - 12, this->pos.y + 45, 128, 220);
	
	std::string path_oculos = this->oculos > 0 ? path_imgs+"avatar/head/oculos_t"+std::to_string(this->oculos)+"_c"+std::to_string(this->cor_do_oculos)+".png" : path_imgs+"avatar/0.png";
	this->t_oculos = Textura(path_oculos, renderer, this->pos.x - 12, this->pos.y + 45, 128, 220);
	
	//std::string path_blusa = path_imgs+"body/blusa_"+std::to_string(this->sexo)+"_t"+std::to_string(this->blusa)+"_c"+std::to_string(this->cor_da_blusa)+".png";
	std::string path_blusa = path_imgs+"avatar/body/blusa_"+std::to_string(this->sexo)+"_t1_c2.png";
	this->t_blusa = Textura(path_blusa, renderer, this->pos.x - 12, this->pos.y + 45, 128, 220);

}

inline Carteirinha* Carteirinha::update() {
	this->updateTexPos();

	return this;
}

inline Carteirinha* Carteirinha::updateTexPos() {
	this->t_fundo.setPosition({int (this->pos.x), int (this->pos.y)});

	this->t_corpo.setPosition({int (this->pos.x - 12), int (this->pos.y + 45)});
	this->t_rosto.setPosition({int (this->pos.x - 12), int (this->pos.y + 45)});
	this->t_cabelo.setPosition({int (this->pos.x - 12), int (this->pos.y + 45)});
	this->t_barba.setPosition({int (this->pos.x - 12), int (this->pos.y + 45)});
	this->t_oculos.setPosition({int (this->pos.x - 12), int (this->pos.y + 45)});
	this->t_blusa.setPosition({int (this->pos.x - 12), int (this->pos.y + 45)});

	return this;
}

inline void Carteirinha::render() {
	this->t_fundo.render();

	SDL_Rect srcrect, format;
	srcrect.x = 31;
	srcrect.y = 30;
	srcrect.w = 72;
	srcrect.h = 100;

	format.x = this->t_corpo.getPosition().x + srcrect.x;
	format.y = this->t_corpo.getPosition().y + srcrect.y;
	format.w = srcrect.w;
	format.h = srcrect.h;

	SDL_RenderCopy(this->t_corpo.getRenderer(), this->t_corpo.getTexture(), &srcrect, &format);
	SDL_RenderCopy(this->t_rosto.getRenderer(), this->t_rosto.getTexture(), &srcrect, &format);
	SDL_RenderCopy(this->t_cabelo.getRenderer(), this->t_cabelo.getTexture(), &srcrect, &format);
	SDL_RenderCopy(this->t_barba.getRenderer(), this->t_barba.getTexture(), &srcrect, &format);
	SDL_RenderCopy(this->t_oculos.getRenderer(), this->t_oculos.getTexture(), &srcrect, &format);
	SDL_RenderCopy(this->t_blusa.getRenderer(), this->t_blusa.getTexture(), &srcrect, &format);

	//this->t_corpo.render();
	//this->t_rosto.render();
	//this->t_cabelo.render();
	//this->t_barba.render();
	//this->t_oculos.render();
	//this->t_blusa.render();
}

#endif