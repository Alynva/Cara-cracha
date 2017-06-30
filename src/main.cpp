#include "../include/Cara_cracha.h"

int main(int argc, char** argv) {
	GeoA::randInit();

	Cara_cracha jogo;

	unsigned int maxFPS = 60, lastTime = 0, currentTime;

	if (jogo.init()) {
		jogo.play();
		while (jogo.update()) {
			currentTime = SDL_GetTicks();
			int sleep = lastTime + maxFPS - currentTime;
			//SDL_Log("%d", lastTime + maxFPS - currentTime);
			if (sleep > 0)
				SDL_Delay(sleep);
			lastTime = currentTime;
		}

		cout << "RODOU" << endl;
	}

	return 7;
}