#include "../include/Cara_cracha.h"

int main(int argc, char** argv) {
	GeoA::randInit();

	Cara_cracha jogo;

	if (jogo.init()) {
		while (jogo.update())
			jogo.render();
	}

	return 7;
}