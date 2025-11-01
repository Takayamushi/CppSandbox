#include <iostream>
#include <string>
#include <fstream>

#include "DataStructures/FString.h"
#include "Files/File.h"
#include "Types/Manipulators.h"

int main()
{
    File file { "TestFile.txt" };
    file.Write("Hello World.\n");
    std::cout << file.Read() << "\n";
    
    return 0;
}
