#include <QPainter>
#include <QBrush>
#include <QLineEdit>

#include "canvas.hpp"
#include "dom.hpp"
#include "parser.hpp"

Canvas::Canvas(QString path, QWidget *parent) {
    this->setStyleSheet("background-color: white;");
    parent->setStyleSheet("background-color: white;");
    this->parent = parent;
    
    HtmlParser *parser = new HtmlParser(path);
    parser->parse();
    tree = parser->get_tree();
    
    tree->apply_parent(this);
    tree->size(this->width(), this->height(), this);
}

Canvas::~Canvas() {

}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    tree->paint(&painter);
}

void Canvas::resizeEvent(QResizeEvent *event) {
    QSize newSize = event->size();
    tree->size(newSize.width(), newSize.height(), this);
}

