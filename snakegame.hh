#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <iostream> // time e rand
#include <ncurses.h> // para as funcoes da ncurses
#include <vector> // logica das coordenadas
#include <unistd.h> // usleep()
#include <stdlib.h>

using namespace std;

// Logica pra armazenar as coordenadas da cobrinha
struct SnakeType {
	int s_x, s_y;
	SnakeType(int s_col, int s_row);
	SnakeType();
};

class SnakeGame {
	protected:
		int m_maxWidht; // largura da tela
		int m_maxHeight; // altura da tela
		vector<SnakeType> snake;
		char m_snake_char;
		SnakeType v_food;
		char m_food_char;
		int m_delay;
		char m_direction;
		bool m_tail_stop;
		int m_score;
	public:
		SnakeGame();
		~SnakeGame();
		void m_insert_food();
		void movesnake();
		bool _collide();
		void start();
};
#endif
