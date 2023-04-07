#pragma once

#include <QPainter>
#include <QColor>
#include <QVector>
#include <QLineEdit>

enum class SizeMode {
    Pixel,
    Percent,
    Absolute
};

class DomBlock {
public:
    explicit DomBlock(QColor color);
    explicit DomBlock();
    
    void set_size_mode(SizeMode mode);
    void set_width(int w);
    
    void add_child(DomBlock *child);
    
    int get_height();
    int get_width();
    
    virtual void set_color(QColor color) {}
    
    virtual void set_bg_color(QColor color) {
        this->color = color;
    }
    
    virtual void clear_sizes() {
        _clear_sizes();
    }
    
    virtual void size(int sx, int sy, int w_max, int h_max) {
        _size(sx, sy, w_max, h_max);
    }
    
    virtual void apply_parent(QWidget *parent) {
        for (DomBlock *block : children) {
            block->apply_parent(parent);
        }
    }
    
    virtual void paint(QPainter *painter) {
        _paint(painter);
    }
protected:
    void _clear_sizes();
    void _size(int sx, int sy, int w_max, int h_max);
    void _paint(QPainter *painter);
    
    // Variables
    QColor color;
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    int w_pct = 0;
    SizeMode size_mode = SizeMode::Pixel;
    QVector<DomBlock *> children;
};

class DomText : public DomBlock {
public:
    explicit DomText(QString text, int font_size) {
        this->x = 0;
        this->y = 0;
        this->text = text;
        this->size_mode = SizeMode::Absolute;
        this->font = QFont("Times", font_size);
        this->color = QColor(Qt::black);
        
        update_sizing();
    }
    
    void set_color(QColor color) {
        this->color = color;
    }
    
    void clear_sizes() {}
    
    void paint(QPainter *painter) {
        painter->setPen(color);
        painter->setFont(font);
        painter->drawText(this->x, this->y, this->w, this->h, Qt::AlignLeft, text);
    }
protected:
    void update_sizing() {
        QFontMetrics metrics(font);
        QRect bounds = metrics.boundingRect(text);
        this->w = bounds.width();
        this->h = bounds.height();
    }

    QFont font;
    QString text;
    QColor color;
};

class DomLineEdit : public DomBlock {
public:
    explicit DomLineEdit() {
        input = new QLineEdit;
        this->w = 150;
        this->h = 30;
        //input->setParent(parent);
        this->size_mode = SizeMode::Absolute;
    }
    
    void apply_parent(QWidget *parent) {
        input->setParent(parent);
        input->resize(this->w, this->h);
    }
    
    void clear_sizes() {}
    
    void paint(QPainter *painter) {
        input->move(this->x, this->y);
        //input->resize(this->w, this->h);
    }
protected:
    QLineEdit *input;
};

class DomTree {
public:
    explicit DomTree() {}
    
    void add_block(DomBlock *block) {
        children.append(block);
    }
    
    void apply_parent(QWidget *parent) {
        for (DomBlock *block : children) {
            block->apply_parent(parent);
        }
    }
    
    void size(int w_max, int h_max) {
        for (DomBlock *block : children) block->clear_sizes();
    
        // Calculate all sizes
        int bx = 0;
        int by = 0;
        for (DomBlock *block : children) {
            block->size(bx, by, w_max, h_max);
            by += block->get_height();
        }
    }
    
    void paint(QPainter *painter) {
        // Paint everything
        for (DomBlock *block : children) {
            block->paint(painter);
        }   
    }
private:
    QVector<DomBlock *> children;
};

