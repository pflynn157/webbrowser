#pragma once

#include <string>

#include "tree.hpp"
#include "lex.hpp"

class HtmlParser {
public:
    explicit HtmlParser(std::string input);
    HtmlTree *parse();
private:
    HtmlTree *tree;
    HtmlScanner *lex;
};

