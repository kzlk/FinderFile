#pragma once
#include <iostream>
#include <filesystem>
#include "ThreadPool.h"

#define MAX_THREADS 8

extern const char* DEFAULT_ROOT_PATH;
namespace fs = std::filesystem;

class FileFinder {
public:
    FileFinder() : found(false) {}
    auto findFile( const std::string& fileName, const fs::path& path = DEFAULT_ROOT_PATH) -> fs::path;

private:
    std::atomic<bool> found;
    std::mutex printMutex;
    fs::path foundFilePath;

    static auto getCountOfFolders(const fs::path& path) -> unsigned int;
    auto searchInDirectory(const fs::path& path, const std::string& fileName) -> void;
};




