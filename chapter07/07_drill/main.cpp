/*
    calculator08buggy.cpp

    Helpful comments removed.

    We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

inline void error(const std::string& s) { throw std::runtime_error(s); }
inline void error(const std::string& s, const std::string& s2) { error(s+s2); }

struct Token
{
    char kind;
    double value;
    std::string name;
    Token(char ch) :kind(ch), value(0) {}
    Token(char ch, double val) :kind(ch), value(val) {}
    Token(char ch, std::string n) : kind(ch), name(n) {}
};

class Token_stream
{
    bool full;
    Token buffer;
public:
    Token_stream() :full(0), buffer(0) {}

    Token get();
    void unget(Token t) { buffer = t; full = true; }

    void ignore(char);
};

//Create symbolic constants
const char let = 'L';
const char square_root = 'S';
const char power = 'P';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const std::string declkey = "#";
const std::string sqrtkey = "sqrt";
const std::string powkey = "pow";
const std::string quitkey = "exit";

Token Token_stream::get()
{
    if (full) { full = false; return buffer; }
    char ch;
    std::cin >> ch;
    switch (ch)
    {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
    case ';':
    case ',':
        return Token(ch);
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {	
        std::cin.unget();
        double val;
        std::cin >> val;
        return Token(number, val);
    }
    default:
        if (isalpha(ch) || ch == '#')
        {
            std::string s;
            s += ch;
            while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;   //add the character to the string
            std::cin.unget();                                                   //put the character back into the input buffer
            if (s == declkey) return Token(let);
            if (s == sqrtkey) return Token(square_root);
            if (s == powkey) return Token(power);
            if (s == quitkey) return Token(quit);
            return Token(name, s);
        }
        error("Bad token");
    }
}

//Clear characters up to and with 'c'
void Token_stream::ignore(char c)
{
    //Check if 'c' is in the buffer first
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (std::cin >> ch)
        if (ch == c) return;
}

struct Variable
{
    std::string name;
    double value;
    Variable(std::string n, double v) :name(n), value(v) {}
};

std::vector<Variable> names;

//Get the value of a Variable
double get_value(std::string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return names[i].value;
    error("get: undefined name ", s);
}

//Set the value of a Variable
void set_value(std::string s, double d)
{
    for (int i = 0; i <= names.size(); ++i)
        if (names[i].name == s)
        {
            names[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

//Checks if a Variable with certain name already exists
bool is_declared(std::string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) return true;
    return false;
}

Token_stream ts;

double expression();

double primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {	
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '-':
        return -primary();
    case square_root: 
    {
        t = ts.get();
        if (t.kind != '(') error("sqrt: '(' expected");
        
        double d = expression();
        if (d < 0) error("sqrt: cannot calculate for negative numbers");
        double s = std::sqrt(d);
        
        t = ts.get();
        if (t.kind != ')') error("sqrt: ')' expected");
        
        return s;
    }
    case power:
    {
        t = ts.get();
        if (t.kind != '(') error("pow: '(' expected");
       
        double x = expression();
        t = ts.get();
        if (t.kind != ',') error("pow: ',' expected");
        int i = primary();
        double p = std::pow(x,i);
        
        t = ts.get();
        if (t.kind != ')') error("pow: ')' expected");
        
        return p;
    }
    case number:
        return t.value;
    case name:
        return get_value(t.name);
    default:
        error("primary expected");
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    
    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {	
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.unget(t);
            return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();
    
    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.unget(t);
            return left;
        }
    }
}

double define_name(std::string s, double d)
{
    if (is_declared(s)) error(s, " declared twice");
    names.push_back(Variable(s, d));
    return d;
}

//Allows to declare a new Variable and adds it to a vector
double declaration()
{
    Token t = ts.get();
    if (t.kind != 'a') error("name expected in declaration");
    std::string name = t.name;
    
    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", name);
    double d = expression();
    define_name(name, d);
    return d;
}

//Checks whether user is declaring a new Variable or wants to calculate something
double statement()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
        return declaration();
    default:
        ts.unget(t);
        return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

const std::string prompt = "> ";
const std::string result = "= ";

void calculate()
{
    while (true)
    {
        try
        {
            std::cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get();
            if (t.kind == quit) return;
            ts.unget(t);
            std::cout << result << statement() << std::endl;
        }
        catch (std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            clean_up_mess();
        }
    }
}

int main()
{
    try
    {
        define_name("k", 1000);
        calculate();
        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "exception\n";
        return 2;
    }
}