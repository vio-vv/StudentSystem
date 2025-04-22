#ifndef __TRANSMITTER_HPP__
#define __TRANSMITTER_HPP__

#ifdef NDEBUG
    #define _AS_ ToStr(__LINE__) + 
#else
    #define _AS_
#endif

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
#include "data_base.hpp"
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
    const std::string CHECK_ONLINE = _AS_"CHECK_ONLINE";

#pragma region <<<--- 接口列表 --->>>
#pragma region 帐户与权限系统
    /**
     * @brief 检查帐户是否存在。
     * @param code 学工号
     * @return YES or NO
     */
    const std::string CHECK_ACCOUNT_EXISTS = _AS_"CHECK_ACCOUNT_EXISTS";
    /**
     * @brief 检查帐号密码是否有效。
     * @param username 帐号
     * @param password 密码
     * @return 第一项为 YES or NO，第一项为 YES 时第二项为 Account 帐户对象，第一项为 NO 时第二项为 NO_ACCOUNT or WRONG_PASSWORD @see @struct Account
     */
    const std::string CHECK_ACCOUNT = _AS_"CHECK_ACCOUNT";
    /**
     * @brief 检查是否拥有指定权限。
     * @param code 学工号
     * @param password 密码
     * @param access 权限 @see @namespace Access
     * @return YES or NO
     * @retval NO 没有权限，或者帐户不存在或密码错误等
     */
    const std::string CHECK_ACCESS = _AS_"CHECK_ACCESS";
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
    const std::string CREATE_ACCOUNT = _AS_"CREATE_ACCOUNT";
    /**
     * @brief 删除帐户。
     * @param code 学工号
     * @param password 密码
     * @param codeToDelete 待删除帐户的学工号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 待删除的帐户不存在等
     * @note ACCESS REQUIRED DELETE_ACCOUNT
     */
    const std::string DELETE_ACCOUNT = _AS_"DELETE_ACCOUNT";
#pragma endregion

#pragma region 课程系统
    ;
#pragma endregion

#pragma region 图书馆系统
    /**
     * 
     * 
     */
    const std::string SORT_BOOK = "SORT_BOOK";
    const std::string MOVE_BOOK = "MOVE_BOOK";
    const std::string BORROW_BOOK = "BORROW_BOOK";
    const std::string RETURN_BOOK = "RETURN_BOOK";
    const std::string SEARCH_BOOK = "SEARCH_BOOK";
    /**
     * @brief 存储书籍
     * @param code 学工号
     * @param password 密码
     * @param isbn 作为索引 书籍 ISBN 号
     * @param amount 存放数量
     * @param bookInfo 书籍信息
     * @return SUCC or ACCESS_DENIED or FAIL
     * @note ACCESS REQUIRED RESTORE_BOOK
     */
    const std::string RESTORE_BOOK = "RESTORE_BOOK";
    const std::string SHOW_BOOK_LIST = "SHOW_BOOK_LIST";
    const std::string MODIFY_BOOK_INFO = "MODIFY_BOOK_INFO";
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
     * @param subject 主题
     * @param message 消息内容
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 发送目标帐户不存在等
     * @note ACCESS REQUIRED SEND_MESSAGE
     */
    const std::string SEND_MESSAGE = _AS_"SEND_MESSAGE";
    /**
     * @brief 获取总的消息数量。
     * @param code 学工号
     * @param password 密码
     * @return ull 消息数量，或者 ACCESS_DENIED
     */
    const std::string GET_MESSAGE_NUMBER = _AS_"GET_MESSAGE_NUMBER";
    /**
     * @brief 获取按时间排序特定范围的总的消息的摘要。
     * @param code 学工号
     * @param password 密码
     * @param start ull 起始位置
     * @param count ull 数量
     * @return 消息摘要列表，一般共 count 项，每项都是一个消息的摘要，或者 ACCESS_DENIED
     * @note 消息摘要就是 content 属性为空的 MailContent 对象。 @see @struct MailContent
     * @note 超出索引范围，返回的相应项为空，特别地，完全超出索引范围，返回空列表，有 0 项。
     */ 
    const std::string GET_MESSAGE_PROFILE = _AS_"GET_MESSAGE";
    /**
     * @brief 获取按时间排序的特定消息，如果该消息未读，则标记为已读。
     * @param code 学工号
     * @param password 密码
     * @param index ull 消息索引
     * @return 消息对象 or FAIL，或者 ACCESS_DENIED @see @struct MailContent
     * @retval FAIL 索引超出范围等
     */
    const std::string GET_MESSAGE = _AS_"GET_MESSAGE";
    /**
     * @brief 标记消息为已读。
     * @param code 学工号
     * @param password 密码
     * @param index ull 消息索引
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 索引超出范围等
     */
    const std::string MARK_AS_READ = _AS_"MARK_AS_READ";
    /**
     * @brief 标记消息为未读。
     * @param code 学工号
     * @param password 密码
     * @param index ull 消息索引
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 索引超出范围等
     */
    const std::string MARK_AS_UNREAD = _AS_"MARK_AS_UNREAD";
    /**
     * @brief 获取未读消息数量。
     * @param code 学工号
     * @param password 密码
     * @return ull 未读消息数量，或者 ACCESS_DENIED
     */
    const std::string GET_UNREAD_MESSAGE_NUMBER = _AS_"GET_UNREAD_MESSAGE_NUMBER";
    /**
     * @brief 删除消息。
     * @param code 学工号
     * @param password 密码
     * @param index ull 消息索引
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 索引超出范围等
     * @note ACCESS REQUIRED DELETE_MESSAGE
     */
    const std::string DELETE_MESSAGE = _AS_"DELETE_MESSAGE";
