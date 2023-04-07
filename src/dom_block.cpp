#include "dom.hpp"

DomBlock::DomBlock(QColor color) {
    this->w = 0;
    this->h = 0;
    this->color = color;
    this->w_pct = 1;
    this->size_mode = SizeMode::Percent;
}

DomBlock::DomBlock() {
    this->w = 0;
    this->h = 0;
    this->w_pct = 1;
    this->size_mode = SizeMode::Percent;
}

void DomBlock::set_size_mode(SizeMode mode) {
    this->size_mode = mode;
}

void DomBlock::set_width(int w) {
    if (size_mode == SizeMode::Percent) {
        this->w_pct = w;
    } else {
        this->w = w;
    }
}

void DomBlock::add_child(DomBlock *child) {
    children.append(child);
}

int DomBlock::get_height() {
    return h;
}

int DomBlock::get_width() {
    return w;
}

void DomBlock::_set_margin(int ml, int mr, int mt, int mb) {
    this->margin_left = ml;
    this->margin_right = mr;
    this->margin_top = mt;
    this->margin_bottom = mb;
}

void DomBlock::_clear_sizes() {
    if (size_mode != SizeMode::Percent) {
        this->w = 0;
    }
    
    this->h = 0;
    for (DomBlock *block : children) {
        block->clear_sizes();
    }
}

void DomBlock::_size(int sx, int sy, int w_max, int h_max) {
    this->x = sx + margin_left;
    this->y = sy + margin_top;
    
    // If we do not have absolute sizing on, reset the height
    if (size_mode != SizeMode::Absolute) {
        this->h = margin_bottom;
    } else {
        this->h += margin_bottom;
    }
    
    // Calculate width
    if (size_mode == SizeMode::Percent) {
        this->w = (w_pct * w_max) - (margin_right * 2);
    }
    
    // Calculate sub blocks
    int bx = sx;
    int by = sy;
    for (DomBlock *block : children) {
        block->size(bx, by, w, h);
        by += block->get_height();
        if (block->get_width() > this->get_width()) {
            this->w = (block->get_width()) - (margin_right * 2);
        }
        this->h += block->get_height();
    }
}

void DomBlock::_paint(QPainter *painter) {
    int x = this->x;
    int y = this->y;
    int w = this->w;
    int h = this->h;
    QRect rect(x, y, w, h);

    painter->setPen(color);
    painter->setBrush(QBrush(color));
    painter->drawRect(rect);
    
    for (DomBlock *block : children) {
        block->paint(painter);
    }
}

