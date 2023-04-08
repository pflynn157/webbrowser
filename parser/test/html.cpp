#include <iostream>
#include <string>

#include <html/tree.hpp>
#include <html/parser.hpp>

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Error: No input specified." << std::endl;
        return 1;
    }
    
    std::string input = argv[1];
    HtmlParser parser(input);
    HtmlTree *tree = parser.parse();
    tree->print();

    return 0;
}

