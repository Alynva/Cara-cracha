/*
	Classe responsável por facilitar o uso das texturas SDL.

	Declaração: o construtor sem parâmetros não inicializa nada, enquanto que o que recebe seis parâmetros, uma string, um renderizador do SDL e quatro inteiros, cria a textura, utilizando os dois primeiros inteiros para a posição e os outros dois para o tamanho.
	Métodos:
		setSize: recebe dois inteiros, x e y, respectivamente, e muda a posição da carta, usando os valores de x e y.
		setPosition: recebe dois inteiros, h e w, altura e largura, respectivamente, e muda o tamanho da carta, usando os valores de h e w.
		render: renderiza a carta na janela principal.
	Detalhes:
*/

#ifndef TEXTURA_H
#define TEXTURA_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

class Textura {
	std::string pPath;
	SDL_Renderer* pRenderer;
	SDL_Texture* pTexture;
	SDL_Rect recSrcrect;
	SDL_Rect recFormat;

	public:
		Textura() {};
		Textura(std::string, SDL_Renderer*, SDL_Rect, SDL_Rect * = nullptr);
		~Textura();
	
		void setPath(std::string);
		std::string getPath() const;
		void setRenderer(SDL_Renderer*);
		SDL_Renderer* getRenderer() const;
		void setTexture(SDL_Texture*);
		SDL_Texture* getTexture() const;
		void setSrcrect(SDL_Rect);
		SDL_Rect getSrcrect() const;
		void setFormat(SDL_Rect);
		SDL_Rect getFormat() const;

		SDL_Texture* loadTexture();

		void setSize(int, int);
		SDL_Point getSize() const;
		void setPosition(SDL_Point);
		SDL_Point getPosition() const;
		
		bool render();
};

#endif