/*
Exercise 04: Look at the headache-inducing last example of §8.4.
             Indent it properly and explain the meaning of each construct.
             Note that the example doesn’t do anything meaningful; it is pure obfuscation.
*/

struct X                            //struct X declaration (scope: global)
{ 
    void f(int x)                   //function f() definition (scope: X)
    { 
        struct Y                    //struct Y declaration (scope: f())
        { 
            int f() { return 1; }   //function f() definition (scope: Y)
            int m;                  //variable m declaration (scope: Y)
        }; 
        int m;                      //variable m declaration (scope: f())
        m = x;                      //assignment of x to m (scope: f())
        Y m2;                       //creation of object m2 of type Y (scope: f())
        return f(m2.f());           //return statement of f()
    }
    int m;                          //variable m declaration (scope: X)
    void g(int m)                   //function g() definition (scope: X)
    { 
        if (m) f(m + 2);            //if statement, call X.f()
        else                        //else statement
        { 
            g(m + 2);               //call X.g()
        } 
    }
    X() {}                          //default constructor
    void m3() {}                    //empty function definition (scope: X)
    void main()                     //function main() definition (scope: X)
    { 
        X a;                        //creation of object a of type X (scope: main())
        a.f(2);                     //call X.f() (scope: main())
    } 
};