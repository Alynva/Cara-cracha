#ifndef OBJETO
#define OBJETO

#include "GeoA.h"
#include "Textura.h"

struct Objeto {
	GeoA::Vetor pos;
	double estado;
	Textura tex_fundo_0;
	Textura tex_fundo_1;
	Textura tex_frente;
};

#endif