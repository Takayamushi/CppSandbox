#pragma once
#include <ostream>

class FString
{
public:
    FString(const char* str);
    FString();
    // We let the compiler generate the copy constructor, assignment operator, and destructor.
    // The default implementations are sufficient since we are not managing any resources manually.
    
    const char& operator[](int index) const
    {
        //[] operator is overloaded to access individual characters in the string
        return string[index];
    }

    //The "friend" keyword allows these operator functions to access private members of FString.
    friend std::ostream& operator<<(std::ostream& os, const FString& str);
    
    int Length() const { return length; }
    void Print() const;

    void ToUpper();
    void ToLower();
    
private:
    char* string = nullptr;
    int length = 0;
};

/* Begin Overload Operators */
inline bool operator>(const FString& my, const FString& other)
{
    return my.Length() > other.Length();
}

inline bool operator<(const FString& my, const FString& other)
{
    return my.Length() < other.Length();
}

inline bool operator>=(const FString& my, const FString& other)
{
    return my.Length() >= other.Length();
}
    
inline bool operator<=(const FString& my, const FString& other)
{
    return my.Length() <= other.Length();
}

inline bool operator==(const FString& my, const FString& other)
{
    if (my.Length() != other.Length())
    {
        return false;
    }
    bool sameString = true;
    for (int i = 0; i < my.Length(); i++)
    {
        if (my[i] != other[i])
        {
            sameString = false;
            break;
        }
    }
    return sameString;
}

inline bool operator!=(const FString& my, const FString& other)
{
    return !(my == other);
}

inline std::ostream& operator<<(std::ostream& os, const FString& str)
{
    os << str.string;
    return os;
}
/* End Overload Operators */
