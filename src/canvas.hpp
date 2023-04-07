#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>

#include "dom.hpp"

class Canvas : public QWidget {
    Q_OBJECT
public:
    Canvas(QWidget *parent);
    ~Canvas();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    DomTree *tree;
    QWidget *parent;
};

