#ifindef CARTEIRINHA_H
#define CARTEIRINHA_H

#include <iostream>

using namespace std;

class Carteirinha {
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
		
		Carteirinha Carteirinha();
		Carteirinha Carteirinha(bool, int, int, int, int, int, int, int, int, int, int, int );
		
};

#endif
