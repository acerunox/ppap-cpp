/*
Exercise 01: Allow underscores in the calculator’s variable names.

Exercise 02: Provide an assignment operator, =, so that you can change the value of a variable after you introduce it using let.

Exercise 03: Provide named constants that you really can’t change the value of.

Exercise 04: The get_value(), set_value(), is_declared(), and define_name() functions all operate on the variable var_table.
             Define a class called Symbol_table with a member var_table of type vector<Variable> and member functions get(), set(), is_declared(), and declare(). 
             Rewrite the calculator to use a variable of type Symbol_table.
             //NOTE: I wrote the calculator in a different way, so I had to do this differently too.

Exercise 05: Modify Token_stream::get() to return Token(print) when it sees a newline.
             This implies looking for whitespace characters and treating newline ('\n') specially. 

Exercise 06: Part of what every program should do is to provide some way of helping its user. 
             Have the calculator print out some instructions for how to use the calculator if the user presses the H key (both upper- and lowercase).

Exercise 07: Change the q and h commands to be quit and help, respectively.

Exercise 08: Fix the calculator grammar.
             Add whatever you feel is needed to that comment as the first comment of the calculator program and its overall comment.

Exercise 09: Suggest three improvements (not mentioned in this chapter) to the calculator. 
             Implement one of them.
             //Decided to implement logarithm calculation

Exercise 10: Modify the calculator to operate on ints (only); give errors for overflow and underflow.
*/

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

enum class CalculatorSymbol { ZERO = '0', ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DOT = '.', 
                              NAME = 'A', NUMBER = 'N', 
                              DECLARE = 'D', CONST = 'C', POWER = 'P', SQUARE_ROOT = 'S', LOGARITHM = 'L', COMMA = ',',
                              UNDERSCORE = '_', EQUALS = '=', PRINT = ';', QUIT = 'Q', HELP = 'H',
                              OPEN_PARENTHESES = '(', CLOSED_PARENTHESES = ')', OPEN_CURLY = '{', CLOSED_CURLY = '}', 
                              PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/', FACTORIAL = '!' };

std::istream &operator>> (std::istream &is, CalculatorSymbol &symbol)
{
    char input;
    do
    {
        is.get(input);
        if (input == '\n') 
        {
            symbol = CalculatorSymbol::PRINT;
            return is;
        }
    } while (isspace(input));
    
    
    if (!is)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }

    symbol = CalculatorSymbol(input);
    return is;
}

std::ostream &operator<< (std::ostream &os, const CalculatorSymbol &symbol)
{
    return os << char(symbol);
}

inline void ThrowError(std::string message) { throw std::runtime_error(message); }

inline bool IsOverflowing(int a, int b, CalculatorSymbol oper)
{
    switch (oper)
    {
    case CalculatorSymbol::PLUS:
        return ((b > 0) && (a > INT_MAX - b)) || ((b < 0) && (a < INT_MIN - b));
    case CalculatorSymbol::MINUS:
        return ((b < 0) && (a > INT_MAX + b)) || ((b > 0) && (a < INT_MIN + b));
    case CalculatorSymbol::MULTIPLY:
        return ((a == -1) && (b == INT_MIN)) || ((b == -1) && (a == INT_MIN)) || (a > INT_MAX / b) || (a < INT_MIN / b);
    case CalculatorSymbol::DIVIDE:
        return ((b == -1) && (a == INT_MIN));
    }
}

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

struct Token
{
    CalculatorSymbol kind;
    int value;
    std::string name;

