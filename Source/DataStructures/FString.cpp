#include "FString.h"

#include <iostream>
#include "CharUtility.h"

FString::FString(const char* str)
{
    // We create a new array of character that we allocate on the Heap.
    // This leads to a few thoughts.
    //  - What happens to the string literal? Does it exist forever and now takes extra memory?
    //  - Creating a copy of a string literal goes against it's design of reusing it.
    size_t strLength = strlen(str);
    string = new char[strLength]();
    strcpy_s(string, strLength + 1, str);
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

void FString::ToUpper()
{
    for (int i = 0; i < length; i++)
    {
        if (islower(string[i]))
        {
            string[i] = toupper(string[i]);
        }
    }
}

void FString::ToLower()
{
    for (int i = 0; i < length; i++)
    {
        if (isupper(string[i]))
        {
            string[i] = tolower(string[i]);
        }
    }
}

uint32 FString::GetWordCount(const FString& str)
{
    //Bugs:
    // - An extra word is added when there are trailing spaces
    uint32 spaceCount = 0;
    for (int i = 0; i < str.Length(); i++)
    {
        if (str[i] == ' ')
        {
            if (i == 0 && str[i - 1] == ' ')
                continue;
            spaceCount++;
        }
    }
    return spaceCount + 1;
}
