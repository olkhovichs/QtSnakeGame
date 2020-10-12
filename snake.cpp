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
    for (int i = 3; i >= 0; i--) {
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
    QPainter painter(this);
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

void Snake::keyPressEvent(QKeyEvent* e) { // unfinished
    switch (e->key()) {
    case Qt::Key_W:
        if (direction != DOWN) {
            direction = UP;
        }
    case Qt::Key_S:
        if (direction != UP) {
            direction = DOWN;
        }
    case Qt::Key_D:
        if (direction != LEFT) {
            direction = RIGHT;
        }
    case Qt::Key_A:
        if (direction != RIGHT) {
            direction = LEFT;
        }
    case Qt::Key_Tab:
       // pauseGame();
        break;
    default:
        break;
    }
}

bool Snake::gameOver() {
    int x = snake.front().x();
    int y = snake.front().y();
    if (x < 0 || x > countRow - 1 || y < 0 || y > countRow - 1) { // вне игрового поля
        return true;
    }
    for (int i = 3; i < snake.size(); i++) {
        if (snake[i] == snake.front()) {
            return true;
        }
    }
    return false;
}

void Snake::growSnake() {
    switch (direction) {
    case UP:
        snake.push_front(QPoint(snake.front().x(), snake.front().y() - 1));
        break;
    case DOWN:
        snake.push_front(QPoint(snake.front().x(), snake.front().y() + 1));
        break;
    case LEFT:
        snake.push_front(QPoint(snake.front().x() - 1, snake.front().y()));
        break;
    case RIGHT:
        snake.push_front(QPoint(snake.front().x() + 1, snake.front().y()));
        break;
    default:
        break;
    }

    if (snake.contains(pointFruits)) {
        gameScore++;
        spawnFruits();
    }
    else {
        snake.pop_back();
    }
    if (gameOver()) {
        gameTimer->stop();
        QMessageBox::information(this, "Failed!", "Game over!");
        return; // 
    }
    update();
}

void Snake::pauseGame() {
    if (isPause) {
        isPause = !isPause;
        gameTimer->start();
    }
    else {
        isPause = !isPause;
        gameTimer->stop();
    }
}