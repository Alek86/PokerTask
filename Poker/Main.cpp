#include "ProcessFile.h"
#include "Tests.h"

#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>

class Pauser
{
public:
    ~Pauser()
    {
        system("pause");
    }
};

// Command arguments: c:\TEMP\input.txt c:\TEMP\output.txt
int main(int argc, char *argv[])
{
    Pauser pauser;

    if (argc == 1)
    {
        std::cout << "Running tests... To process file pass 2 parameters" << std::endl;
        RunTests();
        std::cout << "Done" << std::endl;
        return 0;
    }

    if (argc != 3)
    {
        std::cerr << "Wrong number of parameters" << std::endl;
        return 1;
    }

    try
    {
        std::ifstream input(argv[1], std::ios_base::in);
        std::ofstream output(argv[2], std::ios_base::out);
        
        if (!input.is_open())
        {
            std::cerr << "Cannot open input file " << argv[1] << std::endl;
            return 2;
        }

        if (!output.is_open())
        {
            std::cerr << "Cannot open output file " << argv[2] << std::endl;
            return 3;
        }

        std::string line;
        while (!input.eof())
        {
            std::getline(input, line);

            if (line.empty() || line[0] == '\r' || line[0] == '\n')
            {
                break;
            }

            auto resLine = ProcessInputLine(line);
            output << resLine.c_str() << std::endl;
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
        return 100;
    }
}