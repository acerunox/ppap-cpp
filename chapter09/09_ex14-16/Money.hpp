#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace MoneyLib
{
    enum class Currency { USD, PLN, EUR };
    static const std::vector<std::string> currencyCodes { "USD", "PLN", "EUR" };
    double GetCurrencyExchangeRate(const Currency &first, const Currency &second);

    class Money
    {
    public:
        Money(Currency currency = Currency::USD, double value = 0.00);

        long int GetValueInCents() const { return valueInCents; }
        Currency GetCurrency() const { return currency; }
    private:
        long int valueInCents;
        Currency currency;
    };

    Money operator+(const Money &first, const Money &second);
    Money operator-(const Money &first, const Money &second);
    Money operator-(const Money &money);
    Money operator*(const Money &money, double x);
    Money operator/(const Money &money, double x);
    std::ostream &operator<<(std::ostream &os, const Money &money);
    std::istream &operator>>(std::istream &is, Money &money);
}