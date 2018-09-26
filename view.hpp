#ifndef VIEW_HPP
#define VIEW_HPP

#include "model.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>
#include "portaudio.h"
#include <fstream>
#include <sstream>

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

namespace Audio {

class Sample {
  private:
    std::vector<float> data;
    unsigned int position;

  public:
    Sample();
    ~Sample();
    void load(const char *filename);
    std::vector<float> get_data();
    unsigned int get_position();
    void set_position(unsigned int pos);
    bool finished();

};


class Player {
  private:
    Sample *audio_sample;
    bool playing;

    PaStreamParameters  outputParameters;
    PaStream*           stream;
    PaError             err;
    PaTime              streamOpened;


  public:
    Player();
    ~Player();

    void init();
    void pause();
    void stop();
    void play(Sample *audiosample);
    Sample *get_data();
};

}

#endif
