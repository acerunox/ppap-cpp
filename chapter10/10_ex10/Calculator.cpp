#include "./Calculator.hpp"
#include "./TokenStream.hpp"
#include "./Token.hpp"
#include "../../lib/utilities.h"
#include <fstream>
#include <iomanip>
#include <iostream>

namespace CalculatorLib
{
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

        if (token.kind != CalculatorSymbol::NAME) ThrowError("Name expected in declaration.");
        std::string name = token.name;

        token = tokenStream.Get();
        if (token.kind != CalculatorSymbol::EQUALS) ThrowError("Expected '" + char(CalculatorSymbol::EQUALS), "' in declaration of " + name + '.');
        
        int value = Expression();
        if (IsVariableDeclared(name)) ThrowError("Variable '" + name + "' already exists.");
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

        ThrowError("Variable '" + name + "' couldn't be found.");
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
                else ThrowError("Variable '" + name + "' is constant and cannot be changed.");
            }
        }

        ThrowError("Variable '" + name + "' couldn't be found.");
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

    void Calculator::ReadFromFile(std::ostream &outputStream)
    {
        Token token = tokenStream.Get();
        if (token.kind != CalculatorSymbol::NAME) ThrowError("Name expected as input file name.");
        std::string fileName = token.name;

        std::ifstream inputFileStream{ fileName };
        if (!inputFileStream) ThrowError("Failed to open input file '" + fileName + "'.");
        std::streambuf *bufferBackup = tokenStream.BackupStreamBuffer();
        tokenStream.InputSwitch(inputFileStream.rdbuf());

        while (inputFileStream.peek() != EOF)
        {
            try
            {
                Token token = tokenStream.Get();

                while (token.kind == CalculatorSymbol::PRINT) token = tokenStream.Get();
                switch (token.kind)
                {
                case CalculatorSymbol::DECLARE:
                    DeclareVariable();
                    break;

                default:
                    tokenStream.Putback(token);
                    outputStream << "= " << Calculate() << '\n';
                    break;
                }
            }
            catch (std::runtime_error &err)
            {
                outputStream << "[ERROR] " << err.what() << '\n';
                tokenStream.ClearUntilSymbol(CalculatorSymbol::PRINT);
            }
        }

        tokenStream.InputSwitch(bufferBackup);
    }

    void Calculator::WriteToFile()
    {
        Token token = tokenStream.Get();
        if (token.kind != CalculatorSymbol::NAME) ThrowError("Name expected as input file name.");
        std::string fileName = token.name;

        std::ofstream outputFileStream{ fileName };
        if (!outputFileStream) ThrowError("Failed to open output file '" + fileName + "'.");
        std::cout << "Writing to file '" + fileName + "'. Type 'quit' to stop." << '\n';

        while (true)
        {
            try
            {
                std::cout << ">> ";
                Token token = tokenStream.Get();

                while (token.kind == CalculatorSymbol::PRINT) token = tokenStream.Get();
                switch (token.kind)
                {
                case CalculatorSymbol::DECLARE:
                    DeclareVariable();
                    break;

                case CalculatorSymbol::FROM:
                    ReadFromFile(outputFileStream);
                    break;

                case CalculatorSymbol::QUIT:
                    return;

                default:
                    tokenStream.Putback(token);
                    outputFileStream << "= " << Calculate() << '\n';
                    break;
                }
            }
            catch (std::runtime_error &err)
            {
                outputFileStream << "[ERROR] " << err.what() << '\n';
                tokenStream.ClearUntilSymbol(CalculatorSymbol::PRINT);
            }
        }
    }

    void Calculator::PrintHelp()
    {
        std::cout << "\n--- HELP PAGE ---\n"
            << "This simple calculator can do several different types of operations:\n"
            << "- Addition" << std::setw(15) << CalculatorSymbol::PLUS << '\n'
            << "- Subtraction" << std::setw(12) << CalculatorSymbol::MINUS << '\n'
            << "- Division" << std::setw(15) << CalculatorSymbol::DIVIDE << '\n'
            << "- Multiplication" << std::setw(9) << CalculatorSymbol::MULTIPLY << '\n'
            << "- Power" << std::setw(20) << Keywords::power << "(base,exponent)\n"
            << "- Square root" << std::setw(15) << Keywords::squareRoot << "(x)\n"
            << "- Declare a variable" << std::setw(7) << Keywords::declaration << " name = value\n"
            << "- Read from file" << std::setw(12) << Keywords::from << " filename\n"
            << "- Write to file" << std::setw(11) << Keywords::to << " filename\n"
            << "- Declare a constant" << std::setw(7) << Keywords::declaration << ' ' << Keywords::constant << " name = value\n"
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
                if (token.kind != CalculatorSymbol::CLOSED_CURLY) ThrowError("Expected '" + char(CalculatorSymbol::CLOSED_CURLY), "'.");
                break;

            case CalculatorSymbol::OPEN_PARENTHESES:
                result = Expression();
                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES) ThrowError("Expected '" + char(CalculatorSymbol::CLOSED_PARENTHESES), "'.");
                break;

            case CalculatorSymbol::SQUARE_ROOT:
            {
                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::OPEN_PARENTHESES) ThrowError("Expected '" + char(CalculatorSymbol::OPEN_PARENTHESES), "'.");

                int radicand = Expression();
                if (radicand < 0) ThrowError("Cannot calculate square root for negative numbers.");
                result = std::sqrt(radicand);

                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES) ThrowError("Expected '" + char(CalculatorSymbol::CLOSED_PARENTHESES), "'.");
                break;
            }
            
            case CalculatorSymbol::POWER:
            {
                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::OPEN_PARENTHESES) ThrowError("Expected '" + char(CalculatorSymbol::OPEN_PARENTHESES), "'.");

                int base = Expression();
                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::COMMA) ThrowError("Expected '" + char(CalculatorSymbol::COMMA), "'.");
                int exponent = Expression();
                result = std::pow(base, exponent);

                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES) ThrowError("Expected '" + char(CalculatorSymbol::CLOSED_PARENTHESES), "'.");
                break;
            }

            case CalculatorSymbol::LOGARITHM:
            {
                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::OPEN_PARENTHESES) ThrowError("Expected '" + char(CalculatorSymbol::OPEN_PARENTHESES), "'.");

                int base = Expression();
                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::COMMA) ThrowError("Expected '" + char(CalculatorSymbol::COMMA), "'.");
                int value = Expression();
                if (IsOverflowing(std::log(value), std::log(base), CalculatorSymbol::DIVIDE)) ThrowError("[ERROR] Overflow occurred.");
                result = std::log(value) / std::log(base);

                token = tokenStream.Get();
                if (token.kind != CalculatorSymbol::CLOSED_PARENTHESES) ThrowError("Expected '" + char(CalculatorSymbol::CLOSED_PARENTHESES), "'.");
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
                ThrowError("Expected a primary.");
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
                    if (IsOverflowing(left, value, CalculatorSymbol::MULTIPLY)) ThrowError("Overflow occurred.");
                    left *= value;
                    token = tokenStream.Get();
                    break;
                }
                
                case CalculatorSymbol::DIVIDE:
                {
                    int denominator = Primary();
                    if (denominator == 0) ThrowError("Cannot divide by zero.");
                    if (IsOverflowing(left, denominator, CalculatorSymbol::DIVIDE)) ThrowError("Overflow occurred.");
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
                    if (IsOverflowing(left, value, CalculatorSymbol::PLUS)) ThrowError("Overflow occurred.");
                    left += value;
                    token = tokenStream.Get();
                    break;
                }

                case CalculatorSymbol::MINUS:
                {
                    int value = Term();
                    if (IsOverflowing(left, value, CalculatorSymbol::MINUS)) ThrowError("Overflow occurred.");
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
            if (IsOverflowing(result, i, CalculatorSymbol::MULTIPLY)) ThrowError("Overflow occurred.");
            result *= i;
        }
        return result;
    }

    bool IsOverflowing(int a, int b, CalculatorSymbol oper)
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
}