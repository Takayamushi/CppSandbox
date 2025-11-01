#include "FString.h"

#include <iostream>

FString::FString(const char* str)
{
    string = str;
    int i = 1;
    for (; string[i] != '\0'; i++)
    length = i + 1;
}

FString::FString()
{
    string = nullptr;
    length = 0;
}

void FString::Print() const
{
    for (int i = 0; i < length; i++)
    {
        std::cout << string[i];
    }
    std::cout << "\n";
}
