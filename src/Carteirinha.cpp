#include "../include/Carteirinha.h"


Textura Carteirinha::tex = Textura();

Carteirinha::Carteirinha() {
	
	this->sexo = GeoA::random() > 0.5;

	this->olhos = GeoA::random(1, 2);
	this->cor_do_rosto = GeoA::random(1, 4);
	this->cabelo = GeoA::random(1, 2);
	this->cor_do_cabelo = GeoA::random(1, 4);
	this->blusa = GeoA::random(1, 2);
	this->cor_da_blusa = GeoA::random(1, 4);

}

Carteirinha::Carteirinha(bool ps, int pr, int pcr, int pc):sexo(ps), olhos(pr), cor_do_rosto(pcr), cabelo(pc) {
	this->cor_do_cabelo = GeoA::random(1, 4);
	//this->barba = GeoA::random() > 0.8 ? GeoA::random(1, 4) : 0;
	//this->cor_da_barba = GeoA::random(1, 4);
	this->blusa = GeoA::random(1, 2);
	this->cor_da_blusa = GeoA::random(1, 4);
}

void Carteirinha::initTextures(SDL_Renderer* renderer) {
	std::string path_imgs = "../media/";
	
	std::string path_fundo_t = path_imgs+"img/carteirinha.png";
	this->t_fundo_t = Textura(path_fundo_t, renderer, {(int)this->pos.x - 150, (int)this->pos.y - 100, 300, 200});
	std::string path_fundo_f = path_imgs+"img/carteirinha (reflexo).png";
	this->t_fundo_f = Textura(path_fundo_f, renderer, {(int)this->pos.x - 150, (int)this->pos.y - 100, 300, 200});

	if (this->tex.getRenderer() == nullptr) {
		this->tex.setPath("../media/avatar/spritesheet.png");
		this->tex.setRenderer(renderer);
		this->tex.setTexture(this->tex.loadTexture());
	}

	this->t_corpo.setPath(this->tex.getPath());
	this->t_corpo.setRenderer(this->tex.getRenderer());
	this->t_corpo.setTexture(this->tex.getTexture());


	this->t_braco_e.setPath(this->tex.getPath());
	this->t_braco_e.setRenderer(this->tex.getRenderer());
	this->t_braco_e.setTexture(this->tex.getTexture());

	this->t_braco_d.setPath(this->tex.getPath());
	this->t_braco_d.setRenderer(this->tex.getRenderer());
	this->t_braco_d.setTexture(this->tex.getTexture());


	this->t_cabeca.setPath(this->tex.getPath());
	this->t_cabeca.setRenderer(this->tex.getRenderer());
	this->t_cabeca.setTexture(this->tex.getTexture());


	this->t_nariz_boca.setPath(this->tex.getPath());
	this->t_nariz_boca.setRenderer(this->tex.getRenderer());
	this->t_nariz_boca.setTexture(this->tex.getTexture());


	this->t_olhos.setPath(this->tex.getPath());
	this->t_olhos.setRenderer(this->tex.getRenderer());
	this->t_olhos.setTexture(this->tex.getTexture());


	this->t_cabelo.setPath(this->tex.getPath());
	this->t_cabelo.setRenderer(this->tex.getRenderer());
	this->t_cabelo.setTexture(this->tex.getTexture());


	this->t_blusa.setPath(this->tex.getPath());
	this->t_blusa.setRenderer(this->tex.getRenderer());
	this->t_blusa.setTexture(this->tex.getTexture());
	this->t_blusa_b_d.setPath(this->tex.getPath());
	this->t_blusa_b_d.setRenderer(this->tex.getRenderer());
	this->t_blusa_b_d.setTexture(this->tex.getTexture());
	this->t_blusa_b_e.setPath(this->tex.getPath());
	this->t_blusa_b_e.setRenderer(this->tex.getRenderer());
	this->t_blusa_b_e.setTexture(this->tex.getTexture());

}

Carteirinha* Carteirinha::update() {
	return this->updateTexPos();;
}

