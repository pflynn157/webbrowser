#include <iostream>

#include "lex.hpp"

HtmlScanner::HtmlScanner(std::string input) {
    reader = std::ifstream(input);
    if (!reader.is_open()) {
        std::cerr << "Unable to open input file." << std::endl;
    }
}

std::string HtmlScanner::get_text() {
    std::string text = "";
    if (!text_stack.empty()) {
        text = text_stack.top();
        text_stack.pop();
        return text;
    }
    return text;
}

HtmlToken HtmlScanner::get_next() {
    // Check the token stack
    if (!token_stack.empty()) {
        HtmlToken token = token_stack.top();
        token_stack.pop();
        return token;
    }
    
    // Check to see if we're at the end of the file
    if (reader.eof()) {
        return HtmlToken::Eof;
    }
    
    while (!reader.eof()) {
        char c = reader.get();
        HtmlToken token;
        
        switch (c) {
            // Attributes
            case '\"': {
                std::string text = "";
                char c2 = reader.get();
                while (c2 != '\"') {
                    text += c2;
                    c2 = reader.get();
                }
                
                token = HtmlToken::Attr;
                text_stack.push(text);
            } break;
        
            // Opening tag
            case '<': {
                char c2 = reader.get();
                if (c2 == '/') {
                    token = HtmlToken::CloseTagStart;
                } else {
                    reader.unget();
                    token = HtmlToken::OpenTagStart;
                }
            } break;
            
            // Closing tag
            case '>': {
                token = HtmlToken::TagEnd;
            } break;
            
            // Whitespace
            case ' ': {
                token = HtmlToken::Ws;
            } break;
            
            case '\n': {
                token = HtmlToken::Nl;
            } break;
            
            // Assign (=)
            case '=': {
                token = HtmlToken::Assign;
            } break;
            
            // Otherwise
            default: {
                buffer += c;
                continue;
            }
        }
        
        // Check to see if we have any text
        if (buffer.length() > 0) {
            token_stack.push(token);
            
            text_stack.push(buffer);
            buffer = "";
            return HtmlToken::Text;
        }
        
        return token;
    }
    
    return HtmlToken::Eof;
}

