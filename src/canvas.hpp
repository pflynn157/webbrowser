#pragma once

#include <QFrame>
#include <QPaintEvent>
#include <QResizeEvent>

#include "dom.hpp"

class Canvas : public QFrame {
    Q_OBJECT
public:
    Canvas();
    ~Canvas();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    DomTree *tree;
};

