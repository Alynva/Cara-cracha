#include "../include/Cara_cracha.h"

int main(int argc, char** argv) {
	GeoA::randInit();

	Cara_cracha jogo;

	if (jogo.init()) {
		jogo.play();
		while (jogo.update());

		cout << "RODOU" << endl;
	}

	return 7;
}