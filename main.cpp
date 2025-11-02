#include <iostream>
#include <string>
#include <fstream>

#include "DataStructures/FString.h"
#include "Files/File.h"
#include "Files/Path.h"
#include "Types/Manipulators.h"

int main()
{
    //Remove compatibility with C-Style I/O to false.
    //This reduces overhead and improves I/O performance.
    std::ios_base::sync_with_stdio(false);
    
    return 0;
}