Carteirinha* Carteirinha::updateTexPos() {
	this->t_fundo_t.setPosition({int (this->pos.x), int (this->pos.y)});
	this->t_fundo_f.setPosition({int (this->pos.x), int (this->pos.y)});

	int pos_desloc_x = this->pos.x + 15*2;
	int pos_desloc_y = this->pos.y + 65*2;

	this->t_corpo.setSrcrect({70+309, 0, 24, 54 - 32});
	this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 24*2, (54 - 32)*2});

	this->t_braco_e.setSrcrect({172+309, 84, 8, 33 - 13});
	this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 8*2, (33 - 13)*2});

	this->t_braco_d.setSrcrect({35+309, 150, 8, 33 - 13});
	this->t_braco_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 2*2, 8*2, (33 - 13)*2});

	this->t_cabeca.setSrcrect({70+309, 56, 26, 31});
	this->t_cabeca.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 24*2, 26*2, 31*2});

	this->t_nariz_boca.setSrcrect({32, 10, 6, 6});
	this->t_nariz_boca.setFormat({pos_desloc_x + 9*2, pos_desloc_y - 2*2, 6*2, 6*2});

	if (this->sexo) { // É mulher
		switch (this->olhos) {
			case 1: // olhos 2
				this->t_olhos.setSrcrect({87, 0, 14, 6});
				this->t_olhos.setFormat({pos_desloc_x + 5*2, pos_desloc_y - 9*2, 14*2, 6*2});
				break;

			case 2: // olhos 6
				this->t_olhos.setSrcrect({213, 0, 14, 5});
				this->t_olhos.setFormat({pos_desloc_x + 5*2, pos_desloc_y - 10*2, 14*2, 5*2});
				break;
		}
		switch (this->cabelo) {
			case 1: // Cabelo 6
				this->t_cabelo.setSrcrect({48 + 7, 184, 48 - 7 - 6, 28});
				this->t_cabelo.setFormat({pos_desloc_x - (12 - 7)*2, pos_desloc_y - 27*2, (48 - 7 - 6)*2, 28*2});
				break;

			case 2: // Cabelo 11
				this->t_cabelo.setSrcrect({101, 67 + 2, 28, 33 - 2});
				this->t_cabelo.setFormat({pos_desloc_x - 2*2, pos_desloc_y - (29 - 2)*2, 28*2, (33 - 2)*2});
				break;
		}
		switch (this->blusa) {
			case 1: // Blusa 2405
				this->t_blusa.setSrcrect({192, 205, 29, 33 - 11});
				this->t_blusa.setFormat({pos_desloc_x - 2*2, pos_desloc_y, 29*2, (33 - 11)*2});

				this->t_blusa_b_d.setSrcrect({153, 185, 8, 17});
				this->t_blusa_b_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 3*2, 8*2, 17*2});

				this->t_blusa_b_e.setSrcrect({297, 134, 8, 18});
				this->t_blusa_b_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 8*2, 18*2});
				break;
		}
	} else { // Homem
		switch (this->olhos) {
			case 1: // olhos 4
				this->t_olhos.setSrcrect({147, 0, 16, 3});
				this->t_olhos.setFormat({pos_desloc_x + 4*2, pos_desloc_y - 7*2, 16*2, 3*2});
				break;

			case 2: // olhos 8
				this->t_olhos.setSrcrect({275, 0, 16, 6});
				this->t_olhos.setFormat({pos_desloc_x + 4*2, pos_desloc_y - 9*2, 16*2, 6*2});
				break;
		}
		switch (this->cabelo) {
			case 1: // Cabelo 30
				this->t_cabelo.setSrcrect({251, 67 + 7, 28, 32 - 7});
				this->t_cabelo.setFormat({pos_desloc_x - 2*2, pos_desloc_y - (34 - 7)*2, 28*2, (32 - 7)*2});
				break;

			case 2: // Cabelo 501
				this->t_cabelo.setSrcrect({150, 151, 39, 31});
				this->t_cabelo.setFormat({pos_desloc_x - 7*2, pos_desloc_y - 28*2, 39*2, 31*2});
				break;
		}
		switch (this->blusa) {
			case 1: // Blusa 2301
				this->t_blusa.setSrcrect({29, 237, 26, 31 - 9});
				this->t_blusa.setFormat({pos_desloc_x - 1*2, pos_desloc_y, 26*2, (31 - 9)*2});

				this->t_blusa_b_d.setSrcrect({212, 185, 9, 13});
				this->t_blusa_b_d.setFormat({pos_desloc_x - 5*2, pos_desloc_y + 2*2, 9*2, 13*2});

				this->t_blusa_b_e.setSrcrect({169, 185, 9, 13});
				this->t_blusa_b_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 9*2, 13*2});
				break;
		}
	}

	return this;
}

void Carteirinha::render() {
	this->t_fundo_t.render();

	SDL_Color cor_pele = {255, 255, 255, 255};
	switch (this->cor_do_rosto) {
		case 1:
			cor_pele = {252, 200, 151, 255};
			break;
		case 2:
			cor_pele = {199, 144, 99, 255};
			break;
		case 3:
			cor_pele = {145, 91, 47, 255};
			break;
	}

	SDL_Color cor_cabelo = {255, 255, 255, 255};
	switch (this->cor_do_cabelo) {
		case 1:
			cor_cabelo = {76, 29, 111, 255};
			break;
		case 2:
			cor_cabelo = {51, 51, 51, 255};
			break;
		case 3:
			cor_cabelo = {112, 193, 0, 255};
			break;
		case 4:
			cor_cabelo = {0, 183, 255, 255};
			break;
		case 5:
			cor_cabelo = {246, 255, 0, 255};
			break;
		case 6:
			cor_cabelo = {255, 0, 136, 255};
			break;
	}

	SDL_Color cor_blusa = {255, 255, 255, 255};
	switch (this->cor_da_blusa) {
		case 1:
			cor_blusa = {149, 255, 0, 255};
			break;
		case 2:
			cor_blusa = {59, 255, 0, 255};
			break;
		case 3:
			cor_blusa = {0, 85, 255, 255};
			break;
		case 4:
			cor_blusa = {225, 0, 255, 255};
			break;
		case 5:
			cor_blusa = {255, 0, 85, 255};
			break;
		case 6:
			cor_blusa = {255, 4, 0, 255};
			break;
	}


	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_braco_e.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_blusa.r, cor_blusa.g, cor_blusa.b);

	this->t_blusa_b_e.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_corpo.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_blusa.r, cor_blusa.g, cor_blusa.b);

	this->t_blusa.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_braco_d.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_blusa.r, cor_blusa.g, cor_blusa.b);

	this->t_blusa_b_d.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_cabeca.render();
	this->t_nariz_boca.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), 255, 255, 255);

	this->t_olhos.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_cabelo.r, cor_cabelo.g, cor_cabelo.b);

	this->t_cabelo.render();

	SDL_SetTextureColorMod(this->tex.getTexture(), 255, 255, 255);


	this->t_fundo_f.render();
}