#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream in("TestReadFile.txt");
    std::string c;
    if (in.is_open())
    {
        while (std::getline(in, c))
        {
            std::cout << c << "\n";
        }
    }
    
    std::ofstream out("TestWriteFile.txt");
    if (out.is_open())
    {
        out << "This is a test write to file." << "\n";
    }
    
    return 0;
}