#pragma endregion
#pragma endregion
}
#pragma region <<<--- 常量列表 --->>>
namespace rpl{
    const std::string ACCESS_DENIED = _AS_"ACCESS_DENIED";
    const std::string YES = _AS_"YES";
    const std::string NO = _AS_"NO";
    const std::string SUCC = _AS_"SUCC";
    const std::string FAIL = _AS_"FAIL";
    const std::string NO_ACCOUNT = _AS_"NO_ACCOUNT";
    const std::string WRONG_PASSWORD = _AS_"WRONG_PASSWORD";
}
namespace Access{
    const std::string ADM = _AS_"ADM";                   // 拥有这个权限表示拥有所有权限
    const std::string EVERYONE_OWN = _AS_"EVERYONE_OWN"; // 这个权限被所有人拥有

    const std::string CREATE_ACCOUNT = _AS_"CREATE_ACCOUNT";
    const std::string DELETE_ACCOUNT = _AS_"DELETE_ACCOUNT";

    const std::string SEND_MESSAGE = _AS_"SEND_MESSAGE";
    const std::string DELETE_MESSAGE = _AS_"DELETE_MESSAGE";

    const std::string RESTORE_BOOK = _AS_"RESTORE_BOOK";
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
    std::string subject;
    std::string content;
    bool read;
    MailContent(unsigned long long _timeStamp, const std::string &_sender, const std::string &_receiver, const std::string &_subject, const std::string &_content, bool _read) noexcept :
        timeStamp(_timeStamp), sender(_sender), receiver(_receiver), subject(_subject), content(_content), read(_read) {}
    operator std::string() const noexcept;
    MailContent(const std::string &content) noexcept;
};

class Book{
public:
    unsigned int book_tot;                    //  藏书总数
    unsigned int book_borrowed;               //  借阅总数
    std::string book_isbn;                    //  图书版号
    std::string book_name;                    //  书名
    std::string book_publication_date;        //  出版日期                   
    std::string book_catagory;                //  分类
    std::string store_position;               //  藏书位置
    std::vector<std::string> book_author;     //  作者
    std::vector<std::string> borrow_log;      //  借阅日志

    Book(const std::string &isbn, const std::string &book_n, const std::string &book_pd, const std::string &book_ct,
        const std::string &book_rp, const std::vector<std::string> &book_ath, 
        const unsigned int tot = 1, const unsigned int borrow = 0, const std::vector<std::string> b_log = {}) noexcept 
    :   book_tot(tot), book_borrowed(borrow), 
        book_isbn(isbn), book_name(book_n), book_publication_date(book_pd), book_catagory(book_ct), store_position(book_rp),
        book_author(book_ath), borrow_log(b_log) {};
    
    Book(const std::string&) noexcept;
    ~Book() noexcept;

    operator std::string() noexcept;
};

#pragma endregion

using Information = std::vector<std::string>;
using Message = std::string;
struct Request{
    int id; // 请求编号
    std::string sender;    // 请求发送者链接（相对于服务端）
    Information content;    // 请求内容
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
bool SendReply(const std::string &link, int id, const Information &reply) noexcept;

/**
 * @brief 客户端用以接收回复。
 * @param self 自身链接（文件夹）（相对于自身）
 * @param id 请求编号
 * @return 是否获得回复以及回复内容
 * @note 未获取时第二项为空。
 */
std::pair<bool, Information> PollReply(const std::string &self, int id) noexcept;

/**
 * @brief 将信息转化为消息。
 * @param information 待转换的信息
 * @return 转换后的消息
 */
Message Encode(const Information &information) noexcept;
/**
 * @brief 将消息转化为信息。
 * @param message 待转换的消息
 * @return 转换后的信息
 */
Information Decode(const Message &message) noexcept;

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
 * @return 时间戳
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
    return std::move(result);
}

}

#endif
