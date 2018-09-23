#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "model.hpp"
#include "view.hpp"
#include "control.hpp"
#define DIREITA 0
#define ESQUERDA 1
#define BAIXO 2
#define CIMA 3

#define NUMERO_DE_POSICOES_OBJETIVO 5
#define NUMERO_DE_OBSTACULOS 10
#define X_POSICAO_INICIAL 34
#define Y_POSICAO_INICIAL 1

int main(){
	
	int i;
	//inicializando posicoes obj
	ListaDePosicoes *po = new ListaDePosicoes();
	Posicao *p;
	for (i = 0; i < NUMERO_DE_POSICOES_OBJETIVO; i++){
		p = new Posicao(1,135+i);
		po->adicionar_posicao(p);
	}

	//inicializando posicoes ini
	ListaDePosicoes *pi = new ListaDePosicoes();
	Posicao *posicao_inicial_0 = new Posicao(X_POSICAO_INICIAL, Y_POSICAO_INICIAL);
	Posicao *posicao_antiga_0 = new Posicao(X_POSICAO_INICIAL, Y_POSICAO_INICIAL);
	pi->adicionar_posicao(posicao_inicial_0);
	
	//criando jogadores
	ListaDeJogadores *lj = new ListaDeJogadores();
	Jogador *j1 = new Jogador('x', posicao_inicial_0, posicao_antiga_0);  
	lj->adicionar_jogador(j1);

	//criando obstaculos
	//instanciando lista de obstaculos
	ListaDeJogadores *lo = new ListaDeJogadores();
	
	Posicao *p_o, *p_oa;
	Jogador *obstaculo;
	for (i = 0; i < NUMERO_DE_OBSTACULOS; i++){
		//gera um numero entre 1 e 30
		int x = rand() % 33 + 1;
		//gera um numero entre 1 e 139 
		int y = rand() % 139 + 1;
		if(x != X_POSICAO_INICIAL && y != Y_POSICAO_INICIAL){
			//criando posicoes do obstaculo
			p_o = new Posicao(x,y);
			p_oa = new Posicao(x,y);
			//instanciando obstaculo
			obstaculo = new Jogador('%', p_o, p_oa);
			//adicionando obstaculo na lista
			lo->adicionar_jogador(obstaculo);	
		}
	}

	Mapa *mapa1 = new Mapa(35,140,pi,po,lj,lo);
	Tela *tela = new Tela(mapa1, 50, 50, 50, 50);
	tela->init();
	tela->update();
	Teclado *teclado = new Teclado();
  	teclado->init();
  	//instancia um objeto que será responsável pela thread que move os obstaculos periodicamente
  	ManipuladorDeObstaculos *manipulador = new ManipuladorDeObstaculos(mapa1);
  	//inicializacao do manipulador de obstaculos que inicia a thread de mover obstaculos
  	manipulador->init();
  	
  	//variaveis de sistema
  	int tempo_sistema = 0;
	int numero_de_derrotas = 0;
	int numero_de_vitorias = 0;
	while(1){
		
		//verifica se apos andar o personagem colidiu com um obstaculo
      	//se sim, o personagem perde e sua posicao volta a ser a inicial 
		if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
      	}

      	//le a entrada do teclado
		char c = teclado->getchar();
		//se a tecla detectada for o w o personagem quer ir para cima
		if (c == 'w') {
			//verifica se ha uma parede acima do personagem
			if(mapa1->verificar_colisao_parede(j1,CIMA) == 0){
      			//se nao houver parede move o personagem para cima
      			j1->andar(CIMA);
      			//verifica se apos andar o personagem colidiu com um obstaculo
      			//se sim, o personagem perde e sua posicao volta a ser a inicial
      			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
				if (mapa1->verificar_vitoria(j1) == 1){
					j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_vitorias++;
				}
			}
    	}
    	//se a tecla detectada for o s o personagem quer ir para baixo
    	else if (c == 's') {
    		if(mapa1->verificar_colisao_parede(j1,BAIXO) == 0){
      			j1->andar(BAIXO);
      			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
				if (mapa1->verificar_vitoria(j1) == 1){
					j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_vitorias++;
				}
      		}	
    	}
    	//se a tecla detectada for o a o personagem quer ir para esquerda
    	else if (c == 'a'){
    		if(mapa1->verificar_colisao_parede(j1,ESQUERDA) == 0){
    			j1->andar(ESQUERDA);
    			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
				if (mapa1->verificar_vitoria(j1) == 1){
					j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_vitorias++;
				}
    		}
    	}
    	//se a tecla detectada for o d o personagem quer ir para direita
    	else if (c == 'd'){
    		if(mapa1->verificar_colisao_parede(j1,DIREITA) == 0){
    			j1->andar(DIREITA);
    			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
				if (mapa1->verificar_vitoria(j1) == 1){
					j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_vitorias++;
				}
    		}
    	}
    	//encerra o programa se a tecla lida for q
    	else if (c == 'q') {
      		break;
		}
		//atualiza a tela com as novas posicoes do jogador e dos obstaculos
		tela->update();
		std::this_thread::sleep_for (std::chrono::milliseconds(30));
		tempo_sistema++;
	}

	tela->stop();
	teclado->stop();
	manipulador->stop();
	printf("derrotas: %d\nvitorias: %d\n",numero_de_derrotas,numero_de_vitorias);
	return 0;
}