    Token(CalculatorSymbol kind) : kind(kind), value(0) {}
    Token(CalculatorSymbol kind, int value) : kind(kind), value(value) {}
    Token(CalculatorSymbol kind, std::string name) : kind(kind), name(name) {}
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

TokenStream::TokenStream() : isBufferFull(false), buffer(CalculatorSymbol::ZERO) {}

Token TokenStream::Get()
{
    if (isBufferFull)
    {
        isBufferFull = false;
        return buffer;
    }

    CalculatorSymbol symbol;
    std::cin >> symbol;

    switch (symbol)
    {
        case CalculatorSymbol::PRINT:
        case CalculatorSymbol::OPEN_PARENTHESES: case CalculatorSymbol::CLOSED_PARENTHESES: 
        case CalculatorSymbol::OPEN_CURLY: case CalculatorSymbol::CLOSED_CURLY:
        case CalculatorSymbol::COMMA: case CalculatorSymbol::EQUALS:
        case CalculatorSymbol::PLUS: case CalculatorSymbol::MINUS: case CalculatorSymbol::MULTIPLY: case CalculatorSymbol::DIVIDE: case CalculatorSymbol::FACTORIAL: 
            return Token(symbol);

        case CalculatorSymbol::DOT:
        case CalculatorSymbol::ZERO: case CalculatorSymbol::ONE: case CalculatorSymbol::TWO: case CalculatorSymbol::THREE: case CalculatorSymbol::FOUR:
        case CalculatorSymbol::FIVE: case CalculatorSymbol::SIX: case CalculatorSymbol::SEVEN: case CalculatorSymbol::EIGHT: case CalculatorSymbol::NINE:
        {
            std::cin.putback(char(symbol));
            int value = 0;
            std::cin >> value;
            return Token(CalculatorSymbol::NUMBER, value);
        }

        default:
            char character = char(symbol);
            if (isalpha(character))
            {
                std::string input;
                do 
                {
                    input += character;
                }
                while (std::cin.get(character) && (isalpha(character) || isdigit(character) || character == char(CalculatorSymbol::UNDERSCORE)));
                std::cin.unget();

                if (input == Keys::declaration) return Token(CalculatorSymbol::DECLARE);
                if (input == Keys::constant) return Token(CalculatorSymbol::CONST);
                if (input == Keys::squareRoot) return Token(CalculatorSymbol::SQUARE_ROOT);
                if (input == Keys::power) return Token(CalculatorSymbol::POWER);
                if (input == Keys::logarithm) return Token(CalculatorSymbol::LOGARITHM);
                if (input == Keys::quit) return Token(CalculatorSymbol::QUIT);
                if (input == Keys::help) return Token(CalculatorSymbol::HELP);
                return Token(CalculatorSymbol::NAME, input);
            }
            else
            {
                std::ostringstream outStream;
                outStream << "[ERROR] " << char(symbol) << " is not an allowed symbol.";
                ThrowError(outStream.str());
            }
    }
}

void TokenStream::Putback(const Token &token)
{
    if (isBufferFull) ThrowError("[ERROR] Buffer already full.");
    isBufferFull = true;
    buffer = token;
}

void TokenStream::ClearUntilSymbol(const CalculatorSymbol &symbol)
{
    if (isBufferFull && buffer.kind == symbol)
    {
        isBufferFull = false;
        return;
    }
    isBufferFull = false;
    
    CalculatorSymbol currentSymbol;
    while (std::cin >> currentSymbol)
    {
        if (currentSymbol == symbol) return;
    }
}

struct Variable
{
    std::string name;
    int value;
    bool isConst;
    Variable(std::string name, int value, bool isConst) : name(name), value(value), isConst(isConst) {}
};

class Calculator
{
    public:
        int Calculate();
        Token GetToken();
        void PutbackToken(const Token &token);
        void PrintHelp();
        void ClearErrors();

        void DeclareVariable();
        int GetVariableValue(const std::string &name);
        void SetVariableValue(const std::string &name, const int &value);

    private:
        TokenStream tokenStream;
        std::vector<Variable> variables;

        int Primary();
        int Term();
        int Expression();
        int Factorial(int value);

