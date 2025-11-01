#pragma once

#include <fstream>

/********************************
 * This class is a wrapper around ifstream and ofstream to easily read or write from a file.
 *
 * The path member variable could be improved using <filesystem>std::filesystem::path.
 * It handles native character and the conventions of many operating systems.
 * See chapter 10.10 File System of A Tour of C++ 2nd Edition.
 *******************************/
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
    void OpenOstream(std::ios_base::openmode openMode = std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    void WriteToOstream(const char* str);
    void CloseOstream();
};
