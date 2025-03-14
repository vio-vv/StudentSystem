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
 * 主要功能：
 * - @fn Send 发送消息
 * - @fn Poll 获取消息队列
 * - @fn Encode 组编消息
 * - @fn Decode 解析消息
 * 两端共同语言
 * - @namespace rqs 请求列表
 * - @namespace rpl 响应列表
 * 也提供其他基础的文件读写功能：
 * - @fn CheckFileExist 判断文件是否存在
 * - @fn ReadFile 读文件
 * - @fn WriteFile 覆盖写文件
 * - @fn AppendFile 追加写文件
 * - @fn DeleteFile 删除文件
 * @note 不适合大文件的读写
 * 
 * @author 梁祖章
 */

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <filesystem>
#include <ctime>

namespace trm{

namespace fs = std::filesystem;

namespace rqs{
    /**
     * @brief 检查服务端在线状态
     * @param NONE
     * @return YES or NO
     */
    const std::string CHECK_ONLINE = "Are you on?";
}
namespace rpl{
    const std::string YES = "Yes.";
    const std::string NO = "No.";
}

/**
 * @brief 发送消息
 * @param link 目标链接（文件夹）
 * @param meassage 消息
 * @return 发送成功与否
 */
bool Send(const std::string &link, const std::string &message) noexcept;
/**
 * @brief 获取消息队列
 * @param link 自身链接（文件夹）
 * @return 获取成功与否以及~~按时间顺序排列~~的消息内容，获取不成功时第二项为空
 * @warning 按时间顺序排列的功能未实现
 * @todo 按时间顺序排列
 */
std::pair<bool, std::vector<std::string>> Poll(const std::string &link) noexcept;
/**
 * @brief 组编消息
 * @param argv 待组编的内容
 * @return 组编完成的消息
 */
std::string Encode(const std::vector<std::string> &argv) noexcept;
/**
 * @brief 解析消息
 * @param tied 待解析的消息
 * @return 解析的消息
 */
std::vector<std::string> Decode(const std::string &tied) noexcept;

/**
 * @brief 判断文件是否存在
 * @param filePath 文件路径
 * @return 文件存在与否
 * @note 返回值为假时表示文件不存在或权限不足
 */
bool CheckFileExists(const std::string &filePath) noexcept;
/**
 * @brief 读文件
 * @param filePath 文件路径
 * @return 读取成功与否以及文件全部内容，读取不成功时第二项为空
 */
std::pair<bool, std::string> ReadFile(const std::string &filePath) noexcept;
/**
 * @brief 覆盖写文件
 * @param filePath 文件路径
 * @param content 写入内容
 * @return 写入成功与否
 */
bool WriteFile(const std::string &filePath, const std::string &content) noexcept;
/**
 * @brief 追加写文件
 * @param filePath 文件路径
 * @param content 写入内容
 * @return 写入成功与否
 */
bool AppendFile(const std::string &filePath, const std::string &content) noexcept;
/**
 * @brief 删除文件
 * @param filePath 文件路径
 * @return 删除成功与否
 */
bool DeleteFile(const std::string &filePath) noexcept;

}

#endif
