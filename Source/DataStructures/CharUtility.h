#pragma once

enum
{
    CHAR_SPACE = 32,
    CHAR_EXCLAMATION = 33,
    CHAR_QUOTE = 34,
    CHAR_NUMBERSIGN = 35,
    CHAR_DOLLAR = 36,
    CHAR_PERCENT = 37,
    CHAR_AMPERSAND = 38,
    CHAR_SINGLEQUOTE = 39,
    //TODO Complete..
};

/********************************************
0-31 Control Characters
These characters are unprintable characters used to control peripherals.

48 - 57
'0' to '9'

65 - 90
'A' to 'Z'

97 - 122
'a' to 'z'

32 - SPACE
33 - ! 
34 - "
35 - #
36 - $
37 - %
38 - &
39 - '
40 - (
41 - )
42 - *
43 - +
44 - .
45 - -
46 - .
47 - /

58 - :
59 - ;
60 - <
61 - =
62 - >
63 - ?
64 - @

91 - [
92 - \
93 - ]
94 - ^
95 - _
96 - `

123 - {
124 - |
125 - }
126 - ~
127 - DELETE
**************************************/

static bool IsVowel(char c)
{
    return
    c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

static bool IsLetter(char c)
{
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

static bool IsConsonant(char c)
{
    return IsLetter(c) && !IsVowel(c);
}
