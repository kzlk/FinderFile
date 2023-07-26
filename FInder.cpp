/*
#include "Finder.h"
std::atomic<bool> found{false};
std::filesystem::path resultPath{"NoFound"};
std::mutex foundLock{};
auto Finder::search(const fs::path &path, const std::string &file_name) -> void {
    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied ))
        {
            if (found) return;
            if ( entry.is_regular_file() && (entry.path().filename() == file_name))
            {
                std::lock_guard<std::mutex> lock(foundLock);
                resultPath = entry.path();
                std::cout << "File found: " << entry.path() << std::endl;
                found = true;
                return;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

Finder::~Finder()
{
    delete pool;
}

uint8_t Finder::calcThreadsForSearching(const fs::path& path)
{
    uint16_t count{};
    for (const auto& entry : fs::directory_iterator(path))
    {
        if(count >= 8) return count;
        if (entry.is_directory())
        {
            count++;
        }
    }
    return count;
}

Finder::Finder() {
   // pool = new  ThreadPool(4);
}

auto Finder::find(const fs::path &path, const std::string &file_name) -> std::filesystem::path {
    pool = new  ThreadPool(8);
    if(pool != nullptr) {
       for (const auto &entry: fs::directory_iterator(path)) {
           std::cout << entry.path() << std::endl;
           pool->add_task(search, std::ref(path), std::ref(file_name));
       }

       pool->wait_all();
   }

    pool->wait_all();
    return resultPath;

}

*/
