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
    
    void add_attribute(std::string name, std::string value) {
        attributes.push_back(std::make_pair(name, value));
    }
    
    void set_text(std::string text) {
        this->text = text;
    }

    virtual void print(int indent) {
        for (int i = 0; i<indent; i++) std::cout << " ";
        std::cout << "<" << tag_name;
        if (attributes.size() > 0) {
            for (auto attr : attributes) {
                std::cout << " ";
                std::cout << attr.first << "=\"" << attr.second << "\"";
            }
        }
        std::cout << ">";
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
    std::vector<std::pair<std::string, std::string>> attributes;
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

