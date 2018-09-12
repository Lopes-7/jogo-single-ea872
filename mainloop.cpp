#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "model.hpp"
#include "view.hpp"
#define DIREITA 0
#define ESQUERDA 1
#define BAIXO 2
#define CIMA 3

int main(){

	//inicializando posicoes obj
	ListaDePosicoes *po = new ListaDePosicoes();
	Posicao *posicao_obejtivo_0 = new Posicao(0, 10);
	Posicao *posicao_obejtivo_1 = new Posicao(1, 10);
	Posicao *posicao_obejtivo_2 = new Posicao(2, 10);
	po->adicionar_posicao(posicao_obejtivo_0);
	po->adicionar_posicao(posicao_obejtivo_1);
	po->adicionar_posicao(posicao_obejtivo_2);

	//inicializando posicoes ini
	ListaDePosicoes *pi = new ListaDePosicoes();
	Posicao *posicao_inicial_0 = new Posicao(1, 3);
	Posicao *posicao_inicial_1 = new Posicao(7, 1);
	pi->adicionar_posicao(posicao_inicial_0);
	pi->adicionar_posicao(posicao_inicial_1);
	//criando jogadores
	ListaDeJogadores *lj = new ListaDeJogadores();
	Jogador *j1 = new Jogador('x', posicao_inicial_0);  
	lj->adicionar_jogador(j1);


	Mapa *mapa1 = new Mapa(100,35,pi,po,lj);
	Tela *tela = new Tela(mapa1, 50, 50, 50, 50);
	tela->init();
	tela->update();
	std::this_thread::sleep_for (std::chrono::milliseconds(1000));
	j1->andar(BAIXO);
	tela->update();
	std::this_thread::sleep_for (std::chrono::milliseconds(1000));
	j1->andar(DIREITA);
	tela->update();
	std::this_thread::sleep_for (std::chrono::milliseconds(1000));
	tela->stop();
	return 0;
}