        bool IsVariableDeclared(const std::string &name);
        bool IsVariableConstant(const Variable &variable);
};

int Calculator::Calculate() { return Expression(); }

Token Calculator::GetToken() { return tokenStream.Get(); }

void Calculator::PutbackToken(const Token &token) { tokenStream.Putback(token); }

void Calculator::DeclareVariable()
{
    bool isConstant = false;
    Token token = tokenStream.Get();
    if (token.kind == CalculatorSymbol::CONST) 
    {
        isConstant = true;
        token = tokenStream.Get();
    }
    else isConstant = false;

    if (token.kind != CalculatorSymbol::NAME) ThrowError("[ERROR] Name expected in declaration.");
    std::string name = token.name;

    token = tokenStream.Get();
    if (token.kind != CalculatorSymbol::EQUALS)
    {
        std::ostringstream outStream;
        outStream << "[ERROR] Expected '" << char(CalculatorSymbol::EQUALS) << "' in declaration of " << name << '.';
        ThrowError(outStream.str());
    }
    
    int value = Expression();
    if (IsVariableDeclared(name))
    {
        std::ostringstream outStream;
        outStream << "[ERROR] Variable '" << name << "' already exists.";
        ThrowError(outStream.str());
    }
    else 
    {
        variables.push_back(Variable(name, value, isConstant));
        std::cout << name << ' ' << char(CalculatorSymbol::EQUALS) << ' ' << value << '\n';
    }
}

int Calculator::GetVariableValue(const std::string &name)
{
    for (Variable var : variables)
    {
        if (var.name == name) return var.value;
    }

    ThrowError("[ERROR] Variable '" + name + "' couldn't be found.");
}

void Calculator::SetVariableValue(const std::string &name, const int &value)
{
    for (Variable &var : variables)
    {
        if (var.name == name)
        {
            if (!IsVariableConstant(var)) 
            {
                var.value = value;
                return;
            }
            else ThrowError("[ERROR] Variable '" + name + "' is constant and cannot be changed.");
        }
    }

    ThrowError("[ERROR] Variable '" + name + "' couldn't be found.");
}

bool Calculator::IsVariableDeclared(const std::string &name)
{
    for (Variable var : variables)
    {
        if (var.name == name) return true;
    }
    return false;
}

bool Calculator::IsVariableConstant(const Variable &variable) { return variable.isConst; }

void Calculator::PrintHelp()
{
    std::cout << "\n--- HELP PAGE ---\n"
        << "This simple calculator can do several different types of operations:\n"
        << "- Addition" << std::setw(15) << CalculatorSymbol::PLUS << '\n'
        << "- Subtraction" << std::setw(12) << CalculatorSymbol::MINUS << '\n'
        << "- Division" << std::setw(15) << CalculatorSymbol::DIVIDE << '\n'
        << "- Multiplication" << std::setw(9) << CalculatorSymbol::MULTIPLY << '\n'
        << "- Power" << std::setw(20) << Keys::power << "(base,exponent)\n"
        << "- Square root" << std::setw(15) << Keys::squareRoot << "(x)\n"
        << "- Declare a variable" << std::setw(7) << Keys::declaration << " name = value\n"
        << "- Declare a constant" << std::setw(7) << Keys::declaration << ' ' << Keys::constant << " name = value\n"
        << "You can also use " << CalculatorSymbol::OPEN_PARENTHESES << CalculatorSymbol::CLOSED_PARENTHESES
        << " as well as " << CalculatorSymbol::OPEN_CURLY << CalculatorSymbol::CLOSED_CURLY << ".\n"
        << "To end a single expression press ENTER.\n"
        << "To calculate different expressions at once, separate them with '" << CalculatorSymbol::PRINT << "'.\n\n";/**/
}

void Calculator::ClearErrors() { tokenStream.ClearUntilSymbol(CalculatorSymbol::PRINT); }

int Calculator::Primary()
{
    int result = 0;
    Token token = tokenStream.Get();
    switch (token.kind)
    {
        case CalculatorSymbol::OPEN_CURLY:
            result = Expression();
            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::CLOSED_CURLY) 
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::CLOSED_CURLY) << "'.";
                ThrowError(outStream.str());
            }
            break;

        case CalculatorSymbol::OPEN_PARENTHESES:
            result = Expression();
            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES) 
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::CLOSED_PARENTHESES) << "'.";
                ThrowError(outStream.str());
            }
            break;

        case CalculatorSymbol::SQUARE_ROOT:
        {
            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::OPEN_PARENTHESES)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::OPEN_PARENTHESES) << "'.";
                ThrowError(outStream.str());
            }

            int radicand = Expression();
            if (radicand < 0) ThrowError("[ERROR] Cannot calculate square root for negative numbers.");
            result = std::sqrt(radicand);

            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::CLOSED_PARENTHESES) << "'.";
                ThrowError(outStream.str());
            }
            break;
        }
        
        case CalculatorSymbol::POWER:
        {
            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::OPEN_PARENTHESES)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::OPEN_PARENTHESES) << "'.";
                ThrowError(outStream.str());
            }

            int base = Expression();
            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::COMMA)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::COMMA) << "'.";
                ThrowError(outStream.str());
            }
            int exponent = Expression();
            result = std::pow(base, exponent);

            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::CLOSED_PARENTHESES) << "'.";
                ThrowError(outStream.str());
            }
            break;
        }

        case CalculatorSymbol::LOGARITHM:
        {
            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::OPEN_PARENTHESES)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::OPEN_PARENTHESES) << "'.";
                ThrowError(outStream.str());
            }

            int base = Expression();
            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::COMMA)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::COMMA) << "'.";
                ThrowError(outStream.str());
            }
            int value = Expression();
            if (IsOverflowing(std::log(value), std::log(base), CalculatorSymbol::DIVIDE)) ThrowError("[ERROR] Overflow occurred.");
            result = std::log(value) / std::log(base);

            token = tokenStream.Get();
            if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES)
            {
                std::ostringstream outStream;
                outStream << "[ERROR] Expected '" << char(CalculatorSymbol::CLOSED_PARENTHESES) << "'.";
                ThrowError(outStream.str());
            }
            break;
        }

        case CalculatorSymbol::NUMBER: case CalculatorSymbol::PLUS:
            result = token.value;
            break;

        case CalculatorSymbol::MINUS:
            result = -Primary();
            break;

        case CalculatorSymbol::NAME:
        {
            std::string variableName = token.name;
            token = tokenStream.Get();

            if (token.kind == CalculatorSymbol::EQUALS)
            {
                int value = Expression();
                SetVariableValue(variableName, value);
                result = value;
                break;
            }
            else
            {
                tokenStream.Putback(token);
                result = GetVariableValue(variableName);
                break;
            }
        }

        default:
            ThrowError("[ERROR] Expected a primary.");
    }

    token = tokenStream.Get();
    if (token.kind == CalculatorSymbol::FACTORIAL) return Factorial(result);
    else
    {
        tokenStream.Putback(token);
        return result;
    }
}

