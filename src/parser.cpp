#include <QColor>

#include <iostream>

#include "parser.hpp"
#include "dom.hpp"

HtmlParser::HtmlParser(QString path) {
    tree = new DomTree;
    doc = QDomDocument("first");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cout << "Unable to open file." << std::endl;
        return;
    }
    
    if (!doc.setContent(&file)) {
        std::cout << "Unable to load content." << std::endl;
        file.close();
        return;
    }
    
    file.close();
}

void HtmlParser::parse() {
    DomBlock *root = new DomBlock(QColor(Qt::white));
    tree->add_block(root);
    QDomElement rootElement = doc.documentElement();
    parse_child(rootElement, root);
}

void HtmlParser::parse_child(QDomElement parent, DomBlock *parentBlock) {
    DomBlock *block;
    
    // Heading tags
    if (parent.tagName() == "h1") {
        block = new DomText(parent.text(), 32);
    } else if (parent.tagName() == "h2") {
        block = new DomText(parent.text(), 24);
    } else if (parent.tagName() == "h3") {
        block = new DomText(parent.text(), 20);
    } else if (parent.tagName() == "h4") {
        block = new DomText(parent.text(), 16);
    } else if (parent.tagName() == "h5") {
        block = new DomText(parent.text(), 12);
    } else if (parent.tagName() == "h6") {
        block = new DomText(parent.text(), 10);
        
    // paragraph tags
    } else if (parent.tagName() == "p") {
        std::cout << parent.text().toStdString() << std::endl;
        block = new DomText(parent.text().trimmed(), 14);
    
    // Default to an empty div
    } else {
        block = new DomBlock(QColor(Qt::white));
    }
    
    // Check for style tags
    QString style = parent.attribute("style", "");
    if (style != "") {
        std::cout << "STYLE: " << style.toStdString() << std::endl;
        QStringList parts = style.split(";");
        for (QString part : parts) {
            QStringList attrs = part.split(":");
            QString key = attrs[0];
            QString value = attrs[1];
            std::cout << "\t" << key.toStdString() << " = " << value.toStdString() << std::endl;
            
            if (key == "color") {
                block->set_color(QColor(value));
            } else if (key == "background-color") {
                block->set_bg_color(QColor(value));
            }
        }
    }
    
    parentBlock->add_child(block);

    QDomNode node = parent.firstChild();
    while (!node.isNull()) {
        QDomElement element = node.toElement();
        if (element.isNull()) {
            node = node.nextSibling();
            continue;
        }
        
        parse_child(element, block);
        node = node.nextSibling();
    }
}

