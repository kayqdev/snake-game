#include "snakegame.hh"

SnakeType::SnakeType(int s_col, int s_row) {
    s_x = s_col;
    s_y = s_row;
}

SnakeType::SnakeType() {
    s_x = 0;
    s_y = 0;
}


SnakeGame::SnakeGame() {
	initscr();
	nodelay(stdscr, true); // pra cobra não para
	keypad(stdscr, true);
	noecho(); // nao exibir teclas na tela
	curs_set(0); // desliga o cursor
		        
	m_maxWidht = getmaxx(stdscr) / 2;
	m_maxHeight = getmaxy(stdscr) / 2;

	m_snake_char = 'o';

	m_food_char = 'X';
	srand(time(NULL)); //toda vez que iniciar o jogo a posicao da comida ser aleatoria
	m_insert_food();
	m_delay = 100000;
	m_direction = 'L';
	m_tail_stop = false;
	m_score = 0;

	for(int i = 0; i < m_maxWidht - 1; ++i){
		move(0, i);
		if(i == 0){
			addch('+');
		}else if(i == (m_maxWidht-2)){
			addch('+');
		}else{
			addch('-');
		}
	}
	for(int i = 1; i < m_maxHeight-1; ++i){
		move(i, 0);
		if(i == (m_maxHeight-2)){
			addch('+');
		}else{
			addch('|');
		}
	}

	for(int i = 0; i < m_maxWidht-1; ++i){
		move(m_maxHeight-2, i);
		if(i == 0){
			addch('+');
		}else if(i == (m_maxWidht - 2)){
			addch('+');
		}else{
			addch('-');
		}
	}
	for(int i = 0; i < m_maxHeight-1; ++i){
		move(i, m_maxWidht - 2);
		if(i == (m_maxHeight-2)){
			addch('+');
		}else if(i == 0){
			addch('+');
		}else{
			addch('|');
		}
	}
	 // desenha o tamanho inicial da cobra
	for(int i = 0; i < 5; ++i){
		snake.push_back(SnakeType(40 + i, 10));
	}
	// posicionar a cobra
	for(int i = 0; i < snake.size(); ++i){
		move(snake[i].s_y, snake[i].s_x);
		addch(m_snake_char);
	}
	// mostra o score
	move(m_maxHeight - 1, 0);
	printw("%d", m_score);
	move(v_food.s_y, v_food.s_x);
	addch(m_food_char);
	}
	SnakeGame::~SnakeGame(){
		nodelay(stdscr, false);
		//getch();
		endwin();
	}

	void SnakeGame::m_insert_food(){
		while(true){
			int tmpx = rand() % m_maxWidht + 1;
			int tmpy = rand() % m_maxHeight + 1;

			for(int i = 0; i < snake.size(); ++i){
				if(snake[i].s_x == tmpx && snake[i].s_y == tmpy){
					continue;
				}
			}
			if(tmpx >= m_maxWidht - 2 || tmpy >= m_maxHeight - 3){
				continue;
			}
			v_food.s_x = tmpx;
			v_food.s_y = tmpy;
			break;
			}
			move(v_food.s_y, v_food.s_x);
			addch(m_food_char);
			refresh();
		}
	void SnakeGame::movesnake(){
		int tmp = getch();
		switch(tmp){
			case KEY_LEFT:
				if(m_direction != 'R'){
					m_direction = 'L';
				}
				break;
			case KEY_UP:
				if(m_direction != 'D'){
					m_direction = 'U';
				}
				break;
			case KEY_DOWN:
				if(m_direction != 'U'){
					m_direction = 'D';
				}
				break;
			case KEY_RIGHT:
				if(m_direction != 'L'){
					m_direction = 'R';
				}
				break;
			case 'q':
				m_direction = 'Q';
				break;
			}
		if(!m_tail_stop){
			move(snake[snake.size() - 1].s_y, snake[snake.size() - 1].s_x);
			printw(" ");
			refresh();
			snake.pop_back();
		}
		if(m_direction == 'L'){
			snake.insert(snake.begin(), SnakeType(snake[0].s_x - 1, snake[0].s_y));
		}
		if(m_direction == 'R'){
			snake.insert(snake.begin(), SnakeType(snake[0].s_x + 1, snake[0].s_y));
		}
		if(m_direction == 'U'){
			snake.insert(snake.begin(), SnakeType(snake[0].s_x, snake[0].s_y - 1));
		}
		if(m_direction == 'D'){
			snake.insert(snake.begin(), SnakeType(snake[0].s_x, snake[0].s_y + 1));
		}
		move(snake[0].s_y, snake[0].s_x);
		addch(m_snake_char);
		refresh();
	}


	bool SnakeGame::_collide(){
		// colisao das bordas
		if(snake[0].s_x == 0 || snake[0].s_x == m_maxWidht - 1 || snake[0].s_y == 0 || snake[0].s_y == m_maxHeight - 2){
			return true;
		}
		for(int i = 2; i < snake.size(); ++i){
			if(snake[0].s_x == snake[i].s_x && snake[0].s_y == snake[i].s_y){
			return true;
			}
		}
		// colisao na pontuacao
		if(snake[0].s_x == v_food.s_x && snake[0].s_y == v_food.s_y){
			m_tail_stop = true;
			m_insert_food();
			m_score += 10;
			move(m_maxHeight - 1, 0);
			printw("%d", m_score);
			if((m_score % 50) == 0){
				m_delay -= 10000;
			}
		}else{
			m_tail_stop = false;
		}
		return false;
	}

	void SnakeGame::start(){
		while(true){
			if(_collide()){
				move(m_maxHeight / 2, (m_maxWidht / 2) - 4);
				printw("GAME OVER");
			  	break;
			}
			movesnake();
			usleep(m_delay);
			if(m_direction == 'Q'){
				break;
			}
		}
};
