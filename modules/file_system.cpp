#include "file_system.hpp"

bool file::CheckFileExists(const std::string &filePath) noexcept
{
    return fs::exists(filePath);
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
    return fs::remove(filePath);
}

bool file::CheckDirectoryExists(const std::string &directoryPath) noexcept
{
    return fs::is_directory(directoryPath) && fs::exists(directoryPath);
}

std::pair<bool, std::vector<std::string>> file::ListDirectory(const std::string &directoryPath) noexcept
{
    if (!CheckDirectoryExists(directoryPath)) {
        return {false, {}};
    }
    std::vector<std::string> files;
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
        files.push_back(entry.path().string());
    }
    return {true, files};
}
