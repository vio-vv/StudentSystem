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
     * @brief 查询标签是否存在及其值。
     * @param code 学工号
     * @param key 标签键
     * @return YES or NO，第一项为 YES 时第二项为标签值，第一项为 NO 时第二项为 NO_TAG or NO_ACCOUNT
     */
    const std::string QUERY_TAG = _AS_"QUERY_TAG";
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
     * @note 创建的帐户想要拥有某权限，创建者必须先拥有该权限，否则创建的帐户将没有该权限。
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
    /**
     * @brief 授予指定权限。
     * @param code 学工号
     * @param password 密码
     * @param codeToGrant 被授予权限的帐户学工号
     * @param access 权限 @see @namespace Access
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 被授予权限的帐户不存在等
     * @note ACCESS REQUIRED GRANT_ACCESS
     * @note 想要授予某权限，授予者必须先拥有该权限，否则返回 ACCESS_DENIED。
     */
    const std::string GRANT_ACCESS = _AS_"GRANT_ACCESS";
    /**
     * @brief 撤销指定权限。
     * @param code 学工号
     * @param password 密码
     * @param codeToRevoke 被撤销权限的帐户学工号
     * @param access 权限 @see @namespace Access
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 被撤销权限的帐户不存在等
     * @note ACCESS REQUIRED REVOKE_ACCESS
     * @note 想要撤销某权限，撤销者必须先拥有该权限，否则返回 ACCESS_DENIED。
     */
    const std::string REVOKE_ACCESS = _AS_"REVOKE_ACCESS";
    /**
     * @brief 撤销所有权限。
     * @param code 学工号
     * @param password 密码
     * @param codeToRevoke 被撤销所有权限的帐户学工号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 被撤销权限的帐户不存在等
     * @note ACCESS REQUIRED REVOKE_ACCESS
     * @note 想要撤销所有权限，撤销者必须先拥有该权限，否则该权限不会被撤销成功。
     */
    const std::string REVOKE_ALL_ACCESS = _AS_"REVOKE_ALL_ACCESS";
    /**
     * @brief 增加或修改标签。
     * @param code 学工号
     * @param password 密码
     * @param codeToAddTag 待增加或修改标签的帐户学工号
     * @param key 标签键
     * @param value 标签值
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 待增加或修改标签的帐户不存在等
     * @note ACCESS REQUIRED ADD_TAG
     * @note 标签已经存在，覆盖标签的值。
     */
    const std::string ADD_TAG = _AS_"ADD_TAG";
    /**
     * @brief 删除标签。
     * @param code 学工号
     * @param password 密码
     * @param codeToRemoveTag 待删除标签的帐户学工号
     * @param key 标签键
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 待增加或修改标签的帐户不存在，标签不存在等
     * @note ACCESS REQUIRED REMOVE_TAG
     */
    const std::string REMOVE_TAG = _AS_"REMOVE_TAG";
    /**
     * @brief 清空标签。
     * @param code 学工号
     * @param password 密码
     * @param codeToClearTag 待清空标签的帐户学工号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 待清空标签的帐户不存在等
     * @note ACCESS REQUIRED REMOVE_TAG
     */
    const std::string CLEAR_TAG = _AS_"CLEAR_TAG";
    /**
     * @brief 重置帐户与权限系统。
     * @param code 学工号
     * @param password 密码
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @note ACCESS REQUIRED RESET_ACCOUNT_AND_ACCESS
     * @note 重置后，所有数据都会被删除。
     */
    const std::string RESET_ACCOUNT_AND_ACCESS = _AS_"RESET_ACCOUNT_AND_ACCESS";
#pragma endregion

#pragma region 课程系统
    ;
#pragma endregion

