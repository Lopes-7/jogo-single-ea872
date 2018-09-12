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


Jogador::Jogador(char simbolo, Posicao *posicao_atual) {
	this->simbolo = simbolo;
	this->posicao_atual = posicao_atual;

}
void Jogador::andar(int direcao){
	int v;
	if (direcao == 0){
		//anda para frente;
		v = this->posicao_atual->get_y();
		v++;
		this->posicao_atual->set_y(v);
	}
	else if (direcao == 1){
		//anda para tras;
		v = this->posicao_atual->get_y();
		v--;
		this->posicao_atual->set_y(v);	
	}
	else if (direcao == 2){
		//anda para direita;
		v = this->posicao_atual->get_x();
		v++;
		this->posicao_atual->set_x(v);	
	}
	else if (direcao == 3){
		//anda para esquerda;
		v = this->posicao_atual->get_x();
		v--;
		this->posicao_atual->set_x(v);
	}
	else {
		return;
	}
	
}
Posicao* Jogador::get_posicao_atual(){
	return this->posicao_atual;
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