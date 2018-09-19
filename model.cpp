#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#include "model.hpp"

Posicao::Posicao(int x, int y) {
	this->x = x;
	this->y = y;
}
int Posicao::get_x() {
	return this->x;
}
int Posicao::get_y() {
	return this->y;
}
void Posicao::set_x(int novo) {
	this->x = novo;
}
void Posicao::set_y(int novo) {
	this->y = novo;
}


ListaDePosicoes::ListaDePosicoes(){
	this->posicoes = new std::vector<Posicao *>(0);
}
std::vector<Posicao*> *ListaDePosicoes::get_posicoes(){
	return (this->posicoes);
}
void ListaDePosicoes::adicionar_posicao(Posicao *p){
	(this->posicoes)->push_back(p);
}
void ListaDePosicoes::remover_posicao(Posicao *p){
//TO DO
}
void ListaDePosicoes::hard_copy(ListaDePosicoes *ldp) {
  std::vector<Posicao *> *posicoes = ldp->get_posicoes();

  for (int k=0; k<posicoes->size(); k++) {
    Posicao *p = new Posicao((*posicoes)[k]->get_x(),\
                          (*posicoes)[k]->get_y());
    this->adicionar_posicao(p);
  }
}

Jogador::Jogador(char simbolo, Posicao *posicao_atual, Posicao *posicao_antiga) {
	this->simbolo = simbolo;
	this->posicao_atual = posicao_atual;
	this->posicao_antiga = posicao_antiga;

}

void Jogador::andar(int direcao, FILE *log){	
	int x, y;
	if (direcao == 0){
		//anda para frente;
		//copia posicao atual em antiga
		x = this->posicao_atual->get_x();
		y = this->posicao_atual->get_y();
		this->posicao_antiga->set_x(x);
		this->posicao_antiga->set_y(y);
		
		//atualiza posicao atual
		y++;
		this->posicao_atual->set_y(y);
	}
	else if (direcao == 1){
		//anda para tras;
		//copia posicao atual em antiga
		x = this->posicao_atual->get_x();
		y = this->posicao_atual->get_y();
		this->posicao_antiga->set_x(x);
		this->posicao_antiga->set_y(y);
		
		//atualiza posicao atual
		y--;
		this->posicao_atual->set_y(y);	
	}
	else if (direcao == 2){
		//anda para direita;
		//copia posicao atual em antiga
		x = this->posicao_atual->get_x();
		y = this->posicao_atual->get_y();
		this->posicao_antiga->set_x(x);
		this->posicao_antiga->set_y(y);

		//atualiza posicao atual
		x++;
		this->posicao_atual->set_x(x);	
	}
	else if (direcao == 3){
		//anda para esquerda;
		//copia posicao atual em antiga
		x = this->posicao_atual->get_x();
		y = this->posicao_atual->get_y();
		this->posicao_antiga->set_x(x);
		this->posicao_antiga->set_y(y);

		//atualiza posicao atual
		x--;
		this->posicao_atual->set_x(x);
	}
	else {
		return;
	}
	fprintf(log ,"At: x:%d y:%d\n", this->posicao_atual->get_x(),this->posicao_atual->get_y());
	fprintf(log ,"An: x:%d y:%d\n", this->posicao_antiga->get_x(),this->posicao_antiga->get_y());
	
}
Posicao* Jogador::get_posicao_atual(){
	return this->posicao_atual;
}
Posicao* Jogador::get_posicao_antiga(){
	return this->posicao_antiga;
}
char Jogador::get_simbolo(){
	return this->simbolo;
}

ListaDeJogadores::ListaDeJogadores(){
	this->jogadores = new std::vector<Jogador *>(0);
}
std::vector<Jogador*> *ListaDeJogadores::get_jogadores(){
	return (this->jogadores);
}
void ListaDeJogadores::adicionar_jogador(Jogador *j){
	(this->jogadores)->push_back(j);
}
void ListaDeJogadores::remover_jogador(Jogador *j){
//TO DO
}


Mapa::Mapa(int altura, int largura, ListaDePosicoes *iniciais, ListaDePosicoes *objetivo, ListaDeJogadores *jogadores){
	this->altura = altura;
	this->largura = largura;
	this->posicoes_iniciais = iniciais;
	this->posicoes_objetivo = objetivo;
	this->jogadores = jogadores;
}
int Mapa::get_altura(){
	return this->altura;
}
int Mapa::get_largura(){
	return this->largura;
}
std::vector<Posicao*> *Mapa::get_posicoes_iniciais() {
  return (this->posicoes_iniciais->get_posicoes());
}
std::vector<Posicao*> *Mapa::get_posicoes_objetivo() {
  return (this->posicoes_objetivo->get_posicoes());
}
std::vector<Jogador*> *Mapa::get_jogadores() {
  return (this->jogadores->get_jogadores());
}