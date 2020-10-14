#include <QWidget>
#include <QMainWindow>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QList>
#include <QTimer>
#include <QPainter>
#include <QFont>
#include <QMessageBox>

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
	static const int widthGameArea = 700;
	static const int heightGameArea = 700;
	static const int sizeBlock = 35;
	static const int sizeBorder = 10; // границы
	static const int countRow = 20; // столбцы
	static const int gameTime = 500;

	enum Direction {
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	struct Colors {
		QColor black = Qt::black;
		QColor green = Qt::green;
		QColor red = Qt::red;
		QColor yellow = Qt::yellow;
		QColor blue = Qt::blue;
	}color;

	virtual void paintEvent(QPaintEvent* e);
	virtual void keyPressEvent(QKeyEvent* e);

	void setMainWindow();
	void setPreviewWindow();
	void initGame();
	void pauseGame();
	bool gameOver();
	void spawnFruits();

private slots:
	void growSnake();

public:
	QTimer* gameTimer;
	bool isPause;
	int gameScore = 0;
	QPoint pointFruits;
	QList<QPoint> snake;
	Direction direction;
};