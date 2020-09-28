#include <qwidget.h>
#include <qmainwindow.h>
#include <QKeyEvent>
#include <qlabel.h>

#include <string>

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
	static const int kWidthWindow = 1080;
	static const int kHeightWindow = 720;
	static const int kSizeBlock = 35;

	bool leftDirection;
	bool rightDirection;
	bool upDirection;
	bool downDirection;

	int level;
	int score;

	QString* viewText;

	//void keyPressEvent(QKeyEvent* e);

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