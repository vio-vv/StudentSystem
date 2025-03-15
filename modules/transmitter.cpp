#include "transmitter.hpp"

bool trm::Send(const std::string &link, const std::string &message) noexcept
{
    if (!fs::exists(link) || !fs::is_directory(link)) {
        return false;
    }
    static unsigned long long count = 0;
    std::string filePath;
    if (link[link.size() - 1] == '/' || link[link.size() - 1] == '\\') {
        filePath = link + ToStr(count);
    } else {
        filePath = link + "\\" + ToStr(count);
    }
    ++count;
    return WriteFile(filePath, message);
}

std::pair<bool, std::vector<std::string>> trm::Poll(const std::string &link) noexcept
{
    if (!fs::exists(link) || !fs::is_directory(link)) {
        return {false, {}};
    }
    std::vector<std::string> result;
    for (const auto &entry : fs::directory_iterator(link)) {
        auto read = ReadFile(entry.path().string());
        if (!read.first) {
            return {false, {}};
        }
        result.push_back(read.second);
    }
    return {true, result};
}

std::string trm::Encode(const std::vector<std::string> &argv) noexcept
{
    std::string result;
    for (const auto &each : argv) {
        result += each + "\x1d";
    }
    return result;
}

std::vector<std::string> trm::Decode(const std::string &tied) noexcept
{  
    std::vector<std::string> result;
    std::string current;
    for (auto c : tied) {
        if (c == '\x1d') {
            result.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    return result;
}

bool trm::CheckFileExists(const std::string &filePath) noexcept
{
    return fs::exists(filePath);
}

std::pair<bool, std::string> trm::ReadFile(const std::string &filePath) noexcept
{
    std::ifstream file(filePath);
    if (!file.good()) {
        return {false, ""};
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return {true, content};
}

bool trm::WriteFile(const std::string &filePath, const std::string &content) noexcept
{
    std::ofstream file(filePath);
    if (!file.good()) {
        return false;
    }
    file << content;
    return true;
}

bool trm::AppendFile(const std::string &filePath, const std::string &content) noexcept
{
    std::ofstream file(filePath, std::ios_base::app);
    if (!file.good()) {
        return false;
    }
    file << content;
    return true;
}

bool trm::DeleteFile(const std::string &filePath) noexcept
{
    return fs::remove(filePath);
}
