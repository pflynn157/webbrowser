#pragma once

#include <string>
#include <vector>
#include <iostream>

//
// HTML elements
//
class HtmlElement {
public:
    explicit HtmlElement(std::string tag_name) {
        this->tag_name = tag_name;
    }
    
    void add_child(HtmlElement *child) {
        children.push_back(child);
    }
    
    void set_text(std::string text) {
        this->text = text;
    }

    virtual void print(int indent) {
        for (int i = 0; i<indent; i++) std::cout << " ";
        std::cout << "<" << tag_name << ">";
        std::cout << text;
        
        if (children.size() > 0) {
            std::cout << std::endl;
            for (HtmlElement *element : children) {
                element->print(indent + 2);
            }
        }
        
        if (children.size() > 0)
            for (int i = 0; i<indent; i++) std::cout << " ";
        std::cout << "</" << tag_name << ">" << std::endl;
    }
protected:
    std::vector<HtmlElement *> children;
    std::string tag_name;
    std::string text = "";
};

//
// The base of all HTML trees
//
class HtmlTree {
public:
    HtmlTree() {}
    
    void add_child(HtmlElement *child) {
        children.push_back(child);
    }
    
    void print() {
        std::cout << "<!--HTML-->" << std::endl;
        std::cout << std::endl;
        for (HtmlElement *element : children) {
            element->print(0);
        }
    }
protected:
    std::vector<HtmlElement *> children;
};

