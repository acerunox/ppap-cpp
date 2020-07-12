#include "./Money.hpp"
#include "../../lib/utilities.h"
#include <algorithm>
#include <cmath>
#include <limits.h>
#include <string>

namespace MoneyLib
{
    double GetCurrencyExchangeRate(const Currency &first, const Currency &second)
    {
        switch (first)
        {
        case Currency::USD:
            switch (second)
            {
            case Currency::PLN:
                return 3.95;
            case Currency::EUR:
                return 0.89;
            }
            break;

        case Currency::PLN:
            switch (second)
            {
            case Currency::USD:
                return 0.25;
            case Currency::EUR:
                return 0.22;
            }
            break;

        case Currency::EUR:
            switch (second)
            {
            case Currency::USD:
                return 1.13;
            case Currency::PLN:
                return 4.46;
            }
            break;
        }

        ThrowError("Unrecognized currency.");
    }

    Money::Money(Currency currency, double value) : currency(currency), valueInCents(std::round(value * 100.00))
    {
        if (std::round(value * 100) > LONG_MAX) ThrowError("Value is too big.");
    }

    Money operator+(const Money &first, const Money &second)
    {
        if (first.GetCurrency() == second.GetCurrency())
        {
            return Money(first.GetCurrency(), (first.GetValueInCents() + second.GetValueInCents()) / 100.00);
        }

        double exchangeRate = GetCurrencyExchangeRate(second.GetCurrency(), first.GetCurrency());
        return Money(first.GetCurrency(), (first.GetValueInCents() + second.GetValueInCents() * exchangeRate) / 100.00);
    }

    Money operator-(const Money &first, const Money &second)
    {
        if (first.GetCurrency() == second.GetCurrency())
        {
            return Money(first.GetCurrency(), (first.GetValueInCents() - second.GetValueInCents()) / 100.00);
        }

        double exchangeRate = GetCurrencyExchangeRate(second.GetCurrency(), first.GetCurrency());
        return Money(first.GetCurrency(), (first.GetValueInCents() - second.GetValueInCents() * exchangeRate) / 100.00);
    }

    Money operator-(const Money &money)
    {
        return Money(money.GetCurrency(), (-money.GetValueInCents()) / 100.00);
    }

    Money operator*(const Money &money, double x)
    {
        return Money(money.GetCurrency(), (money.GetValueInCents() * x) / 100.00);
    }

    Money operator/(const Money &money, double x)
    {
        if (x == 0) ThrowError("Cannot divide by 0.");

        return Money(money.GetCurrency(), (money.GetValueInCents() / x) / 100.00);
    }

    std::ostream &operator<<(std::ostream &os, const Money &money)
    {
        long int value = money.GetValueInCents();

        os << currencyCodes[int(money.GetCurrency())] << ' ' << value / 100 << '.';
        if (value % 100 >= -9 && value % 100 <= 9) os << '0';   //if the amount of cents is one digit, add 0 before
        
        if (value % 100 < 0) os << -(value % 100);  //if cents are negative, print them without the minus sign
        else os << value % 100;

        return os;
    }

    std::istream &operator>>(std::istream &is, Money &money)
    {
        double value = 0;
        std::string currencyCode;

        is >> currencyCode >> value;

        auto iter = std::find(currencyCodes.begin(), currencyCodes.end(), currencyCode);
        if (!is || iter == currencyCodes.end())
        {
            is.clear(std::ios_base::failbit);
            return is;
        }

        try
        {
            int index = std::distance(currencyCodes.begin(), iter);
            money = Money(Currency(index), value);
        }
        catch(const std::exception &err)
        {
            std::cerr << "[ERROR] " << err.what() << '\n';
            std::cerr << "[ERROR] Input has failed." << '\n';
            is.clear(std::ios_base::failbit);
        }

        return is;
    }
}