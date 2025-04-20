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
#include <ctime>
#include "string_integral.hpp"

namespace trm{

namespace rqs{
    /**
     * @brief 检查服务端在线状态。
     * @param NONE
     * @return YES
     */
    const std::string CHECK_ONLINE = "CHECK_ONLINE";

#pragma region <<<--- 接口列表 --->>>
#pragma region 帐户与权限系统
    /**
     * @brief 检查帐户是否存在。
     * @param code 学工号
     * @return YES or NO
     */
    const std::string CHECK_ACCOUNT_EXISTS = "CHECK_ACCOUNT_EXISTS";
    /**
     * @brief 检查帐号密码是否有效。
     * @param username 帐号
     * @param password 密码
     * @return 第一项为 YES or NO，第一项为 YES 时第二项为 Account 帐户对象，第一项为 NO 时第二项为 NO_ACCOUNT or WRONG_PASSWORD @see @struct Account
     */
    const std::string CHECK_ACCOUNT = "CHECK_ACCOUNT";
    /**
     * @brief 检查是否拥有指定权限。
     * @param code 学工号
     * @param password 密码
     * @param access 权限 @see @namespace Access
     * @return YES or NO
     * @retval NO 没有权限，抑或帐户不存在或密码错误等
     */
    const std::string CHECK_ACCESS = "CHECK_ACCESS";
    /**
     * @brief 创建新帐户。
     * @param code 学工号
     * @param password 密码
     * @param account Account 帐户对象 @see @struct Account
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 帐号已存在等
     * @note ACCESS REQUIRED CREATE_ACCOUNT
     * @note 创建的帐户想要拥有某权限，创建者必须现拥有该权限，否则创建的帐户将没有该权限。
     */
    const std::string CREATE_ACCOUNT = "CREATE_ACCOUNT";
    /**
     * @brief 删除帐户。
     * @param code 学工号
     * @param password 密码
     * @param codeToDelete 待删除帐户的学工号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 待删除的帐户不存在等
     * @note ACCESS REQUIRED DELETE_ACCOUNT
     */
    const std::string DELETE_ACCOUNT = "DELETE_ACCOUNT";
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
    /**
     * @brief 发送消息。
     * @param code 学工号
     * @param password 密码
     * @param receiver 接收者学工号
     * @param message 消息内容
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @note ACCESS REQUIRED SEND_MESSAGE
     */
    const std::string SEND_MESSAGE = "SEND_MESSAGE";
    /**
     * @brief 获取消息数量。
     * @param code 学工号
     * @return ull 消息数量 or NO_ACCOUNT
     */
    const std::string GET_MESSAGE_NUMBER = "GET_MESSAGE_NUMBER";
#pragma endregion
#pragma endregion
}
#pragma region <<<--- 常量列表 --->>>
namespace rpl{
    const std::string ACCESS_DENIED = "ACCESS_DENIED";
    const std::string YES = "YES";
    const std::string NO = "NO";
    const std::string SUCC = "SUCC";
    const std::string FAIL = "FAIL";
    const std::string NO_ACCOUNT = "NO_ACCOUNT";
    const std::string WRONG_PASSWORD = "WRONG_PASSWORD";
}
namespace Access{
    const std::string ADM = "ADM";

    const std::string CREATE_ACCOUNT = "CREATE_ACCOUNT";
    const std::string DELETE_ACCOUNT = "DELETE_ACCOUNT";

    const std::string SEND_MESSAGE = "SEND_MESSAGE";
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
struct MailContent {
    unsigned long long timeStamp;
    std::string sender;
    std::string receiver;
    std::string content;
    MailContent(unsigned long long _timeStamp, const std::string &_sender, const std::string &_receiver, const std::string &_content) noexcept :
        timeStamp(_timeStamp), sender(_sender), receiver(_receiver), content(_content) {}
    operator std::string() const noexcept;
    MailContent(const std::string &content) noexcept;
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
 * @brief 获取时间戳。
 */
unsigned long long GetTimeStamp() noexcept;

template <typename List> concept Iterable = requires (List list) { list.begin(); list.end(); ++list.begin(); };
template <typename List, typename InputType> concept TypeCorrespond = requires (List list, InputType input) { input = *list.begin(); };
/**
 * TO_COMPLETE
 */
template <typename ReturnType, typename InputType, typename List> requires Iterable<List> && TypeCorrespond<List, InputType>
std::vector<ReturnType> Foreach(const List &series, const std::function<ReturnType (const InputType &)> &func) noexcept
{
    std::vector<ReturnType> result;
    for (const auto &each : series) {
        result.push_back(func(each));
    }
    return result;
}

}

#endif
