#pragma once

#include <QFile>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

#include "dom.hpp"

class HtmlParser {
public:
    explicit HtmlParser(QString path);
    void parse();
    void parse_child(QDomElement parent, DomBlock *parentBlock);
    
    DomTree *get_tree() {
        return tree;
    }
private:
    DomTree *tree;
    QDomDocument doc;
};

