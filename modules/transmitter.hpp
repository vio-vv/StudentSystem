#ifndef __TRANSMITTER_HPP__
#define __TRANSMITTER_HPP__

/**
 * @brief 通过文件系统进行进程间通信，类比起网络的作用。
 * @namespace trm
 * 
 * @par REQUIRES
 * NONE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 * 
 * @author 梁祖章
 */

#include "file_system.hpp"
#include <string>
#include <vector>
#include <utility>
#include <tuple>

namespace trm{

namespace rqs{
    /**
     * @brief 检查服务端在线状态。
     * @param NONE
     * @return YES or NO
     */
    const std::string CHECK_ONLINE = "Are you on?";
}
namespace rpl{
    const std::string YES = "Yes.";
    const std::string NO = "No.";
}

using Message = std::string;
using Infomation = std::vector<Message>;
using Request = std::tuple<unsigned long long, std::string, std::string>;

/**
 * @brief 客户端用以发送消息。
 * @param link 目标链接（文件夹）（相对于自身）
 * @param self 自身链接（文件夹）（相对于对方）
 * @param meassage 消息
 * @return 答复编号
 * @retval 0 发送失败
 * @retval 其他正整数 发送成功，为正常的答复编号
 */
unsigned long long Send(const std::string &link, const std::string &self, const std::string &message) noexcept;
/**
 * @brief 服务端用以获取消息组队列。
 * @param self 自身链接（文件夹）（相对于自身）
 * @return 获取成功与否以及消息组内容
 * @note 获取不成功时第二项为空。
 */
std::pair<bool, std::vector<Group>> Poll(const std::string &self) noexcept;
bool Reply(const std::string &link, const std::string &message) noexcept;
/**
 * @brief 组编信息
 * @param argv 待组编的内容
 * @return 组编完成的消息
 */
std::string Encode(const Infom &argv) noexcept;
/**
 * @brief 解析消息
 * @param tied 待解析的消息
 * @return 解析的消息
 */
Infom Decode(const std::string &tied) noexcept;

/**
 * @brief 将任意类型转为字符串。
 * @param t 待转换的类型
 * @return 转换后的字符串
 */
std::string ToStr(auto t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

}

#endif
