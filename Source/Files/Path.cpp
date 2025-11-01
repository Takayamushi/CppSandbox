#include "Files/Path.h"
#include <filesystem>
#include <iostream>

Path::Path()
{
    path = std::filesystem::current_path();
}

Path::Path(const char* aPath)
{
    path = aPath;
}

Path::~Path()
{
    
}

void Path::GetDirectoryEntries() const
{
    std::filesystem::directory_iterator dirIter(path);
    for (const std::filesystem::directory_entry& entry : dirIter)
    {
        std::cout << entry.path().string() << "\n";
    }
}
