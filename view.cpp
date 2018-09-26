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

using namespace Audio;

Sample::Sample() {

}

Sample::~Sample() {

}

bool Sample::finished() {
  if ( (this->position) >= (this->data.size())) return true;
  else return false;
}

void Sample::load(const char *filename) {
  std::string buffer;
  float fdata;
  std::ifstream input_file;
  unsigned int count = 0;

  input_file.open(filename, std::ios_base::in);
  if (!input_file) {
    std::cerr << "Arquivo " << filename << " nao encontrado" << std::endl;
    return;
  }

  while (std::getline(input_file, buffer) ) {
    std::stringstream(buffer) >> fdata;
    (this->data).push_back(fdata);
    count ++;
  }
  this->position = 0;

  std::cerr << "Total: " << count << " samples" << std::endl;

}

unsigned int Sample::get_position() {
  return this->position;
}

void Sample::set_position(unsigned int pos) {
  this->position = pos;
}

std::vector<float> Sample::get_data() {
  return this->data;
}



Player::Player() {
  this->playing = false;
  this->audio_sample = NULL;
}

void Player::pause() {
  this->playing = false;
}

Player::~Player() {

}

Sample *Player::get_data() {
  return this->audio_sample;
}

//eh chamada para carregar o buffer de audio
int mix_and_play (const void *inputBuffer, void *outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void *userData )

{
  Player *player = (Player*) userData;
  float *buffer = (float *) outputBuffer;
  Sample *s;
  s = player->get_data();
  if (s != NULL) {
    std::vector<float> data = s->get_data();
    unsigned int pos = s->get_position();

    // Fill the buffer with samples!
    for (int i=0; (i<framesPerBuffer); i++) {
      if (pos < data.size())
        buffer[i] = data[pos];
      else
        buffer[i] = 0;
      i++;
      pos+=2;
    }
    s->set_position(pos);
  }
  return 0;
}

void Player::play(Sample *audiosample) {
  this->audio_sample = audiosample;
}

void Player::init() {
  PaError err;

  err = Pa_Initialize();
  if( err != paNoError ) {
    std::cerr << "Error on Pa_Initialize()" << std::endl;
    return;
  }

  outputParameters.device = Pa_GetDefaultOutputDevice(); /* Default output device. */
  if (outputParameters.device == paNoDevice) {
    std::cerr << "Error: No default output device on Pa_GetDefaultOutputDevice()" << std::endl;
    return;
  }

  outputParameters.channelCount = 1;                     /* Mono output. */
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  err = Pa_OpenStream( &stream,
                         NULL,      /* No input. */
                         &outputParameters,
                         44100,
                         512,       /* Frames per buffer. */
                         paClipOff, /* We won't output out of range samples so don't bother clipping them. */
                         mix_and_play,
                         this );

  if( err != paNoError ) {
    std::cerr << "Error on Pa_OpenStream()" << std::endl;
    return;
  }

  err = Pa_StartStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error on Pa_StartStream()" << std::endl;
    return;
  }


}

void Player::stop() {
  PaError err;
  err = Pa_StopStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error on Pa_StopStream()" << std::endl;
    return;
  }

  err = Pa_CloseStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error on Pa_StopStream()" << std::endl;
    return;
  }

  Pa_Terminate();

}