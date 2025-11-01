#pragma once

#include <fstream>

class File
{
public:
    File(const char* aFilePath);
    ~File();
    
private:
    const char* filePath;
    std::ifstream inputStream;
    std::ofstream outputStream;

public:
    std::string Read();
    std::string ReadLine(int lineIndex);
    void Write(const char* str);
    void WriteLine(const char* str);

private:
    void OpenOstream(std::ios_base::openmode openMode = std::ios_base::trunc | std::ios_base::binary);
    void WriteToOstream(const char* str);
    void CloseOstream();
};
