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

void Snake::initGame() {
    snakeDots = 3;
    for (int i = 0; i < snakeDots; i++) {
        x[i] = 5 - i * 10;
        y[i] = 50;
    }

    locateFruit();

    timerId = startTimer(kDelay);
}

void Snake::checkFruit() {
    if ((x.front() == fruitX) && (y.front() == fruitY)) {
        snakeDots++;
        locateFruit();
    }
}

void Snake::move() {
    for (int i = snakeDots; i > 0; i--) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (leftDirection) {
        x.front() -= kSizeDot;
    }

    if (rightDirection) {
        x.front() += kSizeDot;
    }

    if (upDirection) {
        x.front() -= kSizeDot;
    }

    if (downDirection) {
        x.front() += kSizeDot;
    }
}