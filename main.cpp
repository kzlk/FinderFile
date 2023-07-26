#include <iostream>
#include <filesystem>

#include <signal.h>
#include "ThreadPool.cpp"
namespace fs = std::filesystem;
std::atomic<bool> found(false);
std::mutex print_mutex;

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

    //std::cout << "ID -> " << std::this_thread::get_id() << '\n';
    try {
        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied )) {
            if (found) return;
            if ( entry.is_regular_file() && (entry.path().filename() == file_name)) {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "File found: " << entry.path() << std::endl;
                found = true;
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

    std::string file_name = "build.txt";

    thread_pool pool(8);
    for (const auto &entry: fs::directory_iterator(root_path))
    {
        std::cout << entry.path() << std::endl;
        pool.add_task(search, entry.path(), file_name);
    }


pool.wait_all();




    return 0;
}
