#include "Snake.h"

Snake::Snake(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    setStyleSheet("background-color:grey");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(kWidth, kHeight);
    setWindowTitle("Snake");
    setWindowIcon(QIcon("titleIcon.png"));

    loadImage();
}

void Snake::loadImage() {
    dot->load("dot.png");
    head->load("head.png");
    fruit->load("fruit.png");
}


