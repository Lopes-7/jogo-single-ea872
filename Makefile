FLAGS=-lncurses -lpthread -lportaudio -std=c++11

all: model

model: mainloop.cpp model.cpp model.hpp view.cpp view.hpp control.cpp control.hpp
	g++ -omodel mainloop.cpp model.cpp view.cpp control.cpp $(FLAGS)
