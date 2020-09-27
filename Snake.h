#pragma once

#include "ui_Snake.h"

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>

namespace Ui {
	class Snake;
}

class Snake : public QMainWindow {
	Q_OBJECT

public:
	explicit Snake(QWidget* parent = Q_NULLPTR);
	~Snake();

	static struct snakeNode {
		QLabel* label;
		int type;
		int x, y;
	};

private:
	void keyPressEvent(QKeyEvent* e);

	void initGame();
	void drawBorder();
	void drawGameArea();
	void showGameStatus();
	void mainMenu();
	void barMenu();
	void moveSnake();
	void checkCollision();
	void createFruits();
	void gameOver();
};