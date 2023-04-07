#include "window.hpp"
#include "canvas.hpp"

Window::Window() {
    this->setWindowTitle("Browser");
    this->resize(900, 500);
    
    Canvas *canvas = new Canvas;
    this->setCentralWidget(canvas);
}

Window::~Window() {
}

