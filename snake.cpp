#include "snake.h"

Snake::Snake(QWidget* parent)
    : QMainWindow(parent) {

    setMainWindow();
    setPreviewWindow();
    initGame();
}

Snake::~Snake() {}

void Snake::setMainWindow() {
    this->resize(widthMainWindow, heightMainWindow);
    this->setWindowTitle("Snake");
    this->setWindowIcon(QIcon("C:\\VisualStudio\\Qt\\Snake\\img\\titleIcon.png"));
}

void Snake::setPreviewWindow() {
    quit = new QPushButton("Quit", this);
    quit->setStyleSheet("QPushButton{ background-color: rgb(143,122,102); border-radius: 10px; font: bold; color: white; }");
    quit->setFont(QFont("Sans", 15));
    quit->setGeometry(800, 100, 100, 100);
    connect(quit, SIGNAL(clicked()), this, SLOT(pauseGame()));
    
}

void Snake::initGame() {
    for (int i = 4; i >= 0; i--) {
        snake.push_back(QPoint(i, 0));
    }
    direction = RIGHT;
    std::srand(time(0));
    spawnFruits();
    gameScore = 0;
    isPause = false;
    gameTimer = new QTimer;
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

QColor Snake::setRandomColor() {
    int randColor = rand() % 7;
    switch (randColor) {
    case 0:
        return color.red;
        break;
    case 1:
        return color.yellow;
        break;
    case 2:
        return color.green;
        break;
    case 3:
        return color.yellow.darker(150);
        break;
    case 4:
        return color.red.lighter(150);
        break;
    case 5:
        return color.magenta;
        break;
    case 6: 
        return color.magenta.darker(150);
    }
}

void Snake::paintEvent(QPaintEvent* e) {
    QPainter painter(this);

    // main area
    painter.setBrush(color.green.lighter(150)); 
    painter.setPen(color.black);
    painter.drawRect(sizeBorder, sizeBorder, widthGameArea, heightGameArea);

    // snake
    painter.setBrush(color.green.darker(150));
    painter.setPen(color.black);
    for (int i = 0; i < snake.size(); i++) {
        painter.drawRect(sizeBorder + snake[i].x() * sizeBlock,
            sizeBorder + snake[i].y() * sizeBlock,
            sizeBlock,
            sizeBlock);
    }

    // fruits
        painter.setBrush(randColor);
        painter.drawEllipse(sizeBorder + pointFruits.x() * sizeBlock,
            sizeBorder + pointFruits.y() * sizeBlock,
            sizeBlock,
            sizeBlock);
    // status area
    painter.setPen(color.black);
    painter.setFont(QFont("Courier", 15));
    painter.drawText(widthGameArea + (widthMainWindow - widthGameArea),
        heightGameArea / 3,
        "Score" + QString::number(gameScore));
}

void Snake::keyPressEvent(QKeyEvent* e) { // unfinished
    switch (e->key()) {
    case Qt::Key_Up:
        if (direction != DOWN) {
            direction = UP;
        }
        break;
    case Qt::Key_Down:
        if (direction != UP) {
            direction = DOWN;
        }
        break;
    case Qt::Key_Right:
        if (direction != LEFT) {
            direction = RIGHT;
        }
        break;
    case Qt::Key_Left:
        if (direction != RIGHT) {
            direction = LEFT;
        }
        break;
    case Qt::Key_Tab:
        pauseGame();
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
        randColor = setRandomColor();
        gameTimer->start(gameTime -= 10);
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