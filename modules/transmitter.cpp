#include "transmitter.hpp"

unsigned long long trm::GenerateID() noexcept
{
    static unsigned long long count = 0;
    ++count;
    return count;
}

bool trm::MakeRequest(const std::string &link, const Request &request) noexcept
{
    if (!file::CheckDirectoryExists(link)) {
        return false;
    }
    std::string filePath = file::GetFilePath(link, ToStr(request.id));
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
        request.id = ToUll(fileName);
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

bool trm::SendReply(const std::string &link, unsigned long long id, const Infomation &reply) noexcept
{
    if (!file::CheckDirectoryExists(link)) {
        return false;
    }
    auto filePath = file::GetFilePath(link, ToStr(id));
    return file::WriteFile(filePath, Encode(reply));
}

std::pair<bool, trm::Infomation> trm::PollReply(const std::string &self, unsigned long long id) noexcept
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
    Message result;
    for (const auto &each : infomation) {
        result += each + "\x1d";
    }
    return result;
}

trm::Infomation trm::Decode(const Message &message) noexcept
{
    Infomation result;
    std::string current;
    for (auto c : message) {
        if (c == '\x1d') {
            result.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    return result;
}

unsigned long long trm::ToUll(const std::string &s) noexcept
{
    unsigned long long result = 0;
    for (auto c : s) {
        result = result * 10 + (c - '0');
    }
    return result;
}
