#include "snake.h"

Snake::Snake(QWidget* parent)
    : QMainWindow(parent) {

    setMainWindow();
    initGame();
}

Snake::~Snake() {}

void Snake::setMainWindow() {
    this->resize(widthMainWindow, heightMainWindow);
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
    pointFruits.setX(rand() % countRow);
    pointFruits.setY(rand() % countRow);
    if (snake.contains(pointFruits)) {
        spawnFruits();
    }
}

void Snake::paintEvent(QPaintEvent* e) {
    // main area
    painter.setBrush(Qt::black); 
    painter.setPen(Qt::blue);
    painter.drawRect(sizeBorder, sizeBorder, widthGameArea, heightGameArea);

    // snake
    painter.setBrush(Qt::green);
    painter.setPen(Qt::blue);
    for (int i = 0; i < snake.size(); i++) {
        painter.drawRect(sizeBorder + snake[i].x() * sizeBlock,
            sizeBorder + snake[i].y() * sizeBlock,
            sizeBlock,
            sizeBlock);
    }

    // fruits
    painter.setBrush(Qt::red);
    painter.drawEllipse(sizeBorder + pointFruits.x() * sizeBlock, 
        sizeBorder + pointFruits.y() * sizeBlock, 
        sizeBlock, 
        sizeBlock);

    // status area
    painter.setPen(Qt::black);
    painter.setFont(QFont("Courier", 15));
    painter.drawText(sizeBorder * 2 + widthGameArea + 20,
        sizeBorder * 2 + heightGameArea + 20,
        "Score" + QString::number(gameScore));
}

