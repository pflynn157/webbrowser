#pragma once

#include <fstream>
#include <stack>

enum class HtmlToken {
    Text,
    Attr,
    Ws,
    Nl,

    OpenTagStart,
    CloseTagStart,
    TagEnd,
    Assign,
    
    Eof
};

class HtmlScanner {
public:
    explicit HtmlScanner(std::string input);
    std::string get_text();
    HtmlToken get_next();
private:
    std::ifstream reader;
    std::string buffer = "";
    //std::string text;
    
    // Token stacks
    // These will always be parallel
    std::stack<HtmlToken> token_stack;
    std::stack<std::string> text_stack;
};

