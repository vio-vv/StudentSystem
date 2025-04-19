#include "file_system.hpp"

file::DataBase file::DataBase::operator[](const std::string &keyName) noexcept
{
    if (!CheckDirectoryExists(space)) {
        if (!CreateDirectory(space)) {
            assert(false);
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory" << std::endl;
            exit(1);
        }
    }
    return DataBase(GetFilePath(space, keyName));
}

unsigned long long file::DataBase::Count() const noexcept
{
    if (!CheckDirectoryExists(space)) {
        if (!CreateDirectory(space)) {
            assert(false);
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory" << std::endl;
            exit(1);
        }
    }
    auto [success, files] = ListDirectory(space);
    if (!success) {
        assert(false);
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to list directory" << std::endl;
        exit(1);
    }
    return files.size();
}

const std::string &file::DataBase::operator=(const std::string &value) const noexcept
{
    if (!WriteFile(space, value)) {
        assert(false);
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write file" << std::endl;
        exit(1);
    }
    return value;
}

bool file::CheckFileExists(const std::string &filePath) noexcept
{
    return fs::exists(filePath);
}

file::DataBase::operator std::string() const noexcept
{
    if (!CheckFileExists(space)) {
        if (!WriteFile(space, "")) {
            assert(false);
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write file" << std::endl;
            exit(1);
        }
    }
    auto [success, content] = ReadFile(space);
    if (!success) {
        assert(false);
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read file" << std::endl;
        exit(1);
    }
    return content;
}

void file::DataBase::Remove() noexcept
{
    if (CheckFileExists(space)) {
        if (!DeleteFile(space)) {
            assert(false);
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to delete file" << std::endl;
            exit(1);
        }
    }
    DataBase::~DataBase();
}

void file::DataBase::Cut() noexcept
{
    if (CheckDirectoryExists(space)) {
        if (!DeleteDirectory(space)) {
            assert(false);
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to delete file" << std::endl;
            exit(1);
        }
    }
    DataBase::~DataBase();
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
        files.push_back(entry.path().filename().string());
    }
    return {true, files};
}

bool file::CreateDirectory(const std::string &directoryPath) noexcept
{
    return fs::create_directory(directoryPath);
}

bool file::DeleteDirectory(const std::string &directoryPath) noexcept
{
    return fs::remove_all(directoryPath);
}

std::string file::GetFilePath(const std::string &directionPath, const std::string &fileName) noexcept
{
    if (directionPath.back() == '\\' || directionPath.back() == '/') {
        return directionPath + fileName;
    }
    return directionPath + '\\' + fileName;
}
