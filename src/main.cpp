#include <iostream>

#include <QApplication>

#include "window.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Error: Please input a file." << std::endl;
        return 1;
    }
    
    QApplication app(argc, argv);
    
    Window window(argv[1]);
    window.show();
    
    return app.exec();
}

