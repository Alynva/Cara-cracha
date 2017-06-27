#ifindef PESSOA_H
#define PESSOA_H
#include "carteirnha.h"
#include <iostream>

using namespace std;

class Pessoa {
	public:
		bool sexo;
		int forma_do_rosto;
		int cor_do_roso;
		int oculos;
		int cor_do_oculos;
		int cor_da_pele;
		int cabelo;
		int cor_do_cabelo;
		int chapeu;
		int cor_do_chapeu;
		int barba;
		int cor_da_barba;
		int blusa;
		int cor_da_blusa;
		int calca;
		int cor_da_calca;
		int tenis;
		int cor_do_tenis;
		Carteirinha card;
		
		Pessoa Pessoa();
		Pessoa Pessoa(bool, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, Carteirinha);
		
};

#endif
