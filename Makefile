FLAGS=-lncurses -lpthread -std=c++11

all: model

model: mainloop.cpp model.cpp model.hpp view.cpp view.cpp
	g++ -omodel mainloop.cpp model.cpp view.cpp $(FLAGS)
