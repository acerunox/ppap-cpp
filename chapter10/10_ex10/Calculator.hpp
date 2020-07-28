#pragma once
#include "./TokenStream.hpp"
#include "./Token.hpp"
#include <string>
#include <vector>

namespace CalculatorLib
{
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
            void ReadFromFile(std::ostream &outputStream);
            void WriteToFile();
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

    bool IsOverflowing(int a, int b, CalculatorSymbol oper);
}