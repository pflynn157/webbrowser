#include <QScrollArea>

#include "window.hpp"
#include "canvas.hpp"

Window::Window() {
    this->setWindowTitle("Browser");
    this->resize(900, 500);
    
    QScrollArea *area = new QScrollArea;
    area->setStyleSheet("background-color: white;");
    Canvas *canvas = new Canvas(this);
    area->setWidgetResizable(true);
    area->setWidget(canvas);
    this->setCentralWidget(area);
}

Window::~Window() {
}

