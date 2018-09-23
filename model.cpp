#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

#include "model.hpp"

//implementacao da classe Posicao
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

//implementacao da classe ListaDePosicoes
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

//implementacao da classe Jogador
Jogador::Jogador(char simbolo, Posicao *posicao_atual, Posicao *posicao_antiga) {
	this->simbolo = simbolo;
	this->posicao_atual = posicao_atual;
	this->posicao_antiga = posicao_antiga;

}
//funcao que modifica a posicao atual do jogador ou obstaculo com base no parametro direcao
void Jogador::andar(int direcao){	
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
		//anda para baixo;
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
Posicao* Jogador::set_posicao_atual(int x, int y){
	this->posicao_atual->set_x(x);
	this->posicao_atual->set_y(y);
	
}

//implementacao da classe ListaDeJogadores
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

//implementacao da classe mapa
Mapa::Mapa(int altura, int largura, ListaDePosicoes *iniciais, ListaDePosicoes *objetivo, ListaDeJogadores *jogadores, ListaDeJogadores *obstaculos){
	this->altura = altura;
	this->largura = largura;
	this->posicoes_iniciais = iniciais;
	this->posicoes_objetivo = objetivo;
	this->jogadores = jogadores;
	this->obstaculos = obstaculos;
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
std::vector<Jogador*> *Mapa::get_obstaculos() {
  return (this->obstaculos->get_jogadores());
}
//funcao para verificar se houve uma colisao de um jogador com o limite do mapa
int Mapa::verificar_colisao_parede(Jogador *j, int direcao){
	int intencao;
	
	//verifica se o jogador quer andar para a direita
	if (direcao == 0){
		intencao = j->get_posicao_atual()->get_y() + 1;
		if (intencao == get_largura()){
			return 1;
		}
	}
	//verifica se o jogador quer andar para a esquerda
	else if (direcao == 1){
		intencao = j->get_posicao_atual()->get_y() - 1;
		if (intencao == 0){
			return 1;
		}
	}
	//verifica se o jogador quer andar para baixo
	else if (direcao == 2){
		intencao = j->get_posicao_atual()->get_x() + 1;
		if (intencao == get_altura()){
			return 1;
		}
	}
	//verifica se o jogador quer andar para cima
	else if (direcao == 3){
		intencao = j->get_posicao_atual()->get_x() - 1;
		if (intencao == 0){
			return 1;
		}
	}
	else{
		//se o parametro informado nao for 0,1,2 ou 3 retorna 3 para indicar um erro
		return 3;
	}
	//caso nao haja colisao retorna 0
	return 0;
}

//funcao que verifica se houve colisao entre o jogador e um obstaculo
int Mapa::verificar_colisao_obstaculo(Jogador *j){
	std::vector<Jogador*> *obstaculos = this->get_obstaculos();
	int i;
	//pegando coordenadas da posicao atual do jogador
	int x_jogador = j->get_posicao_atual()->get_x();
	int y_jogador = j->get_posicao_atual()->get_y();
	
	//compara as coordenadas com todas as coordenadas dos obstaculos
	for (i = 0; i < obstaculos->size();i++){
    	int x = (int) (*obstaculos)[i]->get_posicao_atual()->get_x();
    	int y = (int) (*obstaculos)[i]->get_posicao_atual()->get_y();
    	//se as duas coordenadas forem iguais retorna 1 para indicar que houve uma colisao
    	if (x == x_jogador && y == y_jogador){
    		return 1;
    	}
	}
	//retorna 0 se nao houve colisao
	return 0;	
}

//funcao que verifica se a posicao do jogador é igual a alguma posicao objetivo
int Mapa::verificar_vitoria(Jogador *j){
	std::vector<Posicao*> *posicoes_objetivo = this->get_posicoes_objetivo();
	int i;
	int x_jogador = j->get_posicao_atual()->get_x();
	int y_jogador = j->get_posicao_atual()->get_y();
	for (i = 0; i < posicoes_objetivo->size();i++){
    	int x = (int) (*posicoes_objetivo)[i]->get_x();
    	int y = (int) (*posicoes_objetivo)[i]->get_y();
    	if (x ==  x_jogador && y == y_jogador){
    		return 1;
    	}
	}
	return 0;
}

//funcao que move todos os obstaculos da lista de obstaculos a partir do parametro direcao
void Mapa::mover_obstaculos(int direcao){
	std::vector<Jogador*> *obstaculos = this->get_obstaculos();
	int i;
	
	for (i = 0; i < obstaculos->size();i++){
    	(*obstaculos)[i]->andar(direcao);
	}
}

//thread responsavel por mover todos os obstaculos de um mapa recebido como parametro
void thread_manipular_obstaculos(Mapa *m, int *control ){
	int tempo = 0;
	//se a thread estiver ativa:
	while((*control) == 1){
		//move obstaculos com um certo padrao de direcoes (0, 1, 2, 3)
		m->mover_obstaculos(tempo % 4);
		tempo++;
		std::this_thread::sleep_for (std::chrono::milliseconds(1000));
	}
	return;
}

//implementacao da classe ManipuladorDeObstaculos
ManipuladorDeObstaculos::ManipuladorDeObstaculos(Mapa *m){
	this->m = m;
}
//funcao que inicializa a execucao da thread para mover os obstaculos
void ManipuladorDeObstaculos::init(){
	this->rodando = 1;
	std::thread newthread(thread_manipular_obstaculos, this->m, &(this->rodando));
  	(this->mo_thread).swap(newthread);
}
//funcao para parar a execucao da thread
void ManipuladorDeObstaculos::stop(){
	this->rodando = 0;
}

