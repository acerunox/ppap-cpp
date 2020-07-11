#include "./Patron.hpp"
#include "../../lib/utilities.h"
#include <iostream>

Patron::Patron(std::string name, int cardNumber) : name(name), cardNumber(cardNumber), owedFees(0.0) {}

void Patron::SetFees(double fee)
{
    if (fee < 0.0) ThrowError("Fees cannot be negative.");
    else owedFees = fee;
}

bool IsOwingFees(const Patron &patron) { return patron.GetFees() > 0.0; }

std::ostream &operator<<(std::ostream &os, const Patron &patron)
{
    return os << "Name: " << patron.GetName() << '\n'
              << "Card number: " << patron.GetCardNumber() << '\n'
              << "Fees: " << patron.GetFees() << '\n';
}