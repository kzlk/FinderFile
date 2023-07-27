#include "FileFinder.h"

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <file_name> [<search directory (root folder by default)>]" << std::endl;
        return 1;
    }

    FileFinder finder{};
    fs::path result{};

    if(argc == 2) result = finder.findFile(argv[1]);
    else result = finder.findFile(argv[1], argv[2]);

    if (!result.empty()) std::cout << "Result: " << result << std::endl;
    else std::cout << "File not found." << std::endl;

    return 0;
}