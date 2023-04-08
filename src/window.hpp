#pragma once

#include <QMainWindow>

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window(QString path);
    ~Window();
};

