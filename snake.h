#include <QWidget>
#include <QMainWindow>
#include <QKeyEvent>
#include <QPaintEvent>

#include <string>

namespace Ui {
	class Snake;
}

class Snake : public QMainWindow {
	Q_OBJECT

public:
	explicit Snake(QWidget* parent = Q_NULLPTR);
	~Snake();

	static const int widthWindow = 1080;
	static const int heightWindow = 720;
	static const int sizeBlock = 30;
	static const int sizeBorder = 15;
	static const int countRow = 15;
	static const int gameTime = 1000;

	enum Direction {
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	virtual void paintEvent(QPaintEvent* e);
	virtual void keyPressEvent(QKeyEvent* e);

	void setMainWindow();
	void setPreviewWindow();
	void initGame();
	void pauseGame();
	void gameOver();
	void spawnFruits();

private slots:
	void growSnake();

	QTimer* gameTimer;
	bool isPause;
	QPoint pointFruits;
	QList<QPoint> snake;
	Direction direction;
	int score = 0;
};