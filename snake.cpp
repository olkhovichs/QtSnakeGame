#include "snake.h"

Snake::Snake(QWidget* parent)
    : QMainWindow(parent) {

    this->resize(kWidthWindow, kHeightWindow);
    this->setWindowTitle("Snake");
    this->setWindowIcon(QIcon("C:\\VisualStudio\\Qt\\Snake\\img\\titleIcon.png"));

    initGame();
}

Snake::~Snake() {}

void Snake::initGame() {

}