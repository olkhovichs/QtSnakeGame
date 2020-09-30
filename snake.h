#include <QWidget>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout> 

#include <string>

namespace Ui {
	class Snake;
}

class Snake : public QMainWindow {
	Q_OBJECT

public:
	explicit Snake(QWidget* parent = Q_NULLPTR);
	~Snake();

private:
	static const int kWidthWindow = 1080;
	static const int kHeightWindow = 720;

	QWidget* centralWidget;
	QWidget* gameAref;
	QLabel* gameStatus;

	QHBoxLayout* mainBox;

	void setMainWindow();

};