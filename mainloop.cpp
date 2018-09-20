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

#define X_POSICAO_INICIAL 34
#define Y_POSICAO_INICIAL 1

int main(){
	FILE *log;
	log = fopen("log.txt","w+");
	//inicializando posicoes obj
	ListaDePosicoes *po = new ListaDePosicoes();
	Posicao *posicao_objetivo_0 = new Posicao(1, 50);
	Posicao *posicao_objetivo_1 = new Posicao(1, 51);
	Posicao *posicao_objetivo_2 = new Posicao(1, 52);
	po->adicionar_posicao(posicao_objetivo_0);
	po->adicionar_posicao(posicao_objetivo_1);
	po->adicionar_posicao(posicao_objetivo_2);

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
	//criando posicoes dos obstaculos
	Posicao *obstaculo_0 = new Posicao(25,25);
	Posicao *obstaculo_antiga_0 = new Posicao(25,25);
	Posicao *obstaculo_1 = new Posicao(30,30);
	Posicao *obstaculo_antiga_1 = new Posicao(30,30);
	Posicao *obstaculo_2 = new Posicao(20,20);
	Posicao *obstaculo_antiga_2 = new Posicao(20,20);
	//instanciando obstaculos
	Jogador *o0 = new Jogador('%', obstaculo_0, obstaculo_antiga_0);
	Jogador *o1 = new Jogador('%', obstaculo_1, obstaculo_antiga_1);
	Jogador *o2 = new Jogador('%', obstaculo_2, obstaculo_antiga_2);
	lo->adicionar_jogador(o0);
	lo->adicionar_jogador(o1);
	lo->adicionar_jogador(o2);
	

	Mapa *mapa1 = new Mapa(35,140,pi,po,lj,lo);
	Tela *tela = new Tela(mapa1, 50, 50, 50, 50);
	tela->init();
	tela->update();
	Teclado *teclado = new Teclado();
  	teclado->init();

  	double tempo_sistema = 0;
	int numero_de_derrotas = 0;
	while(1){
		int resultado;
		char c = teclado->getchar();
		
		//se a tecla detectada for o w o personagem quer ir para cima
		if (c == 'w') {
			//verifica se ha uma parede acima do personagem
			if(mapa1->verificar_colisao_parede(j1,CIMA) == 0){
      			//se nao houver parede move o personagem para cima
      			j1->andar(CIMA, log);
      			//verifica se apos andar o personagem colidiu com um obstaculo
      			//se sim, o personagem perde e sua posicao volta a ser a inicial
      			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
			}
    	}
    	else if (c == 's') {
    		if(mapa1->verificar_colisao_parede(j1,BAIXO) == 0){
      			j1->andar(BAIXO, log);
      			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
      		}	
    	}
    	else if (c == 'a'){
    		if(mapa1->verificar_colisao_parede(j1,ESQUERDA) == 0){
    			j1->andar(ESQUERDA, log);
    			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
    		}
    	}
    	else if (c == 'd'){
    		if(mapa1->verificar_colisao_parede(j1,DIREITA) == 0){
    			j1->andar(DIREITA, log);
    			if (mapa1->verificar_colisao_obstaculo(j1) == 1){
      				j1->set_posicao_atual(X_POSICAO_INICIAL,Y_POSICAO_INICIAL);
      				numero_de_derrotas++;
				}
    		}
    	}
    	else if (c == 'q') {
      		break;
		}
		tela->update();
		std::this_thread::sleep_for (std::chrono::milliseconds(30));
		tempo_sistema++;
	}
	tela->stop();
	teclado->stop();
	printf("tempo: %.2f\nderrotas: %d\n", (tempo_sistema/30), numero_de_derrotas);
	return 0;
}