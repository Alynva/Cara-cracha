#ifndef __Geometria_Alynva__
#define __Geometria_Alynva__

namespace GeoA {
	const double TWO_PI = 6.28318530717958647693;
	const double PI = 3.14159265358979323846;
	const double HALF_PI = 1.57079632679489661923;
	const double QUARTER_PI = 0.7853982;

	void randInit();
	double random(); // [0.0 .. 1.0]
	double random(double); // [0.0 .. double]
	int random(int, int); // [int .. int]
	double random(double, double); // [double .. double]
	int randomX(int, int); // (int .. int)
	
	double map(double, double, double, double, double);
	
	struct Ponto {
		double x; // Número do componente x do vetor
		double y; // Número do componente y do vetor
		
		Ponto(double px, double py):x(px), y(py) {};
		Ponto(Ponto* pp):x(pp->x), y(pp->y) {};
		Ponto():x(), y() {};
	};

	struct Vetor : public Ponto { // Uma classe para descrever um vetor de duas ou três dimensões, especificamente um vetor euclidiano (também conhecido como geométrico).
		double z; // Número do componente z do vetor

		Vetor(double px, double py, double pz):Ponto(px, py), z(pz) {}; // Construtores para a passagem direta ou indireta dos componentes ou para o vetor nulo.
		Vetor(Vetor* pv):Ponto(pv->x, pv->y), z(pv->z) {};
		Vetor():Ponto(0, 0), z(0) {};

		char* toString() const; // Retorna uma representação em sequência de caracteres de um vetor v ao chamar v.toString(). Esse método é útil para registrar vetores no console.
		Vetor* set(double, double, double); // Definem o componente x, y e z do vetor usando três variáveis ​​separadas ou os dados de um Vetor.
		Vetor* set(Vetor*);
		Vetor* copy() const; // Obtém uma cópia do vetor, retorna um objeto Vetor.

		Vetor* add(double, double, double); // Adiciona componentes x, y e z a um vetor, adiciona um vetor a outro ou adiciona dois vetores independentes juntos. A versão do método que adiciona dois vetores juntos é um método estático e retorna um objeto Vetor, os outros atuam diretamente no vetor.
		Vetor* add(const Vetor*);
		static Vetor* add(Vetor*, Vetor*);
		Vetor* sub(double, double, double); // Subtrai componentes x, y e z de um vetor, subtrai um vetor de outro, ou subtrai dois vetores independentes. A versão do método que subtrai dois vetores é um método estático e retorna um objeto Vetor, os outros atuam diretamente no vetor.
		Vetor* sub(const Vetor*);
		static Vetor* sub(const Vetor*, const Vetor*);
		Vetor* mult(double); // Multiplique o vetor por um escalar.
		Vetor* div(double); // Divida o vetor por um escalar.
		double mag(); // Calcula a magnitude (comprimento) do vetor e retorna o resultado como um double.

		double magSq(); // Calcula a magnitude quadrada do vetor e retorna o resultado como um double. Mais rápido se o comprimento real não for necessário no caso de comparar vetores, etc.
		double dot(Vetor*) const; // Calcula o produto interno de dois vetores. A versão do método que calcula o produto ponto de dois vetores independentes é um método estático.
		static double dot(Vetor*, Vetor*);
		Vetor* cross(Vetor*) const; // Calcula e retorna um vetor composto do produto cruzado entre dois vetores. Ambos os métodos estático e não estático retornam um novo objeto Vetor.
		static Vetor* cross(Vetor*, Vetor*);
		double dist(const Vetor*) const; // Calcula a distância euclidiana entre dois pontos (considerando ponto como um objeto vetorial). A versão do método que calcula a distância de dois pontos independentes é um método estático.
		static double dist(const Vetor*, const Vetor*);
		Vetor* normalize(); // Normaliza o vetor para o comprimento 1 (faça dele um vetor unitário).
		Vetor* limit(double); // Limita a magnitude desse vetor ao valor usado no parâmetro.
		Vetor* setMag(double); // Define a magnitude desse vetor para o valor usado no parâmetro.
		double heading() const; // Calcula e retorna o ângulo de rotação para este vetor (apenas vetores 2D)
		Vetor* rotate(double); // Gira o vetor por um ângulo (apenas vetores 2D), a magnitude permanece a mesma.
		static double angleBetween(Vetor*, Vetor*); // Calcula e retorna o ângulo (em radianos) entre dois vetores.
		static Vetor* lerp(Vetor*, Vetor*, double = 0); // Interpolar linearmente o vetor para outro vetor.
		double* array() const; // Retorna uma representação deste vetor como um array de double. Isso é apenas para uso temporário. Se for necessário usar de qualquer outra forma, o conteúdo deve ser copiado usando o método Vetor::copy() para copiar para sua própria matriz.
		static bool equals(Vetor*, Vetor*); // Checa a igualdade entre dois vetores.
		static Vetor* fromAngle(double); // Cria um novo vetor 2D unitário a partir de um ângulo.
		static Vetor* random2D(); // Cria um novo vetor 2D unitário a partir de um ângulo aleatório.
		static Vetor* random3D(); // Cria um novo vetor 3D unitário a partir de um ângulo aleatório.

		bool operator!=(const Vetor&) const;
	};
	
	
	class Objeto {
		Vetor pos;
		Vetor target;
		Vetor vel;
		Vetor acc;
		double max_speed;
		double max_force;
		
		public:
			Objeto() {
				this->max_speed = 10;
				this->max_force = 1;
			}
			
			Objeto* update();
			Objeto* behaviors();
			Objeto* applyForce(const Vetor*);
			Vetor* arrive(const Vetor*);
			Vetor* flee(const Vetor*);
	};
}

#endif
