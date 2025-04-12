#ifndef __TRANSMITTER_HPP__
#define __TRANSMITTER_HPP__

/**
 * @brief 通过文件系统进行进程间通信，类比起网络的作用。
 * @namespace trm
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include "file_system.hpp"
#include <functional>
#include <random>

namespace trm{

namespace rqs{
    /**
     * @brief 检查服务端在线状态。
     * @param NONE
     * @return YES
     */
    const std::string CHECK_ONLINE = "CK ONL";

#pragma region 帐户与权限系统
    /**
     * @brief 检查帐号密码是否有效。
     * @param username 帐号
     * @param password 密码
     * @return 第一项为 YES or NO，第一项为 YES 时第二项为 Account 帐户对象，第一项为 NO 时第二项为 NO_ACCOUNT or WRONG_PASSWORD @see @namespace Account
     */
    const std::string CHECK_ACCOUNT = "CK ACC";
    /**
     * @brief 创建新帐户。
     * @param account Account 帐户对象 @see @namespace Account
     * @return SUCC or FAIL
     */
    const std::string CREATE_ACCOUNT = "CR ACC";
#pragma endregion

#pragma region 课程系统
    ;
#pragma endregion

#pragma region 图书馆系统
    ;
#pragma endregion

#pragma region 在线饭堂系统
    ;
#pragma endregion

#pragma region 预约入校系统
    ;
#pragma endregion

#pragma region 通知与公示系统
    ;
#pragma endregion

#pragma region 消息与站内信系统
    ;
#pragma endregion
}
#pragma region <<<--- 常量列表 --->>>
namespace rpl{
    const std::string YES = "Y";
    const std::string NO = "N";
    const std::string SUCC = "SUCC";
    const std::string FAIL = "FAIL";
    const std::string NO_ACCOUNT = "NACC";
    const std::string WRONG_PASSWORD = "WPSW";
}
namespace Access{
    const std::string ALL = "ALL";
}
struct Account{
    using Tag = std::pair<std::string, std::string>;
    std::string code;                  // 学工号
    std::string hashedPassword;        // 密码哈希值
    std::vector<std::string> access;   // 权限列表
    std::vector<Tag> tags;             // 标签列表
    Account(const std::string &_code, const std::string &_hashedPassword, const std::vector<std::string> &_access = {}, const std::vector<Tag> &_tags = {}) noexcept : 
        code(_code), hashedPassword(_hashedPassword), access(_access), tags(_tags) {}
    operator std::string() const noexcept;
    Account(const std::string &content) noexcept;
};

#pragma endregion

using Infomation = std::vector<std::string>;
using Message = std::string;
struct Request{
    int id; // 请求编号
    std::string sender;    // 请求发送者链接（相对于服务端）
    Infomation content;    // 请求内容
};

/**
 * @brief 客户端用以生成请求编号。
 * @return 请求编号
 */
int GenerateID() noexcept;

/**
 * @brief 客户端用以发送请求。
 * @param link 目标链接（文件夹）（相对于自身）
 * @param request 请求内容
 * @return 发送成功与否
 */
bool MakeRequest(const std::string &link, const Request &request) noexcept;

/**
 * @brief 服务端用以获取请求队列。
 * @param self 自身链接（文件夹）（相对于自身）
 * @return 获取成功与否以及请求队列
 * @note 获取不成功时第二项为空。
 */
std::pair<bool, std::vector<Request>> GetRequests(const std::string &self) noexcept;

/**
 * @brief 服务端用以发送回复。
 * @param link 目标链接（文件夹）（相对于自身）
 * @param reply 回复内容
 * @return 发送成功与否
 */
bool SendReply(const std::string &link, int id, const Infomation &reply) noexcept;

/**
 * @brief 客户端用以接收回复。
 * @param self 自身链接（文件夹）（相对于自身）
 * @param id 请求编号
 * @return 是否获得回复以及回复内容
 * @note 未获取时第二项为空。
 */
std::pair<bool, Infomation> PollReply(const std::string &self, int id) noexcept;

/**
 * @brief 将信息转化为消息。
 * @param infomation 待转换的信息
 * @return 转换后的消息
 */
Message Encode(const Infomation &infomation) noexcept;
/**
 * @brief 将消息转化为信息。
 * @param message 待转换的消息
 * @return 转换后的信息
 */
Infomation Decode(const Message &message) noexcept;

/**
 * @brief 将任意类型转为字符串。
 * @param t 待转换的类型
 * @return 转换后的字符串
 */
std::string ToStr(auto t) noexcept
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

/**
 * @brief 将字符串转为整数。
 * @param s 待转换的字符串
 * @return 转换后的整数
 */
template<typename ReturnType = int>
ReturnType ToNum(const std::string &s) noexcept
{
    ReturnType result = 0;
    for (auto c : s) {
        if (c == '-') {
            result = -result;
            continue;
        }
        result = result * 10 + (c - '0');
    }
    return result;
}

/**
 * TO_COMPLETE
 */
std::string Combine(const std::vector<std::string> &series) noexcept;

/**
 * TO_COMPLETE
 */
std::vector<std::string> Split(const std::string &str) noexcept;

/**
 * TO_COMPLETE
 */
std::string Combine(const std::vector<std::string> &series, char delimiter) noexcept;

/**
 * TO_COMPLETE
 */
std::vector<std::string> Split(const std::string &str, char delimiter) noexcept;

/**
 * TO_COMPLETE
 */
std::string Hash(const std::string &str) noexcept;

/**
 * TO_COMPLETE
 */
unsigned long long GenerateRandomCode() noexcept;

/**
 * TO_COMPLETE
 */
template<typename ReturnType, typename InputType>
std::vector<ReturnType> Foreach(const auto &series, const std::function<ReturnType (const InputType &)> &func) noexcept
{
    std::vector<ReturnType> result;
    for (const auto &each : series) {
        result.push_back(func(each));
    }
    return result;
}

}

#endif
