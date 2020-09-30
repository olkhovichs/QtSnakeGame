#include "snake.h"

Snake::Snake(QWidget* parent)
    : QMainWindow(parent) {

    setMainWindow();
    
}

Snake::~Snake() {}

void Snake::setMainWindow() {
    this->resize(kWidthWindow, kHeightWindow);
    this->setWindowTitle("Snake");
    this->setWindowIcon(QIcon("C:\\VisualStudio\\Qt\\Snake\\img\\titleIcon.png"));
    this->setCentralWidget(centralWidget);
    mainBox->setSpacing(5);
    mainBox->addWidget(gameAref);
    mainBox->addWidget(gameStatus);

    this->centralWidget->setLayout(mainBox);
}