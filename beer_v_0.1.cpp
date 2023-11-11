#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include <cctype>
#include ".\extensions\parser.hpp"
#include ".\extensions\tokenization.hpp"
#include ".\extensions\generator.hpp"

using std::cout;
using string = std::string; 

int main(int argc, char* argv[])
{
    cout << "Brew Beer Black Bush\n";

    if (argc != 2)
    {
        std::cerr << "Brew Beer 0.1 \n";
        std::cerr << "Incorrect usage: Expected <file.bbs> \n";
        return EXIT_FAILURE;
    }

    std::fstream input(argv[1], std::ios::in);

    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    input.close();

    string contents = contents_stream.str();

    Tokenizer tokenizer(contents); 

    std::vector<_Token_> tokens = tokenizer.tokenize();

    tokenParser parser(std::move(tokens));
    std::optional <nodes::__return__node> tree = parser.parse();
    
    Generator generator(tree.value());

    if (!tree.has_value())
    {
        std::cerr << "No tree in " << argv[1] << ".\n";
        exit(1);
    }
    
    std::fstream file("../out.asm", std::ios::out);
    file << generator.generate();
    file.close();

    return EXIT_SUCCESS;
}
