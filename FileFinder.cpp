#include "FileFinder.h"

#ifdef _WIN32
const char* DEFAULT_ROOT_PATH = "C:\\";
#else
const char* DEFAULT_ROOT_PATH = "/";
#endif

auto FileFinder::findFile(const std::string &fileName, const fs::path &path) -> fs::path {

    auto folderCount = getCountOfFolders(path);
    thread_pool pool(folderCount > MAX_THREADS ? MAX_THREADS : folderCount);

    for (const auto& entry : fs::directory_iterator(path))
        pool.push([this, capture0 = entry.path(), fileName] { searchInDirectory(capture0, fileName); });

    pool.join();
    return foundFilePath;
}

auto FileFinder::searchInDirectory(const fs::path &path, const std::string &fileName) -> void {
    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
        {
            if (found) return;
            if (entry.is_regular_file() && (entry.path().filename() == fileName))
            {
                std::lock_guard<std::mutex> lock(printMutex);
                //std::cout << "File found: " << entry.path() << std::endl;
                found = true;
                foundFilePath = entry.path().string();
                return;
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

auto FileFinder::getCountOfFolders(const fs::path &path) -> unsigned int {
    return std::count_if(std::filesystem::directory_iterator(path),
                         std::filesystem::directory_iterator(),
                         [](const auto& entry) { return entry.is_directory(); });
}
