#pra#pragma once

#include "ui_Snake.h"

#include <QtWidgets/QMainWindow>

#include <vector>

namespace Ui {
    class Snake;
}

class Snake : public QMainWindow {

    Q_OBJECT

public:
    explicit Snake(QWidget* parent = Q_NULLPTR);

private:
    Ui::SnakeClass ui;

    static const int kWidth = 500;
    static const int kHeight = 500;
    static const int kSizeDot = 10;
    static const int kAllDots = kWidth * kHeight;
    static const int kRandPosition = 20;
    static const int kDelay = 150;

    std::vector<int> x;
    std::vector<int> y;


};