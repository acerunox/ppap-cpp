#include <iostream>
#include <string>

inline void ShowSimpleError(std::string s)
{
    std::cerr << "error: " << s << '\n';
    exit(EXIT_FAILURE);
}

std::string GetPronoun(const char &gender)
{
    std::string pronoun;
    switch (gender)
    {
        case 'm':
            pronoun = "him";
            break;
        case 'f':
            pronoun = "her";
            break;
        case 'o':
            pronoun = "them";
            break;
        default:
            ShowSimpleError("Unknown input.");
            break;
    }
    return pronoun;
}

int main()
{
    int intendSize = 4;

    std::cout << "Enter the name of the person you want to write to: ";
    std::string firstName;
    std::cin >> firstName;

    std::cout << "How old are they?: ";
    int age = 0;
    std::cin >> age;
    if (age <= 0 || age >= 110) ShowSimpleError("You're kidding!");

    std::cout << "What's your mutual friend's name?: ";
    std::string friendName;
    std::cin >> friendName;

    std::cout << "What is their gender? (m/f/o): ";
    char friendSex = 0;
    std::cin >> friendSex;
    std::string pronoun = GetPronoun(friendSex);

    std::cout << "Dear " << firstName << ",\n"
              << std::string(intendSize, ' ') << "Thank you for your letter, it was great to hear from you. " 
              << "You've asked me how am I doing - everything is going very well. Hopefully you can say the same thing. "
              << "Have you seen " << friendName << " lately? " << "If you see " << friendName << ", please ask " << pronoun << " to call me. "
              << "Also, you just had your birthday and you are " << age << " years old. ";

    if (age < 12) std::cout << "Next year you will be " << age + 1 << "! ";
    else if (age == 17) std::cout << "Next year you will be able to vote! ";
    else if (age > 70) std::cout << "I hope you are enjoying retirement! ";

    std::cout << "\n\nYours sincerely, \nXYZ\n";
}