#pragma once
#include "./Token.hpp"
#include <istream>
#include <string>

namespace Keywords
{
    const std::string declaration = "let";
    const std::string from = "from";
    const std::string to = "to";
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
    TokenStream(std::istream &instream = std::cin);
    Token Get();
    void Putback(const Token &token);
    void ClearUntilSymbol(const CalculatorSymbol &symbol);

    void InputSwitch(std::streambuf* buf) { std::cin.rdbuf(buf); }
    std::streambuf *BackupStreamBuffer() { return inputStream.rdbuf(); }
private:
    std::istream &inputStream;
    bool isBufferFull;
    Token buffer;
};