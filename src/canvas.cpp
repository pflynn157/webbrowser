#include <QPainter>
#include <QBrush>
#include <QLineEdit>

#include "canvas.hpp"
#include "dom.hpp"
#include "parser.hpp"

Canvas::Canvas(QWidget *parent) {
    this->setStyleSheet("background-color: white;");
    this->parent = parent;
    
    HtmlParser *parser = new HtmlParser;
    parser->parse();
    tree = parser->get_tree();
    
    tree->apply_parent(this);
    tree->size(this->width(), this->height(), this);
    
    /*
    tree = new DomTree;
    DomBlock *root = new DomBlock(QColor(Qt::cyan));
    root->set_size_mode(SizeMode::Percent);
    root->set_width(1);
    tree->add_block(root);
    
    root->add_child(new DomText("Hello!", 30));
    root->add_child(new DomText("How are you?", 20));
    
    DomBlock *s1 = new DomBlock(QColor(Qt::blue));
    s1->set_size_mode(SizeMode::Percent);
    s1->set_width(1);
    s1->add_child(new DomText("Hello!!", 20));
    root->add_child(s1);
    
    s1->add_child(new DomLineEdit);
    
    DomBlock *ss1 = new DomBlock(QColor(Qt::green));
    ss1->add_child(new DomText("I am good.", 20));
    s1->add_child(ss1);
    
    DomBlock *sss1 = new DomBlock(QColor(Qt::yellow));
    sss1->add_child(new DomText("Good", 25));
    sss1->set_size_mode(SizeMode::Percent);
    sss1->set_width(1);
    ss1->add_child(sss1);
    
    root->add_child(new DomText("Hello! How are you doing today? I am excellent.", 12));
    
    tree->apply_parent(this);
    tree->size(this->width(), this->height());
    */
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

