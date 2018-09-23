#include "view.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>

//construtor da tela
Tela::Tela(Mapa *m, int maxI, int maxJ, float maxX, float maxY) {
  this->m = m;
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;
}

//inicializacao da tela
void Tela::init() {
  initscr();			      
	raw();				        
  curs_set(0);         
}

//funcao que desenha na tela
void Tela::update() {
  int linhaMax, colunaMax;
  getmaxyx(stdscr, linhaMax, colunaMax);
  int a = this->m->get_altura();
  int l = this->m->get_largura();
  int i,k;
  
//desenhando limite superior e inferior
for(i = 0; i < l; i++){
    
    move(0,i);
    echochar('=');
    if (i < colunaMax){
      move(a,i);
      echochar('=');  
    }    
}

//desenhando limites laterais
for(i = 1; i < a; i++){
  move(i,0);
  echochar('|');
  if (i < linhaMax){
    move(i,l);
    echochar('|');
  }
}
move(a,l);
echochar('=');

  //pegar todas as posicoes antigas dos jogadores e apaga-los
  std::vector<Jogador*> *vetor = this->m->get_jogadores();
  for (i = 0; i < vetor->size();i++){
    int x = (int) (*vetor)[i]->get_posicao_antiga()->get_x()  * (this->maxI / this->maxX);
    int y = (int) (*vetor)[i]->get_posicao_antiga()->get_y()  * (this->maxJ / this->maxY);
    move(x,y);
    echochar(' ');
  }

  //pegar todas as posicoes atuais dos jogadores desenha-los
  for (i = 0; i < vetor->size();i++){
    int x = (int) (*vetor)[i]->get_posicao_atual()->get_x() * (this->maxI / this->maxX);
    int y = (int) (*vetor)[i]->get_posicao_atual()->get_y() * (this->maxJ / this->maxY);
    move(x,y);
    echochar((*vetor)[i]->get_simbolo());
  }

  //pegar todas as posicoes objetivo e mostrá-las
  std::vector<Posicao*> *posicoes_objetivo = this->m->get_posicoes_objetivo();
  for (i = 0; i < posicoes_objetivo->size(); i++){
    int x = (int) (*posicoes_objetivo)[i]->get_x() * (this->maxI / this->maxX);
    int y = (int) (*posicoes_objetivo)[i]->get_y() * (this->maxJ / this->maxY);
    move(x,y);
    echochar('O');
  }

  //pegar todos as posicoes antigas dos obstaculos e apaga-los
  std::vector<Jogador*> *obstaculos = this->m->get_obstaculos();
  for (i = 0; i < obstaculos->size();i++){
    int x = (int) (*obstaculos)[i]->get_posicao_antiga()->get_x()  * (this->maxI / this->maxX);
    int y = (int) (*obstaculos)[i]->get_posicao_antiga()->get_y()  * (this->maxJ / this->maxY);
    move(x,y);
    echochar(' ');
  }

  //pegar todas as posicoes atuais dos obstaculos e desenha-los
  for (i = 0; i < obstaculos->size();i++){
    int x = (int) (*obstaculos)[i]->get_posicao_atual()->get_x()  * (this->maxI / this->maxX);
    int y = (int) (*obstaculos)[i]->get_posicao_atual()->get_y()  * (this->maxJ / this->maxY);
    move(x,y);
    echochar((*obstaculos)[i]->get_simbolo());
  }
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}
