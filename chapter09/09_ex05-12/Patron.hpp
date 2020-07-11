#pragma once

#include <iostream>
#include <string>

class Patron
{
public:
    Patron(std::string name, int cardNumber);
    
    std::string GetName() const { return name; }
    int GetCardNumber() const { return cardNumber; }
    double GetFees() const { return owedFees; }
    void SetFees(double fee);
    void ClearFees() { owedFees = 0.0; }

private:
    std::string name;
    int cardNumber;
    double owedFees;
};

bool IsOwingFees(const Patron &patron);
std::ostream &operator<<(std::ostream &os, const Patron &patron);