#pragma once
#include "./Token.hpp"
#include <string>

namespace Keys
{
    const std::string declaration = "let";
    const std::string constant = "const";
    const std::string squareRoot = "sqrt";
    const std::string power = "pow";
    const std::string logarithm = "log";
    const std::string quit = "quit";
    const std::string help = "help";
};

class TokenStream
{
public:
    TokenStream();
    Token Get();
    void Putback(const Token &token);
    void ClearUntilSymbol(const CalculatorSymbol &symbol);

private:
    bool isBufferFull;
    Token buffer;
};