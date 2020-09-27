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
    initGame();
}

void Snake::loadImage() {
    dot.load("dot.png");
    head.load("head.png");
    fruit.load("fruit.png");
}

void Snake::initGame() {
    x.resize(kAllDots);
    y.resize(kAllDots);
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

void Snake::checkCollision() {
    for (int i = snakeDots; i > 0; i--) {
        if ((i < 4) && (x.front() == x[i]) && (y.front() == y[i])) {
            inGame = false;
        }
    }

    if (x.front() >= kWidth) {
        inGame = false;
    }
    if (x.front() < 0) {
        inGame = false;
    }
    if (y.front() >= kHeight) {
        inGame = false;
    }
    if (y.front() < 0) {
        inGame = false;
    }

    if (!inGame) {
        killTimer(timerId);
    }
}

void Snake::timerEvent(QTimerEvent* e) {
    Q_UNUSED(e);

    if (inGame) {
        checkFruit();
        checkCollision();
        move();
    }

    repaint();
}

void Snake::locateFruit() {
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int rand = qrand() % kRandPos;
    fruitX = (rand * kSizeDot);

    rand = qrand() % kRandPos;
    fruitY = (rand * kSizeDot);
}

void Snake::keyPressEvent(QKeyEvent* e) {
    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }
    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
    if ((key == Qt::Key_Down) && (!upDirection)) {
        upDirection = true;
        leftDirection = false;
        rightDirection = false;
    }

    QWidget::keyPressEvent(e);
}

void Snake::doDrawing() {
    QPainter qp(this);

    if (inGame) {
        qp.drawImage(fruitX, fruitY, fruit);
        for (int i = 0; i < snakeDots; i++) {
            if (i == 0) {
                qp.drawImage(x[i], y[i], head);
            }
            else {
                qp.drawImage(x[i], y[i], dot);
            }
        }
    }
    else {
        gameOver(qp);
    }
}

void Snake::gameOver(QPainter& qp) {
    const QString message = "Game over";
    QFont font("Times New Roman", 15, QFont::DemiBold);
    QFontMetrics fm(font); 
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w / 2, h / 2));
    qp.drawText(-textWidth / 2, 0, message);
}

void Snake::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    doDrawing();
}