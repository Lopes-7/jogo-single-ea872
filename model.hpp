#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

//classe para identificar a posicao de jogadores e obstaculos
class Posicao{
  private:
    int x, y;
  public:
    Posicao(int x, int y);
    int get_x();
    int get_y();
    void set_x(int novo);
    void set_y(int novo);
};
//classe para agrupar posicoes
class ListaDePosicoes{
  private:
    std::vector<Posicao*> *posicoes;
  public:
    ListaDePosicoes();
    std::vector<Posicao*> *get_posicoes();
    void adicionar_posicao(Posicao *p);
    void remover_posicao(Posicao *p);
    void hard_copy(ListaDePosicoes *ldp);
};

//classe usada para identificar um jogador ou um obstaculo no mapa
class Jogador{
  private:
    char simbolo;
    Posicao *posicao_atual;
    Posicao *posicao_antiga;

  public:
    Jogador(char simbolo, Posicao *posicao_atual, Posicao *posicao_antiga);
    void andar(int direcao);
    Posicao* get_posicao_atual();
    Posicao* get_posicao_antiga();
    char get_simbolo();
    Posicao* set_posicao_atual(int x, int y);

};
//classe para agrupar jogadores e obstaculos
class ListaDeJogadores{
  private:
    std::vector<Jogador*> *jogadores;
  public:
    ListaDeJogadores();
    std::vector<Jogador*> *get_jogadores();
    void adicionar_jogador(Jogador *j);
    void remover_jogador(Jogador *j);  
};

//classe que contem uma lista de posicoes iniciais dos jogadores, posicoes objetivo e lista de jogadores e obstaculos
class Mapa{
  private:
    int altura, largura;
    ListaDePosicoes *posicoes_iniciais, *posicoes_objetivo;
    ListaDeJogadores *jogadores, *obstaculos;
    
  public:
    Mapa(int altura, int largura, ListaDePosicoes *iniciais, ListaDePosicoes *objetivo, ListaDeJogadores *jogadores, ListaDeJogadores *obstaculos);
    int get_altura();
    int get_largura();
    std::vector<Posicao*> *get_posicoes_iniciais();
    std::vector<Posicao*> *get_posicoes_objetivo();
    std::vector<Jogador*> *get_jogadores();
    std::vector<Jogador*> *get_obstaculos();
    int verificar_colisao_parede(Jogador *j, int direcao);
    int verificar_colisao_obstaculo(Jogador *j);
    int verificar_vitoria(Jogador *j);
    void mover_obstaculos(int direcao);

};

//thread para mover os obstaculos
void thread_manipular_obstaculos(Mapa *m, int* control);
//classe para mover os obstaculos
class ManipuladorDeObstaculos{
  private:
    Mapa *m;
    //variavel que ve se a thread esta ativa
    int rodando;
    //varaivel para guardar a thread
    std::thread mo_thread;

  public:
    ManipuladorDeObstaculos(Mapa *m);
    ~ManipuladorDeObstaculos();
    void init();
    void stop();

};
#endif
