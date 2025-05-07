#include "data_base.hpp"

bool dat::DataBase::fail = false;

dat::DataBase::operator std::string() const noexcept
{
    if (!file::CheckFileExists(space)) {
        if (!file::WriteFile(space, "")) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write file:" << space << std::endl;
            fail = true;
            return "";
        }
    }
    auto [success, content] = file::ReadFile(space);
    if (!success) {
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read file:" << space << std::endl;
        fail = true;
        return "";
    }
    return content;
}

void dat::DataBase::Clear() const noexcept
{
    if (file::CheckFileExists(space)) {
        if (!file::DeleteFile(space)) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to delete file:" << space << std::endl;
            fail = true;
            return;
        }
    }
}

void dat::DataBase::Remove() const noexcept
{
    if (consideredAsFileOnly) {
        assert(false); // Deny
        return;
    }
    if (file::CheckDirectoryExists(space)) {
        if (!file::DeleteDirectory(space)) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to delete file:" << space << std::endl;
            fail = true;
            return;
        }
    }
}

dat::DataBase dat::DataBase::operator[](const std::string &keyName) const noexcept
{
    if (consideredAsFileOnly) {
        assert(false); // Deny
        return DataBase(".\\data", false);
    }
    if (!file::CheckDirectoryExists(space)) {
        if (!file::CreateDirectory(space)) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory:" << space << std::endl;
            fail = true;
            return DataBase(".\\data", false);
        }
    }
    return DataBase(file::GetFilePath(space, keyName), false);
}
dat::DataBase dat::DataBase::operator[](const unsigned long long index) noexcept
{
    return DataBase(file::GetFilePath(space, List()[index]), true);
}

void dat::DataBase::Push(const std::pair<std::string, std::string> &key_value) const noexcept
{
    if (consideredAsFileOnly) {
        assert(false); // Deny
        return;
    }
    if (!file::CheckDirectoryExists(space)) {
        if (!file::CreateDirectory(space)) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory:" << space << std::endl;
            fail = true;
            return;
        }
    }
    const auto &next = (*this)[key_value.first];
    next = key_value.second;
}

void dat::DataBase::Push(const std::string &value) noexcept
{
    List();
    unsigned long long index = 0;
    if (list.size() > 0) {
        index = ToNum<unsigned long long>(list[list.size() - 1]) + 1;
    } else {
        index = 0;
    }
    const auto &next = (*this)[ToStr(index)];
    next = value;
}

std::vector<std::string> dat::DataBase::List() noexcept
{
    if (consideredAsFileOnly) {
        assert(false); // Deny
        return {};
    }
    if (!file::CheckDirectoryExists(space)) {
        if (!file::CreateDirectory(space)) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory:" << space << std::endl;
            fail = true;
            return {};
        }
    }
    auto [success, files] = file::ListDirectory(space);
    if (!success) {
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to list directory:" << space << std::endl;
        fail = true;
        return {};
    }
    std::sort(files.begin(), files.end(), [](const std::string &a, const std::string &b){
        auto la = a.size();
        auto lb = b.size();
        if (la != lb) return la < lb;
        return a < b;
    });
    return list = std::move(files);
}

dat::DataBase::iterator dat::DataBase::begin() noexcept
{
    List();
    return iterator(&space, list.begin());
}

dat::DataBase::iterator dat::DataBase::end() const noexcept
{
    return iterator(&space, list.end());
}

unsigned long long dat::DataBase::Size() noexcept
{
    return List().size();
}

bool dat::DataBase::Exists() const noexcept
{
    return file::CheckExists(space);
}

bool dat::DataBase::Exists(const std::string &keyName) const noexcept
{
    return file::CheckExists(file::GetFilePath(space, keyName));
}

const std::string &dat::DataBase::operator=(const std::string &value) const noexcept
{
    if (!file::WriteFile(space, value)) {
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write file:" << space << std::endl;
        fail = true;
        return value;
    }
    return value;
}

void dat::DataBase::operator+=(const std::string &delta) const noexcept
{
    if (!file::AppendFile(space, delta)) {
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to append file:" << space << std::endl;
        fail = true;
        return;
    }
}

std::ostream &dat::operator<<(std::ostream &os, const DataBase &db)
{
    os << (std::string)db;
    return os;
}
