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

char* FString::begin() const
{
    return &string[0];
}

char* FString::end() const
{
    return &string[0] + length;
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

uint32 FString::GetVowelCount(const FString& str)
{
    uint32 count = 0;
    for (int i = 0; i < str.Length(); i++)
    {
        if (IsVowel(str[i])) count++;
    }
    return count;
}

uint32 FString::GetConsonantCount(const FString& str)
{
    uint32 count = 0;
    for (int i = 0; i < str.Length(); i++)
    {
        if (IsConsonant(str[i])) count++;
    }
    return count;
}

FString FString::Reverse(const FString& str)
{
    uint32 strLen = str.Length();
    char* temp = new char[strLen + 1];
    for (int i = strLen - 1; i >= 0; i--)
    {
        temp[strLen - 1 - i] = str[i];
    }
    temp[strLen] = '\0';
    FString result = temp;
    delete[] temp;
    return result;
}

FString FString::ToLower(const FString& str)
{
    char* temp = new char[str.Length() + 1];
    for (int i = 0; i < str.Length(); i++)
    {
        temp[i] = tolower(str[i]);
    }
    temp[str.Length()] = '\0';
    FString result = temp;
    delete[] temp;
    return result;
}

FString FString::ToUpper(const FString& str)
{
    char* temp = new char[str.Length() + 1];
    for (int i = 0; i < str.Length(); i++)
    {
        temp[i] = toupper(str[i]);
    }
    temp[str.Length()] = '\0';
    FString result = temp;
    delete[] temp;
    return result;
}

FString FString::RemoveWhitespaces(const FString& str)
{
    uint32 strLen = str.Length();
    char* temp = new char[str.Length() + 1];
    uint32 j = 0;
    for (int i = 0; i < strLen; i++)
    {
        if (str[i] != ' ')
        {
            temp[j] = str[i];
            j++;
        }
    }
    temp[j] = '\0';
    FString result {temp};
    delete[] temp;
    return result;
}

bool FString::IsPalindrome(const FString& str)
{
    FString string = RemoveWhitespaces(str);
    FString strReversed = RemoveWhitespaces(Reverse(str));
    return string == strReversed;
}


uint32 FString::FindDuplicates(const FString& str)
{
    uint32 foundLetters = 0, result = 0;
    FString loweredStr = ToLower(str);
    for (int i = 0; i < loweredStr.Length(); i++)
    {
        uint32 compare = 1 << (loweredStr[i] - 97);
        if ((foundLetters & compare) > 0)
        {
            result += compare;
        }
        else
        {
            foundLetters += compare;
        }
    }

    return result;
}
