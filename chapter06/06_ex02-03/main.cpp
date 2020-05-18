/*
Exercise 02: Add the ability to use {} as well as () in the program, so that {(4+5)*6} / (3+4) will be a valid expression.

Exercise 03: Add a factorial operator: use a suffix ! operator to represent “factorial.” 
             For example, the expression 7! means 7 * 6 * 5* 4 * 3 * 2 * 1. 
             Make ! bind tighter than * and /; that is, 7*8! means 7*(8!) rather than (7*8)!. 
             Begin by modifying the grammar to account for a higher-level operator. 
             To agree with the standard mathematical definition of factorial, let 0! evaluate to 1.
*/

#include <iostream>
#include <stdexcept>
#include <string>

enum class Symbol { ZERO = '0', ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
                    NUMBER = '8', DOT = '.', PRINT = '=', QUIT = 'x', 
                    OPEN_PARENTHESES = '(', CLOSED_PARENTHESES = ')', OPEN_CURLY = '{', CLOSED_CURLY = '}',
                    ADD = '+', SUBTRACT = '-', MULTIPLY = '*', DIVIDE = '/', FACTORIAL = '!' };

std::istream &operator>> (std::istream &is, Symbol &symbol)
{
    char input;
    is >> input;
    
    if (!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    symbol = Symbol(input);
    return is;
}

struct Token
{
    Symbol kind;
    double value;
    Token(Symbol kind) : kind(kind), value(0) {}
    Token(Symbol kind, double value) : kind(kind), value(value) {}
};

class TokenStream
{
    public:
        TokenStream();
        Token Get();
        void Putback(const Token &token);
    private:
        bool isBufferFull;
        Token buffer;
};

TokenStream::TokenStream() : isBufferFull(false), buffer(Symbol::ZERO) {}

Token TokenStream::Get()
{
    if (isBufferFull)
    {
        isBufferFull = false;
        return buffer;
    }

    Symbol input;
    std::cin >> input;

    switch (input)
    {
        case Symbol::PRINT: case Symbol::QUIT:
        case Symbol::OPEN_PARENTHESES: case Symbol::CLOSED_PARENTHESES: 
        case Symbol::OPEN_CURLY: case Symbol::CLOSED_CURLY: 
        case Symbol::ADD: case Symbol::SUBTRACT: case Symbol::MULTIPLY: case Symbol::DIVIDE: case Symbol::FACTORIAL: 
            return Token(input);

        case Symbol::DOT:
        case Symbol::ZERO: case Symbol::ONE: case Symbol::TWO: case Symbol::THREE: case Symbol::FOUR:
        case Symbol::FIVE: case Symbol::SIX: case Symbol::SEVEN: case Symbol::EIGHT: case Symbol::NINE:
        {
            std::cin.putback(char(input));
            double value = 0;
            std::cin >> value;
            return Token(Symbol::NUMBER, value);
        }

        default:
            throw std::runtime_error("[ERROR] Bad token.");
    }
}

void TokenStream::Putback(const Token &token)
{
    if (isBufferFull) throw std::runtime_error("[ERROR] Buffer already full.");
    isBufferFull = true;
    buffer = token;
}

class Calculator
{
    public:
        double Calculate();
        Token GetToken();
        void PutbackToken(const Token &token);

    private:
        TokenStream tokenStream;

        double Primary();
        double Term();
        double Expression();
        int Factorial(int value);
};

double Calculator::Calculate() { return Expression(); }

Token Calculator::GetToken() { return tokenStream.Get(); }

void Calculator::PutbackToken(const Token &token) { tokenStream.Putback(token); }

double Calculator::Primary()
{
    double value = 0;
    Token token = tokenStream.Get();
    switch (token.kind)
    {
        case Symbol::OPEN_CURLY:
        {
            value = Expression();
            token = tokenStream.Get();
            if (token.kind != Symbol::CLOSED_CURLY) 
            {
                int length = std::snprintf(NULL, 0, "[ERROR] Expected '%c', received '%c'.", char(Symbol::CLOSED_CURLY), char(token.kind));
                char buffer [length + 1];
                std::sprintf(buffer, "[ERROR] Expected '%c', received '%c'.", char(Symbol::CLOSED_CURLY), char(token.kind));
                throw std::runtime_error(buffer);
            }
            break;
        }

        case Symbol::OPEN_PARENTHESES:
        {
            value = Expression();
            token = tokenStream.Get();
            if (token.kind != Symbol::CLOSED_PARENTHESES) 
            {
                int length = std::snprintf(NULL, 0, "[ERROR] Expected '%c'.", char(Symbol::CLOSED_PARENTHESES));
                char buffer [length + 1];
                std::sprintf(buffer, "[ERROR] Expected '%c'.", char(Symbol::CLOSED_PARENTHESES));
                throw std::runtime_error(buffer);
            }
            break;
        }

        case Symbol::NUMBER:
        {
            value = token.value;
            break;
        }

        default:
            throw std::runtime_error("[ERROR] Expected a primary.");
    }

    token = tokenStream.Get();
    if (token.kind == Symbol::FACTORIAL) return Factorial(value);
    else
    {
        tokenStream.Putback(token);
        return value;
    }
}

double Calculator::Term()
{
    double left = Primary();
    Token token = tokenStream.Get();

    while (true)
    {
        switch (token.kind)
        {
            case Symbol::MULTIPLY:
                left *= Primary();
                token = tokenStream.Get();
                break;
            
            case Symbol::DIVIDE:
            {
                double denominator = Primary();
                if (denominator == 0) throw std::runtime_error("[ERROR] Cannot divide by zero.");
                left /= denominator;
                token = tokenStream.Get();
                break;
            }

            default:
                tokenStream.Putback(token);
                return left;
        }
    }
}

double Calculator::Expression()
{
    double left = Term();
    Token token = tokenStream.Get();

    while (true)
    {
        switch (token.kind)
        {
            case Symbol::ADD:
                left += Term();
                token = tokenStream.Get();
                break;

            case Symbol::SUBTRACT:
                left -= Term();
                token = tokenStream.Get();
                break;

            default:
                tokenStream.Putback(token);
                return left;
        }
    }
}

int Calculator::Factorial(int value)
{
    int result = 1;
    if (value == 0) return 1;
    
    for (int i = 1; i <= value; ++i) result *= i;
    return result;
}

int main()
{
    std::cout << "Welcome to our simple calculator.\n"
              << "Please enter expressions using floating-point numbers.\n";
    std::printf("You can use %c, %c, %c and %c. Use '%c' to quit and '%c' to end an expression.\n", 
                char(Symbol::ADD), char(Symbol::SUBTRACT), char(Symbol::MULTIPLY), char(Symbol::DIVIDE), char(Symbol::QUIT), char(Symbol::PRINT));
    
    try
    {
        Calculator calculator;
        double val = 0;
        while (true) {
            Token token = calculator.GetToken();

            if (token.kind == Symbol::QUIT) break;
            if (token.kind == Symbol::PRINT)
                std::cout << "=" << val << '\n';
            else
            {
                calculator.PutbackToken(token);
                val = calculator.Calculate();
            }
        }
    }
    catch (const std::runtime_error &err) {
        std::cerr << err.what() << '\n'; 
        return EXIT_FAILURE;
    }
}