/*
#pragma once
#include <string>
#include <filesystem>
#include "ThreadPool.h"
namespace fs = std::filesystem;
#define MAX_THREADS 8



class Finder
{
public:
    explicit Finder();

    auto find(const fs::path& path, const std::string& file_name) -> std::filesystem::path;
    ~Finder();

private:

    ThreadPool* pool = nullptr;
    const fs::path root_path = "/";

    static uint8_t calcThreadsForSearching(const fs::path& path);
   static auto search(const fs::path& path, const std::string& file_name) -> void;

};



*/


#include <iostream>
#include <filesystem>
#include "NewThreadPool.h"

namespace fs = std::filesystem;

class Finder {
public:
    Finder() : found(false) {}

    std::string search(const fs::path& path, const std::string& file_name) {
        thread_pool pool();
        for (const auto& entry : fs::directory_iterator(path))
            pool.push([this, capture0 = entry.path(), file_name] { searchInDirectory(capture0, file_name); });

        pool.join();
        return found_file_path;
    }

private:
    std::atomic<bool> found;
    std::mutex print_mutex;
    std::condition_variable found_cv;
    std::string found_file_path;

    void searchInDirectory(const fs::path& path, const std::string& file_name) {
        try
        {
            for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
            {
                if (found) return;
                if (entry.is_regular_file() && (entry.path().filename() == file_name))
                {
                    std::lock_guard<std::mutex> lock(print_mutex);
                    std::cout << "File found: " << entry.path() << std::endl;
                    found = true;
                    found_file_path = entry.path().string();
                    // found_cv.notify_all(); // Notify other threads to stop searching
                    return;
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};


