#include "File.h"

#include <iostream>
#include <string>

File::File(const char* aFilePath)
{
    filePath = aFilePath;
    inputStream = std::ifstream(aFilePath, std::ios::binary);
}

File::~File()
{
    inputStream.close();
    outputStream.close();
}

std::string File::Read()
{
    //Looping through each line allows us to not define a buffer.
    //This is probably not optimal.
    std::string result;
    std::string line;
    while (std::getline(inputStream, line))
    {
        result += line + "\n";
    }

    return result;
}

std::string File::ReadLine(int lineIndex)
{
    std::string result;
    int currentLine = 0;
    while (std::getline(inputStream, result))
    {
        if (currentLine == lineIndex)
        {
            break;
        }
        currentLine++;
    }
    return result;
}

void File::Write(const char* str)
{
    OpenOstream(std::ios_base::trunc | std::ios_base::binary);
    WriteToOstream(str);
    CloseOstream();
}

void File::WriteLine(const char* str)
{
    OpenOstream(std::ios_base::app | std::ios_base::binary);
    WriteToOstream(str);
    CloseOstream();
}

void File::OpenOstream(std::ios_base::openmode openMode)
{
    outputStream.open(filePath, openMode);
}

void File::WriteToOstream(const char* str)
{
    outputStream << str;
}

void File::CloseOstream()
{
    outputStream.close();
}

