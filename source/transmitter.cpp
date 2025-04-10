#include "transmitter.hpp"

int trm::GenerateID() noexcept
{
    static int count = 0;
    ++count;
    return count;
}

bool trm::MakeRequest(const std::string &link, const Request &request) noexcept
{
    if (!file::CheckDirectoryExists(link)) {
        return false;
    }
    std::string filePath = file::GetFilePath(link, Combine({ToStr(request.id), ToStr(GenerateRandomCode())}, '.'));
    auto info = request.content;
    info.push_back(request.sender);
    return file::WriteFile(filePath, Encode(info));
}

std::pair<bool, std::vector<trm::Request>> trm::GetRequests(const std::string &self) noexcept
{
    if (!file::CheckDirectoryExists(self)) {
        return {false, {}};
    }
    std::vector<Request> result;
    auto ok_files = file::ListDirectory(self);
    if (!ok_files.first) {
        return {false, {}};
    }
    for (const auto &fileName : ok_files.second) {
        Request request;
        auto id_code = Split(fileName, '.');
        request.id = ToNum(id_code[0]);
        auto ok_read = file::ReadFile(file::GetFilePath(self, fileName));
        if (!ok_read.first) {
            return {false, {}};
        }
        auto tmp = Decode(ok_read.second);
        request.sender = tmp.back();
        tmp.pop_back();
        request.content = tmp;
        result.push_back(request);
    }
    for (const auto &fileName : ok_files.second) {
        file::DeleteFile(file::GetFilePath(self, fileName));
    }
    return {true, result};
}

bool trm::SendReply(const std::string &link, int id, const Infomation &reply) noexcept
{
    if (!file::CheckDirectoryExists(link)) {
        return false;
    }
    auto filePath = file::GetFilePath(link, ToStr(id));
    return file::WriteFile(filePath, Encode(reply));
}

std::pair<bool, trm::Infomation> trm::PollReply(const std::string &self, int id) noexcept
{
    auto filePath = file::GetFilePath(self, ToStr(id));
    if (!file::CheckFileExists(filePath)) {
        return {false, {}};
    }
    auto ok_read = file::ReadFile(filePath);
    if (!ok_read.first) {
        return {false, {}};
    }
    file::DeleteFile(filePath);
    return {true, Decode(ok_read.second)};
}

trm::Message trm::Encode(const Infomation &infomation) noexcept
{
    return Combine(infomation);
}

trm::Infomation trm::Decode(const Message &message) noexcept
{
    return Split(message);
}

std::string trm::Combine(const std::vector<std::string> &series) noexcept
{
    std::string result = "";
    for (const auto &each : series) {
        result += '\x1d' + each + '\x1f';
    }
    return result;
}

std::vector<std::string> trm::Split(const std::string &str) noexcept
{
    std::vector<std::string> result;
    std::string current = "";
    int openerCount = 0;
    for (auto c : str) {
        if (openerCount > 0) {
            if (c == '\x1f') {
                --openerCount;
                if (openerCount == 0) {
                    result.push_back(current);
                    current = "";
                    continue;
                }
            }
            current += c;
        }
        if (c == '\x1d') {
            ++openerCount;
        }
    }
    return result;
}

std::string trm::Combine(const std::vector<std::string> &series, char delimiter) noexcept
{
    std::string result = "";
    for (const auto &each : series) {
        result += each + delimiter;
    }
    return result;
}

std::vector<std::string> trm::Split(const std::string &str, char delimiter) noexcept
{
    std::vector<std::string> result;
    std::string current = "";
    for (auto c : str) {
        if (c == delimiter) {
            result.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    return result;
}

unsigned long long trm::GenerateRandomCode() noexcept
{
    static std::mt19937 generator(time(nullptr));
    static std::uniform_int_distribution<unsigned long long> distribution(0, 1e18);
    return distribution(generator);
}

std::string trm::Hash(const std::string &str) noexcept
{
    return str; // TODO: implement hash function
}
