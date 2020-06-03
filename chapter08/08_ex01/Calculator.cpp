#include "Calculator.h"
#include "../../lib/utilities.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Option Calculator::Statement()
{
    Token token = tokenStream.Get();
    while (token.kind == CalculatorSymbol::PRINT) token = tokenStream.Get();  // "Eat" print characters until next statement

    switch (token.kind)
    {
        case CalculatorSymbol::QUIT:
            return Option::QUIT;

        case CalculatorSymbol::HELP:
            return Option::HELP;

        case CalculatorSymbol::DECLARE:
            return Option::DECLARE;
        
        default:
            tokenStream.Putback(token);
            return Option::CALCULATE;
    }
}

int Calculator::Calculate() { return Expression(); }

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
        << "To calculate different expressions at once, separate them with '" << CalculatorSymbol::PRINT << "'.\n\n";
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

    default:
        ThrowError("[ERROR] Unrecognized operator.");
    }
}