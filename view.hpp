#ifndef VIEW_HPP
#define VIEW_HPP

#include "model.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>

class Tela {
  private:
    Mapa *m;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(Mapa *m, int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void stop();
    void init();
    void update();
};


#endif