#pragma region 图书馆系统
    enum bk {
        BOOK_ISBN = 1,
        BOOK_NAME,
        BOOK_AUTHOR,
        BOOK_CATAGORY,
        BOOK_PUBLISHDATE,
        BOOK_STROEPOSTION,
    };
    /**
     * @brief 对匹配的图书按指定内容排序
     * @param sortFunction 排序函数，排序变量需为图书成员数据
     * @return SUCC or FAIL
     * @note 需先使用SEARCH_BOOK进行检索，然后使用SHOW_BOOK_LIST获取排序后图书
     */
    const std::string SORT_BOOK = _AS_"SORT_BOOK";
    /**
     * @brief 下架图书
     * @param code 学工号
     * @param password 密码
     * @param isbn 作为索引 书籍 ISBN 号
     * @param amount 下架数量 若为all，则下架该书所有存量
     * @return SUCC or NO_BOOK or EXCEED_BOOK_NUM or ACCESS_DENIED
     * @note ACCESS REQUIRED BOOK_MANAGE
     */
    const std::string REMOVE_BOOK = _AS_"REMOVE_BOOK";
    /**
     * @借阅书籍
     * @param code 学工号
     * @param password 密码
     * @param isbn 作为索引 书籍 ISBN 号
     * @param borrowPeriod 借阅期限
     * @return SUCC or NO_BOOK or NO_SPARE_BOOK or ACCESS_DENIED
     * @note ACCESS REQUIRED BORROW_BOOK
     */
    const std::string BORROW_BOOK = _AS_"BORROW_BOOK";
    /**
     * @brief 查看账户借阅列表
     * @param code 学工号
     * @param password 密码
     * @return 第一项为 NO_ACCOUNT or SUCCESS, 第二项为 BorrowLog 列表
     */
    const std::string GET_ACCOUNT_BORROW_LIST = _AS_"GET_ACCOUNT_BORROW_LIST";
    /**
     * @brief 归还书籍
     * @param code 学工号
     * @param password 密码
     * @param isbn 书籍 ISBN 号 作为索引
     * @param borrowDate 借阅时间 作为索引 
     * @return SUCC or FAIL or NO_BORROW_RECORD
     */
    const std::string RETURN_BOOK = _AS_"RETURN_BOOK";
    /**
     * @brief 搜索图书。
     * @param searchKey 查找关键字
     * @param searchType 查找图书属性 默认为书名
     * @param replace true 则重新进行检索, false 则仅进行排序
     * @param sortFunction 排序函数，排序变量需为图书成员数据 @see @struct Book
     * @return 第一项为 FAIL or SUCCESS, 第二项为 Book 列表
     */
    const std::string SEARCH_BOOK = _AS_"SEARCH_BOOK";
    /**
     * @brief 存储书籍
     * @param code 学工号
     * @param password 密码
     * @param isbn 作为索引 书籍 ISBN 号
     * @param amount 存放数量
     * @param bookInfo 书籍信息 @see @struct Book
     * @return SUCC or FAIL or ACCESS_DENIED
     * @note ACCESS REQUIRED BOOK_MANAGE
     */
    const std::string RESTORE_BOOK = _AS_"RESTORE_BOOK";
    /**
     * @brief 修改书籍信息
     * @param code 学工号
     * @param password 密码
     * @param isbn 作为索引 书籍 ISBN 号
     * @param bookInfo 书籍信息 @see @struct Book
     * @return SUCC or NO_BOOK or EXIST_BOOK or ACCESS_DENIED   
     * @note ACCESS REQUIRED BOOK_MANAGE
     */
    const std::string MODIFY_BOOK_INFO = _AS_"MODIFY_BOOK_INFO";
    /**
     * @brief 发送还书提醒。
     * @return SUCC or FAIL
     */
    const std::string SEND_RETURN_REMINDER = _AS_"SEND_RETURN_REMINDER";

    //extra

    const std::string ADD_FAVOURATE = _AS_"ADD_FAVOURATE";
    const std::string REMOVE_FAVOURATE = _AS_"REMOVE_FAVOURATE";
    const std::string SHOW_FAVOURATE_LIST = _AS_"SHOW_FAVOURATE_LIST";
    const std::string SEARCH_FAVOURATE = _AS_"SEARCH_FAVOURATE";
#pragma endregion

#pragma region 在线饭堂系统
    /**
     * @brief 开设店铺。
     * @param code 学工号
     * @param password 密码
     *  // TODO
     */
    const std::string SET_A_RESTAURANT = _AS_"SET_A_RESTAURANT";
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
    /**
     * @brief 清空消息。
     * @param code 学工号
     * @param password 密码
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @note ACCESS REQUIRED DELETE_MESSAGE
     */
    const std::string CLEAR_MESSAGE = _AS_"CLEAR_MESSAGE";
    /**
     * @brief 删除别人的消息。
     * @param code 学工号
     * @param password 密码
     * @param codeToDeleteMessage 待删除消息的学工号
     * @param index ull 消息索引
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 待删除消息的帐户不存在，索引超出范围等
     * @note ACCESS REQUIRED DELETE_MESSAGE_OF_OTHERS
     */
    const std::string DELETE_MESSAGE_OF_OTHERS = _AS_"DELETE_MESSAGE_OF_OTHERS";
    /**
     * @brief 清空别人的消息。
     * @param code 学工号
     * @param password 密码
     * @param codeToClearMessage 待清空消息的学工号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL 待清空消息的帐户不存在等
     * @note ACCESS REQUIRED DELETE_MESSAGE_OF_OTHERS
     */
    const std::string CLEAR_MESSAGE_OF_OTHERS = _AS_"CLEAR_MESSAGE_OF_OTHERS";
    /**
     * @brief 重置邮件系统。
     * @param code 学工号
     * @param password 密码
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @note ACCESS REQUIRED RESET_MAIL_SYSTEM
     * @note 重置后，所有数据都会被删除。
     */
    const std::string RESET_MAIL_SYSTEM = _AS_"RESET_MAIL_SYSTEM";
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
    const std::string NO_TAG = _AS_"NO_TAG";
    
    const std::string NO_BOOK = _AS_"NO_BOOK";
    const std::string EXIST_BOOK = _AS_"EXIST_BOOK";
    const std::string NO_SPARE_BOOK = _AS_"NO_SPARE_BOOK";
    const std::string EXCEED_BOOK_NUM = _AS_"EXCEED_BOOK_NUM";
    const std::string NO_BORROW_RECORD = _AS_"NO_BORROW_RECORD";
}
namespace Access{
    const std::string ADM = _AS_"ADM";                   // 拥有这个权限表示拥有所有权限
    const std::string EVERYONE_OWN = _AS_"EVERYONE_OWN"; // 这个权限被所有人拥有