int Calculator::Term()
{
    int left = Primary();
    Token token = tokenStream.Get();

    while (true)
    {
        switch (token.kind)
        {
            case CalculatorSymbol::MULTIPLY:
            {
                int value = Primary();
                if (IsOverflowing(left, value, CalculatorSymbol::MULTIPLY)) ThrowError("[ERROR] Overflow occurred.");
                left *= value;
                token = tokenStream.Get();
                break;
            }
            
            case CalculatorSymbol::DIVIDE:
            {
                int denominator = Primary();
                if (denominator == 0) throw std::runtime_error("[ERROR] Cannot divide by zero.");
                if (IsOverflowing(left, denominator, CalculatorSymbol::DIVIDE)) ThrowError("[ERROR] Overflow occurred.");
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

int Calculator::Expression()
{
    int left = Term();
    Token token = tokenStream.Get();

    while (true)
    {
        switch (token.kind)
        {
            case CalculatorSymbol::PLUS:
            {
                int value = Term();
                if (IsOverflowing(left, value, CalculatorSymbol::PLUS)) ThrowError("[ERROR] Overflow occurred.");
                left += value;
                token = tokenStream.Get();
                break;
            }

            case CalculatorSymbol::MINUS:
            {
                int value = Term();
                if (IsOverflowing(left, value, CalculatorSymbol::MINUS)) ThrowError("[ERROR] Overflow occurred.");
                left -= value;
                token = tokenStream.Get();
                break;
            }

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
    
    for (int i = 1; i <= value; ++i) 
    {
        if (IsOverflowing(result, i, CalculatorSymbol::MULTIPLY)) ThrowError("[ERROR] Overflow occurred.");
        result *= i;
    }
    return result;
}

int main()
{
    std::printf("Please enter expressions.\nType '%s' for help and '%s' to quit.\n", 
                Keys::help.c_str(), Keys::quit.c_str());
    
    Calculator calculator;
    while (true) 
    {
        try 
        {
            std::cout << "> ";
            Token token = calculator.GetToken();
            while (token.kind == CalculatorSymbol::PRINT) token = calculator.GetToken();  // "Eat" print characters until next expression
            if (token.kind == CalculatorSymbol::QUIT) return EXIT_SUCCESS;
            
            switch (token.kind)
            {
                case CalculatorSymbol::HELP:
                    calculator.PrintHelp();
                    break;

                case CalculatorSymbol::DECLARE:
                    calculator.DeclareVariable();
                    break;
                
                default:
                {
                    calculator.PutbackToken(token);
                    int result = 0;
                    result = calculator.Calculate();
                    std::cout << char(CalculatorSymbol::EQUALS) << ' ' << result << '\n';
                }
            }
        }
        catch (const std::runtime_error &err) 
        {
            std::cerr << err.what() << '\n'; 
            calculator.ClearErrors();
        }
    }
}