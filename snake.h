#include <QWidget>
#include <QMainWindow>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QList>
#include <QTimer>
#include <QPainter>
#include <QFont>

#include <ctime>

namespace Ui {
	class Snake;
}

class Snake : public QMainWindow {
	Q_OBJECT

public:
	explicit Snake(QWidget* parent = Q_NULLPTR);
	~Snake();

	static const int widthMainWindow = 1080;
	static const int heightMainWindow = 720;
	static const int widthGameArea = 650;
	static const int heightGameArea = 650;
	static const int widthStatusArea = 325;
	static const int heightStatusArea = 650;
	static const int sizeBlock = 30;
	static const int sizeBorder = 10;
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

/*private slots:
	void growSnake();*/

public:
	QTimer* gameTimer = new QTimer;
	bool isPause;
	int gameScore = 0;
	QPoint pointFruits;
	QPainter painter;
	QList<QPoint> snake;
	Direction direction;
};