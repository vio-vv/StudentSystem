#include "file_system.hpp"

bool file::CheckFileExists(const std::string &filePath) noexcept
{
    return fs::exists(filePath) && !fs::is_directory(filePath);
}

std::pair<bool, std::string> file::ReadFile(const std::string &filePath) noexcept
{
    std::ifstream file(filePath);
    if (!file.good()) {
        return {false, ""};
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return {true, content};
}

bool file::WriteFile(const std::string &filePath, const std::string &content) noexcept
{
    std::ofstream file(filePath);
    if (!file.good()) {
        return false;
    }
    file << content;
    return true;
}

bool file::AppendFile(const std::string &filePath, const std::string &content) noexcept
{
    std::ofstream file(filePath, std::ios_base::app);
    if (!file.good()) {
        return false;
    }
    file << content;
    return true;
}

bool file::DeleteFile(const std::string &filePath) noexcept
{
    try {
        fs::remove(filePath);
        return true;
    } catch (const std::exception &e) {
        return false;
    }
}

bool file::CheckDirectoryExists(const std::string &directoryPath) noexcept
{
    return fs::exists(directoryPath) && fs::is_directory(directoryPath);
}

std::pair<bool, std::vector<std::string>> file::ListDirectory(const std::string &directoryPath) noexcept
{
    if (!CheckDirectoryExists(directoryPath)) {
        return {false, {}};
    }
    std::vector<std::string> files;
    try {
        auto it = fs::directory_iterator(directoryPath);
        for (const auto &entry : it) {
            files.push_back(entry.path().filename().string());
        }
    } catch (const std::exception &e) {
        return {false, {}};
    }
    return {true, files};
}

bool file::CreateDirectory(const std::string &directoryPath) noexcept
{
    try {
        fs::create_directory(directoryPath);
        return true;
    } catch (const std::exception &e) {
        return false;
    }
}

bool file::DeleteDirectory(const std::string &directoryPath) noexcept
{
    return system(("rd /s /q " + directoryPath).c_str()) == 0;
}

bool file::CheckExists(const std::string &path) noexcept
{
    return fs::exists(path);
}

std::string file::GetFilePath(const std::string &directionPath, const std::string &fileName) noexcept
{
    if (directionPath.back() == '\\' || directionPath.back() == '/') {
        return directionPath + fileName;
    }
    return directionPath + '\\' + fileName;
}
