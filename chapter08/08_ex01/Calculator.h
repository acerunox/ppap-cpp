#pragma once
#include "TokenStream.h"
#include <limits.h>
#include <vector>
#include <string>

enum class Option { QUIT, HELP, DECLARE, CALCULATE };

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
        Option Statement();
        int Calculate();
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

inline bool IsOverflowing(int a, int b, CalculatorSymbol oper);