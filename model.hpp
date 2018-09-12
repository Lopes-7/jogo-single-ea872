#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

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

class ListaDePosicoes{
  private:
    std::vector<Posicao*> *posicoes;
  public:
    ListaDePosicoes();
    std::vector<Posicao*> *get_posicoes();
    void adicionar_posicao(Posicao *p);
    void remover_posicao(Posicao *p);
};

class Jogador{
  private:
    char simbolo;
    Posicao *posicao_atual;

  public:
    Jogador(char simbolo, Posicao *posicao_atual);
    void andar(int direcao);
    Posicao* get_posicao_atual();
    char get_simbolo();
};
class ListaDeJogadores{
  private:
    std::vector<Jogador*> *jogadores;
  public:
    ListaDeJogadores();
    std::vector<Jogador*> *get_jogadores();
    void adicionar_jogador(Jogador *j);
    void remover_jogador(Jogador *j);  
};
class Mapa{
  private:
    int altura, largura;
    ListaDePosicoes *posicoes_iniciais, *posicoes_objetivo;
    ListaDeJogadores *jogadores;
    
  public:
    Mapa(int altura, int largura, ListaDePosicoes *iniciais, ListaDePosicoes *objetivo, ListaDeJogadores *jogadores);
    int get_altura();
    int get_largura();
    std::vector<Posicao*> *get_posicoes_iniciais();
    std::vector<Posicao*> *get_posicoes_objetivo();
    std::vector<Jogador*> *get_jogadores();
};

#endif
