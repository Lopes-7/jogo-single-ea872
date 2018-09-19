#include "view.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>

Tela::Tela(Mapa *m, int maxI, int maxJ, float maxX, float maxY) {
  this->m = m;
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;
}

void Tela::init() {
  initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
  curs_set(0);           /* Do not display cursor */
}

void Tela::update() {
  int linhaMax, colunaMax;
  getmaxyx(stdscr, linhaMax, colunaMax);
  int a = this->m->get_altura();
  int l = this->m->get_largura();
  int i,k;
  
  //fazer de forma mais eficiente
  for (i = 0; i < l; i++){
    for(k = 0; k < a; k++){
      if(i == 0 || i == l-1){
        move(i, k);   /* Move cursor to position */
        echochar('=');  /* Prints character, advances a position */  
      }
      if(k == 0 || k == a-1){
        move(i, k);   /* Move cursor to position */
        echochar('|');
      }
    }
  }
  //pegar todas as posicoes antigas dos jogadores e apaga-los
  std::vector<Jogador*> *vetor = this->m->get_jogadores();
  for (i = 0; i < vetor->size();i++){
    int x = (*vetor)[i]->get_posicao_antiga()->get_x();
    int y = (*vetor)[i]->get_posicao_antiga()->get_y();
    move(x,y);
    echochar(' ');
  }

  //pegar todas as posicoes atuais dos jogadores desenha-los

  for (i = 0; i < vetor->size();i++){
    int x = (*vetor)[i]->get_posicao_atual()->get_x();
    int y = (*vetor)[i]->get_posicao_atual()->get_y();
    move(x,y);
    echochar((*vetor)[i]->get_simbolo());
  }


}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}
