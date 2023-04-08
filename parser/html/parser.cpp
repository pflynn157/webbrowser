#include <iostream>

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
            case HtmlToken::OpenTagStart: {
                HtmlElement *element = parse_tag();
                tree->add_child(element);
            } break;
            
            default: {}
        }
        
        token = lex->get_next();
    }
    
    /*HtmlToken token = lex->get_next();
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
    }*/
    
    //test
    /*HtmlElement *t1 = new HtmlElement("html");
    tree->add_child(t1);
    
    HtmlElement *t2 = new HtmlElement("head");
    HtmlElement *t3 = new HtmlElement("body");
    t1->add_child(t2);
    t1->add_child(t3);
    
    HtmlElement *h1 = new HtmlElement("h1");
    h1->add_attribute("style", "color:blue");
    h1->set_text("Hello!");
    t3->add_child(h1);*/
    
    return tree;
}

HtmlElement *HtmlParser::parse_tag() {
    HtmlToken token = lex->get_next();
    if (token != HtmlToken::Text) {
        std::cerr << "Error: Expected tag name." << std::endl;
        return nullptr;
    }
    HtmlElement *element = new HtmlElement(lex->get_text());
    
    // See if we have an attribute
    token = lex->get_next();
    while (token != HtmlToken::TagEnd) {
        if (token == HtmlToken::Ws) {
            HtmlToken name_token = lex->get_next();
            std::string attr_name = lex->get_text();
            
            HtmlToken assign_token = lex->get_next();
            
            HtmlToken value_token = lex->get_next();
            std::string attr_value = lex->get_text();
            
            element->add_attribute(attr_name, attr_value);
        }
        
        token = lex->get_next();
    }
    
    // Now parse any body we might have
    token = lex->get_next();
    std::string buffer = "";
    while (token != HtmlToken::CloseTagStart) {
        if (token == HtmlToken::OpenTagStart) {
            if (buffer.length() > 0) {
                HtmlElement *text_element = new HtmlElement("");
                text_element->set_text(buffer);
                element->add_child(text_element);
                buffer = "";
            }
            
            HtmlElement *child_element = parse_tag();
            element->add_child(child_element);
            
        } else if (token == HtmlToken::Ws) {
            buffer += " ";
        } else if (token == HtmlToken::Nl) {
            buffer += "\n";
        } else {
            buffer += lex->get_text();
        }
        
        token = lex->get_next();
    }
    
    if (buffer.length() > 0) {
        HtmlElement *text_element = new HtmlElement("");
        text_element->set_text(buffer);
        element->add_child(text_element);
        buffer = "";
    }
    
    // Parse close tag
    token = lex->get_next();
    while (token != HtmlToken::TagEnd) {
        token = lex->get_next();
    }
    
    return element;
}

