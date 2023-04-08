#include "parser.hpp"
#include "lex.hpp"

HtmlParser::HtmlParser(std::string input) {
    lex = new HtmlScanner(input);
}

HtmlTree *HtmlParser::parse() {
    tree = new HtmlTree;
    
    HtmlToken token = lex->get_next();
    while (token != HtmlToken::Eof) {
        switch (token) {
            case HtmlToken::Text: {
                std::cout << "TEXT: " << lex->get_text() << std::endl;
            } break;
            
            case HtmlToken::Attr: {
                std::cout << "ATTR: {" << lex->get_text() << "}" << std::endl;
            } break;
            
            case HtmlToken::Ws: std::cout << " (WS) " << std::endl; break;
            case HtmlToken::Nl: std::cout << " (NL) " << std::endl; break;

            case HtmlToken::OpenTagStart: std::cout << "<" << std::endl; break;
            case HtmlToken::CloseTagStart: std::cout << "</" << std::endl; break;
            case HtmlToken::TagEnd: std::cout << ">" << std::endl; break;
            case HtmlToken::Assign: std::cout << "=" << std::endl; break;
            
            default: std::cout << "??" << std::endl;
        }
        
        token = lex->get_next();
    }
    
    //test
    /*HtmlElement *t1 = new HtmlElement("html");
    tree->add_child(t1);
    
    HtmlElement *t2 = new HtmlElement("head");
    HtmlElement *t3 = new HtmlElement("body");
    t1->add_child(t2);
    t1->add_child(t3);
    
    HtmlElement *h1 = new HtmlElement("h1");
    h1->set_text("Hello!");
    t3->add_child(h1);*/
    
    return tree;
}