    const std::string CREATE_ACCOUNT = _AS_"CREATE_ACCOUNT";
    const std::string DELETE_ACCOUNT = _AS_"DELETE_ACCOUNT";
    const std::string GRANT_ACCESS = _AS_"GRANT_ACCESS";
    const std::string REVOKE_ACCESS = _AS_"REVOKE_ACCESS"; // 有这个权限才能撤销或清空别人的权限
    const std::string ADD_TAG = _AS_"ADD_TAG";
    const std::string REMOVE_TAG = _AS_"REMOVE_TAG"; // 有这个权限才能删除或清空别人的标签
    const std::string RESET_ACCOUNT_AND_ACCESS = _AS_"RESET_ACCOUNT_AND_ACCESS";

    const std::string SEND_MESSAGE = _AS_"SEND_MESSAGE";
    const std::string DELETE_MESSAGE = _AS_"DELETE_MESSAGE"; // 有这个权限才能删除或清空自己的消息
    const std::string DELETE_MESSAGE_OF_OTHERS = _AS_"DELETE_MESSAGE_OF_OTHERS"; // 有这个权限才能删除或清空别人的消息
    const std::string RESET_MAIL_SYSTEM = _AS_"RESET_MAIL_SYSTEM";
    
    const std::string BOOK_MANAGE = _AS_"BOOK_MANAGE";
    const std::string BORROW_BOOK = _AS_"BORROW_BOOK";
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

struct Date {
    time_t currantTime;
    tm *timeInfo;

    Date(time_t _currantTime = 0) noexcept { currantTime = _currantTime ? _currantTime : time(nullptr); timeInfo = localtime(&currantTime); }
    Date(const std::string&) noexcept;
    operator std::string() const noexcept;
    friend int operator-(const Date &date, const Date &other) noexcept 
    {
        double timeDiff = difftime(date.currantTime, other.currantTime);
        return (int) timeDiff / (60 * 60 * 24) + 1;
    }
    friend Date operator+(const Date &date, const int &day) noexcept
    {
        return trm::Date(date.currantTime + day * 60 * 60 * 24);
    }
};

struct BorrowLog {
    int borrowLast;
    Date start;
    Date end;
    std::string borrower;
    std::string bookIsbn;
    BorrowLog(int _borrowLast = 0, const Date &_start = Date(), const std::string &_borrower = "", const std::string &_bookIsbn = "") noexcept
    : borrowLast(_borrowLast), start(_start), end(_start + _borrowLast), borrower(_borrower), bookIsbn(_bookIsbn) {}
    BorrowLog(const std::string &content) noexcept;
    operator std::string() const noexcept;
};


struct Book{
    unsigned int bookTot;                    //  藏书总数
    unsigned int bookBorrowed;               //  借阅总数
    std::string bookIsbn;                    //  图书版号
    std::string bookName;                    //  书名
    std::string bookPublicationDate;        //  出版日期                   
    std::string bookCatagory;                //  分类
    std::string storePosition;               //  藏书位置
    std::vector<std::string> bookAuthor;     //  作者

    Book(const std::string &_bookIsbn, const std::string &_bookName, const std::string &_bookPublicationDate, const std::string &_bookCatagory,
        const std::string &_storePosition, const std::vector<std::string> &_bookAuthor, 
        const unsigned int tot = 1, const unsigned int borrow = 0) noexcept 
    :   bookTot(tot), bookBorrowed(borrow), 
        bookIsbn(_bookIsbn), bookName(_bookName), bookPublicationDate(_bookPublicationDate), bookCatagory(_bookCatagory), storePosition(_storePosition),
        bookAuthor(_bookAuthor) {};
    
    Book(const std::string &constent) noexcept;
    operator std::string() const noexcept;
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

/**
 * @brief 模糊匹配
 * @return 最长公共子序列与较短字符串比值
 */
double FuzzyMatch(const std::string &str1, const std::string &str2) noexcept;

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
