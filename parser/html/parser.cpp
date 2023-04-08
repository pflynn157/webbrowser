#include "parser.hpp"
#include "lex.hpp"

HtmlParser::HtmlParser(std::string input) {
    
}

HtmlTree *HtmlParser::parse() {
    tree = new HtmlTree;
    
    //test
    HtmlElement *t1 = new HtmlElement("html");
    tree->add_child(t1);
    
    HtmlElement *t2 = new HtmlElement("head");
    HtmlElement *t3 = new HtmlElement("body");
    t1->add_child(t2);
    t1->add_child(t3);
    
    HtmlElement *h1 = new HtmlElement("h1");
    h1->set_text("Hello!");
    t3->add_child(h1);
    
    return tree;
}

