#include "transmitter.hpp"

unsigned long long trm::Send(const std::string &link, const std::string &self, const std::string &message) noexcept
{
    static unsigned long long count = 0;

    if (file::CheckDirectoryExists(link)) {
        return 0;
    }
    ++count;
    std::string filePath;
    if (link[link.size() - 1] == '/' || link[link.size() - 1] == '\\') {
        filePath = link + ToStr(count);
    } else {
        filePath = link + '\\' + ToStr(count) + '\x1d' + self;
    }
    if (WriteFile(filePath, message)) {
        return count;
    }else {
        return 0;
    }
}

std::pair<bool, std::vector<trm::Group>> trm::Poll(const std::string &self) noexcept
{
    if (!fs::exists(self) || !fs::is_directory(self)) {
        return {false, {}};
    }
    std::vector<Group> result;
    for (const auto &entry : fs::directory_iterator(self)) {
        unsigned long long number;
        std::string link;
        
        auto read = ReadFile(entry.path().string());
        if (!read.first) {
            return {false, {}};
        }
        result.push_back({, , read.second});
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
