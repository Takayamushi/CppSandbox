#pragma once

#include <filesystem>

class Path
{
public:
    Path();
    Path(const char* aPath);
    ~Path();
    
private:
    std::filesystem::path path;
    
public:
    void GetDirectoryEntries() const;
};