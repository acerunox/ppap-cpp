#include <iostream>
#include <string>
#include <vector>

void Fragment01()
{
    /* -1-
    Cout << "Success!\n"; */

    std::cout << "Success!\n";
}

void Fragment02()
{
    /* -2-
    cout << "Success!\n; */

    std::cout << "Success!\n";
}

void Fragment03()
{
    /* -3- 
    cout << "Success" << !\n" */

    std::cout << "Success" << "!\n";
}

void Fragment04()
{
    /* -4-
    cout << success << '\n';*/

    std::cout << "Success!" << '\n';
}

void Fragment05()
{
    /* -5- 
    string res = 7; 
    vector<int> v(10); 
    v[5] = res; 
    cout << "Success!\n"; */

    int res = 7;
    std::vector<int> v(10);
    v[5] = res;
    std::cout << "Success!\n";
}

void Fragment06()
{
    /* -6- 
    vector<int> v(10); 
    v(5) = 7; 
    if (v(5)!=7) cout << "Success!\n"; */

    std::vector<int> v(10);
    v[5] = 7;
    if (v[5] == 7) std::cout << "Success!\n";
}

void Fragment07()
{
    /* -7- 
    if (cond) cout << "Success!\n"; 
    else cout << "Fail!\n"; */

    if (true) std::cout << "Success!\n";
    else std::cout << "Fail!\n";
}

void Fragment08()
{
    /* -8- 
    bool c = false; 
    if (c) cout << "Success!\n";
    else cout << "Fail!\n"; */

    bool c = true;
    if (c) std::cout << "Success!\n";
    else std::cout << "Fail!\n";
}

void Fragment09()
{
    /* -9- 
    string s = "ape"; 
    boo c = "fool"<s; 
    if (c) cout << "Success!\n"; */

    std::string s = "ape";
    bool c = "fool" > s;
    if (c) std::cout << "Success!\n";
}

void Fragment10()
{
    /* -10- 
    string s = "ape"; 
    if (s=="fool") cout << "Success!\n"; */
    
    std::string s = "ape";
    if (s != "fool") std::cout << "Success!\n";
}

void Fragment11()
{
    /* -11- 
    string s = "ape"; 
    if (s=="fool") cout < "Success!\n"; */

    std::string s = "ape";
    if (s != "fool") std::cout << "Success!\n";
}

void Fragment12()
{
    /* -12- 
    string s = "ape"; 
    if (s+"fool") cout < "Success!\n"; */

    std::string s = "ape";
    if (s < "fool") std::cout << "Success!\n";
}

void Fragment13()
{
    /* -13- 
    vector<char> v(5); 
    for (int i=0; 0<v.size(); ++i) ; cout << "Success!\n"; */
    
    std::vector<char> v(5);
    for (int i = 0; i < v.size(); ++i) std::cout << "Success!\n";
}

void Fragment14()
{
    /* -14- 
    vector<char> v(5); 
    for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n"; */

    std::vector<char> v(5);
    for (int i = 0; i < v.size(); ++i) std::cout << "Success!\n";
}

void Fragment15()
{
    /* -15- 
    string s = "Success!\n"; 
    for (int i=0; i<6; ++i) cout << s[i]; */
    
    std::string s = "Success!\n";
    for (int i = 0; i < s.length(); ++i) std::cout << s[i];
}

void Fragment16()
{
    /* -16- 
    if (true) then cout << "Success!\n"; 
    else cout << "Fail!\n"; */

    if (true) std::cout << "Success!\n";
    else std::cout << "Fail!\n";
}

void Fragment17()
{
    /* -17- 
    int x = 2000; 
    char c = x; 
    if (c==2000) cout << "Success!\n"; */

    int x = 2000;
    char c = x;
    if (c != 2000) std::cout << "Success!\n";
}

void Fragment18()
{
    /* -18- 
    string s = "Success!\n"; 
    for (int i=0; i<10; ++i) cout << s[i]; */

    std::string s = "Success!\n";
    for (int i = 0; i < s.length(); ++i) std::cout << s[i];
}

void Fragment19()
{
    /* -19- 
    vector v(5); 
    for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n"; */

    std::vector<int> v(5);
    for (int i = 0; i < v.size(); ++i) std::cout << "Success!\n";
}

void Fragment20()
{
    /* -20- 
    int i=0; 
    int j = 9; 
    while (i<10) ++j; 
    if (j<i) cout << "Success!\n"; */

    int i = 0;
    int j = 9;
    while (i < 10) ++i;
    if (j < i) std::cout << "Success!\n";
}

void Fragment21()
{
    /* -21- 
    int x = 2; 
    double d = 5/(x–2); 
    if (d==2*x+0.5) cout << "Success!\n"; */

    int x = 2;
    double d = 5/(x-1);
    if (d == 2*(x+0.5)) std::cout << "Success!\n";
}

void Fragment22()
{
    /* -22- 
    string<char> s = "Success!\n"; 
    for (int i=0; i<=10; ++i) cout << s[i]; */

    std::string s = "Success!\n";
    for (int i = 0; i < s.length(); ++i) std::cout << s[i];
}

void Fragment23()
{
    /* -23- 
    int i=0; 
    while (i<10) ++j; 
    if (j<i) cout << "Success!\n"; */

    int i = 0;
    while (i < 10) ++i;
    if (9 < i) std::cout << "Success!\n";
}

void Fragment24()
{
    /* -24- 
    int x = 4; 
    double d = 5/(x–2); 
    if (d=2*x+0.5) cout << "Success!\n"; */

    int x = 4;
    double d = 5/(x-2);
    if (d != 2*x+0.5) std::cout << "Success!\n";
}

void Fragment25()
{
    /* -25- 
    cin << "Success!\n"; */

    std::cout << "Success!\n";
}

int main()
{
    try
    {
        Fragment01();
        Fragment02();
        Fragment03();
        Fragment04();
        Fragment05();
        Fragment06();
        Fragment07();
        Fragment08();
        Fragment09();
        Fragment11();
        Fragment12();
        Fragment13();
        Fragment14();
        Fragment15();
        Fragment16();
        Fragment17();
        Fragment18();
        Fragment19();
        Fragment20();
        Fragment21();
        Fragment22();
        Fragment23();
        Fragment24();
        Fragment25();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
}