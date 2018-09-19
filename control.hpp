#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

void threadfun (char *keybuffer, int *control);

class Teclado {
  private:
    char ultima_captura;
    int rodando;

    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};

#endif