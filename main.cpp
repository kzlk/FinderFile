/*
#include <iostream>
#include <filesystem>

#include <signal.h>
#include "ThreadPool.cpp"
namespace fs = std::filesystem;
std::atomic<bool> found(false);
std::mutex print_mutex;
std::condition_variable found_cv;

//thread pool  | lib
//finder       | lib
//main         | use lib
//using lib
//Finder finder = new Finder();
//finder.search("/", "filename.txt") -> std::string


//-----------------------

// finder func


auto search(const fs::path& path, const std::string& file_name) -> void
{
    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied ))
        {
            if (found) return;
            if ( entry.is_regular_file() && (entry.path().filename() == file_name))
            {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "File found: " << entry.path() << std::endl;
                found = true;
               // found_cv.notify_all(); // Notify other threads to stop searching
                return;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


int main()
{
    fs::path root_path = "/";
    std::string file_name = "kernel";

    ThreadPool pool(4);
    for (const auto &entry: fs::directory_iterator(root_path))
    {
        std::cout << entry.path() << std::endl;
        pool.add_task(search, entry.path(), file_name);
    }

pool.wait_all();





    return 0;
}
*/

#include "Finder.h"
int main()
{
    Finder finder;
    fs::path root_path = "/";
    std::string file_name = "CMakeCCompilerId.c";

    std::string result = finder.search(root_path, file_name);
    if (!result.empty()) {
        std::cout << "Result: " << result << std::endl;
    }
    else {
        std::cout << "File not found." << std::endl;
    }

    return 0;
}