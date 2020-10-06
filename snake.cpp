#include "snake.h"

Snake::Snake(QWidget* parent)
    : QMainWindow(parent) {

    setMainWindow();
    initGame();
}

Snake::~Snake() {}

void Snake::setMainWindow() {
    this->resize(widthWindow, heightWindow);
    this->setWindowTitle("Snake");
    this->setWindowIcon(QIcon("C:\\VisualStudio\\Qt\\Snake\\img\\titleIcon.png"));
}

void Snake::initGame() {
    for (int i = 4; i >= 0; i--) {
        snake.push_back(QPoint(i, 0));
    }
    direction = LEFT;
    std::srand(time(0));
    spawnFruits();
    gameScore = 0;
    isPause = false;
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(growSnake()));
    gameTimer->start(gameTime);
}

void Snake::spawnFruits() {

}

