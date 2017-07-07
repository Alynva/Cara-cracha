[![GitHub contributors](https://img.shields.io/github/contributors/Alynva/Cara-cracha.svg)](https://github.com/Alynva/Cara-cracha/graphs/contributors) [![GitHub tag](https://img.shields.io/github/tag/Alynva/Cara-cracha.svg)](https://github.com/Alynva/Cara-cracha/tags) [![Codacy grade](https://img.shields.io/codacy/grade/ad0f531c54c748269e35392ea2f79756.svg)](https://www.codacy.com/app/Alynva/Cara-cracha?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Alynva/FreeCell&amp;utm_campaign=Badge_Grade) [![Github Downloads All Releases](https://img.shields.io/github/downloads/Alynva/Cara-cracha/total.svg)](https://github.com/Alynva/Cara-cracha/releases/latest)

# Cara crachá
## Repositório do Projeto 3 da disciplina Estrutura de Dados.
O jogo desenvolvido para o terceiro projeto de Estruturas de Dados foi o jogo “Cara-Cracha”. Neste jogo, o jogador vive na pele a experiência de trabalhar como monitor em um restaurante universitário (RU). Sua função é verificar se uma pessoa é quem diz ser, olhando para seu rosto e sua suposta carteirinha de estudante.

Durante o jogo, o jogador deve administrar seu tempo e administrar as pessoas que ficam aparecendo na entrada do refeitório. O jogo tem inicio às 11:00 e termina às 14:00, reabrindo das 17:00 às 19:00 simulando o horário de funcionamento padrão do refeitório. Após o início do expediente, uma fila de pessoas começa se formar na frente da catraca. A missão do jogador é ser rápido, para evitar o acúmulo de pessoas, e ser observador, pois pessoas com carteirinhas erradas não podem entrar. Ao autorizar a entrada de alguém com carteirinha irregular, o jogador é penalizado. Ao alcançar o fim do expediente, com uma boa classificação (baseada na quantidade de pessoas corretas e incorretas), o jogador vence.

Uma pessoa é gerada aleatoriamente e possui diversas características que as identifica, além de ter sua própria carteirinha de estudante. Claramente, a carteirinha deve conter determinadas informações e características sobre a pessoa para que seja considerada válida. O jogador deve ser rápido e observar detalhes para evitar cometer erros durante seu dia de trabalho. 
O que torna o jogo realmente desafiador é o fato de uma pessoa estar de um jeito na foto da carteirinha, mas depois ter pintado o cabelo, comprado um óculos, deixado o bigode crescer, entre outras alterações cotidianas, o que o torna ligeiramente diferente da foto, mas ainda é ele! Então tenha muito cuidado!

Estruturas de Dados do jogo:
- Uma fila de personagens. Gerada no início do jogo e preenchida conforme novos personagens ingressam na fila;
- Uma fila de posições. Cada pessoa possui uma posição, a qual é definida a partir de uma lista ordenada de coordenadas que representam cada posição na fila.
- Uma lista de camadas para a construção do cenário;

## Instalação
Utilizamos a linguagem de programação C++ na versão 11 durante a codificação do jogo. Para compilá-lo, basta executar o comando ```make``` na pasta **./src**. O arquivo **makefile** está configurado para colocar o executável dentro da pasta **./bin**, o qual pode ser lançado utilizando o comando ```make run```. Caso queira otimizar as etapas, ao executar o comando ```make full``` você estará compilando e executando o jogo.

O projeto foi compilado e testado utilizando os seguintes SOs:

- Windows 8.1 64-bit

- Linux Xubuntu 64-bit


Para demais sistemas, fica a cargo do utilizador verificar a compatibilidade. Ocorrendo algum problema, comunique-nos [criando uma nova questão](https://github.com/Alynva/Cara-cracha/issues/new). Caso obtenha sucesso na utilização em demais sistemas, sinta-se à vontade para colaborar com a presente documentação, incrementando-o à lista anterior.

## Descrição da Implementação
O jogo foi desenvolvido seguindo as configurações do tipo abstrato de dado (TAD) Fila circular, com encadeamento duplo e com nó header. Tem-se então que cada elemento é armazenado em um nó com três atributos, sendo eles:
- Value: armazena o elemento em si;
- Next: ponteiro que define o nó do próximo elemento;
- Previous: ponteiro que define o nó do elemento anterior.

![Pilha vazia](https://dl.dropboxusercontent.com/sh/t21x4vitadfju4f/AACFp7c9owqJjeheMEUKR8Cga/Freecell/fila2.png?dl=0)

Figura 1: Fila vazia. Nó header, com os campos value, previous e next.

![Pilha com três elementos](https://dl.dropboxusercontent.com/sh/t21x4vitadfju4f/AADT-urACh2Yyr-EMwvzeUQga/Freecell/fila.png?dl=0)

Figura 2: Fila com 3 elementos, nó header e encadeamento duplo. Na figura acima C é o último elemento.

## Autores
* Alisson Nunes - [GitHub](https://github.com/Alynva)
* Gabriel Alves - [GitHub](https://github.com/CptSpookz)
* Matheus Bortoleto - [GitHub](https://github.com/explodingnuggets)
* Rafael Sales - [GitHub](https://github.com/rsaless)

## Créditos
* Alisson Nunes - Programação.
* Gabriel Alves - Desenvolvimento do segundo projeto.
* Matheus Bortoleto - Desenvolvimento do segundo projeto.
* Rafael Sales - Documentação.

## Licença
O código a seguir foi criado para propósitos educacionais e seu reuso é aberto a qualquer um que o queira utilizar, com permissões de cópia, criação, distribuição e remoção de partes ou totalidade dele, desde que se deem os devidos créditos aos autores. Para mais detalhes, acesse o [documento completo](https://github.com/Alynva/Cara-cracha/blob/master/LICENSE.md).
