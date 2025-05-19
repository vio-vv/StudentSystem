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
#include "string_integral.hpp"
#include <functional>
#include <random>
#include <ctime>

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
    /**
     * @brief 列出所有帐户的学工号。
     * @param code 学工号
     * @param password 密码
     * @return 学工号列表，或者 ACCESS_DENIED
     * @note ACCESS REQUIRED LIST_ACCOUNT
     */
    const std::string LIST_ACCOUNT = _AS_"LIST_ACCOUNT";
    /**
     * @brief 查看某一帐户的详细信息。
     * @param code 学工号
     * @param password 密码
     * @param codeToQuery 待查询帐户的学工号
     * @return Account 对象，包含帐户信息，或者 ACCESS_DENIED @see @struct Account
     * @note ACCESS REQUIRED LIST_ACCOUNT
     */
    const std::string GET_ACCOUNT_DETAIL = _AS_"GET_ACCOUNT_DETAIL";
#pragma endregion

#pragma region 课程系统
    /**
     * @brief 查询自己的特定课程信息
     * @param code 学工号
     * @param courseName 课程编号
     * @param pageNumber 页面数（待定）
     * @return 第一项为YES/NO，第一项为YES时第二项为CourseInformation,第一项为NO时第二项为NO_MATCH_COURSE @see @struct CourseInformation
     * @retval NO_MATCH_COURSE 没有匹配的课程 
     * @retval CourseInformation 上课周数，上课地点，上课老师
    */
    const std::string SEARCH_COURSE_INFORMATION = _AS_"SEARCH_COURSE_INFORMATION";
    /**
     * @brief 增加课程
     * @param code 学工号
     * @param password 密码
     * @param courseName 课程编号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL COURSE_EXITS 课程已存在等
     * @retval FAIL NO_MATCH_COURSE 待增加课程不存在等
     * @note ACCESS REQUIRED ADD_COURSE
     */
    const std::string ADD_COURSE = _AS_"ADD_COURSE";
    /**
     * @brief 删除课程
     * @param code 学工号
     * @param password 密码
     * @param courseName 课程编号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL NO_MATCH_COURSE待删课程不存在等
     * @note ACCESS REQUIRED DELETE_COURSE
     */
    const std::string DELETE_COURSE = _AS_"DELETE_COURSE";
    /**
     * @brief 查看所有课程
     * @param code 学工号
     * @return SUCC or FAIL
     * @retval SUCC 课程信息列表 @see @struct CourseInformation
     * @retval FAIL NO_COURSE_EXITS
     */
    const std::string CHECK_ALL_COURSE = _AS_"CHECK_ALL_COURSE";
    /**
     * @brief 管理员增加课程
     * @param code 学工号
     * @param password 密码
     * @param courseName 课程编号
     * @param courseInformation 课程信息 @see @struct CourseInformation 
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL COURSE_EXITS课程已存在等
     * @note ACCESS REQUIRED ADM_ADD_COUR 
     */ 
    const std::string ADM_ADD_COUR = _AS_"ADM_ADD_COUR";
    /**
     * @brief 管理员删除课程
     * @param code 学工号
     * @param password 密码
     * @param courseName 课程编号
     * @return SUCC or FAIL，或者 ACCESS_DENIED
     * @retval FAIL NO_MATCH_COURSE待删课程不存在等
     * @note ACCESS REQUIRED ADM_DELETE_COURSE 
    */  
    const std::string ADM_DELETE_COUR = _AS_"ADM_DELETE_COUR";
    
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
     * @return 成功时返回借阅列表，失败时返回 NO_ACCOUNT
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
     * @param isSort 是否进行排序 默认为 false
     * @param ascendingOrder 排序图书属性与searchType相同 排序方式 默认字典序小在前，true 为字典序小在前，false 为字典序大在前
     * @return 成功时返回匹配书籍 失败时返回 FAIL
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
    /**
     * @重置图书馆
     * @param code 学工号
     * @param password 密码
     * @return SUCC 或者 ACCESS_DENIED
     * @note ACCESS REQUIRED RESET_LIBRARY
     */
    const std::string RESET_LIBRARY = _AS_"RESET_LIBRARY";

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
    /**
     * @brief 查询可预约时间
     * @param date 日期 @see @struct Date
     * @return 可预约时间列表 @see @struct ReserveTime
    */
    const std::string CHECK_TIME = _AS_"CHECK_TIME";
    /**
     * @brief 查询特定的预约时间
     * @param date 日期 @see @struct Date
     * @param time 时间
     * @return YES or NO 第一项为 YES时无第二项,第一项为 NO 时第二项为 NO_MATCH_TIME or NO_LEFT_RESERVE
     * @retval NO_MATCH_TIME 预约时间不合法
     * @retval NO_LEFT_RESERVE 预约名额已满
     */
    const std::string CHECK_RESERVE_TIME = _AS_"CHECK_RESERVE_TIME"; 
   /** 
     * @brief 预约入校
     * @param date 日期 @see @struct Date
     * @param time 时间
     * @param id 身份证号
     * @param phone 手机号
     * @return SUCC or FAIL
     * @retval FAIL NO_MATCH_RESERVE 预约时间不合法或者预约名额已满
     * @retval FAIL RESERVE_EXISTS 预约已存在
     */
    const std::string REQUEST_RESERVE = _AS_"REQUEST_RESERVE";
    /**
     * @brief 取消预约
     * @param date 日期 @see @struct Date
     * @param time 时间
     * @param id 身份证号
     * @param phone 手机号
     * @return SUCC or FAIL 或者 RESERVE_ACCESS_DENIED
     * @retval FAIL NO_MATCH_RESERVE 待取消的预约不存在
     * @note ACCESS REQUIRED CANCEL_RESERVE 但不在Acess名称空间里
    */
    const std::string CANCEL_RESERVE = _AS_"CANCEL_RESERVE";
     /**
     * @brief 查询特定预约状态
     * @param date 日期 @see @struct Date
     * @param time 时间
     * @param id 身份证号
     * @param phone 手机号
     * @return SUCC or FAIL 
     * @retval FAIL NO_MATCH_RESERVE 待查询的预约不存在
     * @retval SUCC 预约状态 
     */
    const std::string CHECK_RESERVE_STATUS = _AS_"CHECK_RESERVE_STATUS"; 
    /**
     * @brief 查询预约状态列表
     * @param id
     * @param phone
     * @return SUCC or FAIL
     * @retval FAIL NO_RESERVE_EXISTS 没有预约记录
     * @retval SUCC 预约状态列表
    */
    const std::string CHECK_RESERVE_STATUS_LIST = _AS_"CHECK_RESERVE_STATUS_LIST"; 

   //预约状态的改变还没想好具体怎么写,可能会包装一个结构体还是枚举什么的自动对应状态 

    /**
     * @brief 管理员增加可预约时间
     * @param code 学工号
     * @param password 密码
     * @param date 日期 @see @struct Date
     * @param time 时间
     * @param number 可预约数量
     * @return SUCC or FAIL 或者 ACCESS_DENIED
     * @retval FAIL TIME_HAVE_SET 预约时间已设置
     * @note ACCESS REQUIRED ADM_ADD_RESERVE_TIME 
    */
    const std::string ADM_ADD_RESERVE_TIME = _AS_"ADM_ADD_RESERVE_TIME"; 
    /**
     * @brief 管理员删除可预约时间
     * @param code 学工号
     * @param password 密码
     * @param date 日期 @see @struct Date
     * @param time 时间
     * @return SUCC or FAIL 或者 ACCESS_DENIED
     * @retval FAIL NO_MATCH_TIME 待删除的预约时间不存在
     * @note ACCESS REQUIRED ADM_DELETE_RESERVE_TIME 
    */
    const std::string ADM_DELETE_RESERVE_TIME = _AS_"ADM_DELETE_RESERVE_TIME";
    /**
     * @brief 管理员修改可预约数量 
     * @param code 学工号
     * @param password 密码
     * @param date 日期 @see @struct Date
     * @param time 时间
     * @param number 可预约数量
     * @return SUCC or FAIL 或者 ACCESS_DENIED
     * @retval FAIL NO_MATCH_TIME 待修改的数量对应的预约时间不存在
     * @note ACCESS REQUIRED ADM_MODIFTY_RESERVE_NUMBER
     */
    const std::string ADM_MODIFY_RESERVE_NUMBER = _AS_"ADM_MODIFY_RESERVE_NUMBER";
    
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
    const std::string TIME_OUT = _AS_"TIME_OUT";
    const std::string ACCESS_DENIED = _AS_"ACCESS_DENIED";
    const std::string YES = _AS_"YES";
    const std::string NO = _AS_"NO";
    const std::string SUCC = _AS_"SUCC";
    const std::string FAIL = _AS_"FAI";
    
    const std::string NO_ACCOUNT = _AS_"NO_ACCOUNT";
    const std::string WRONG_PASSWORD = _AS_"WRONG_PASSWORD";
    const std::string NO_TAG = _AS_"NO_TAG";
    
    const std::string NO_MATCH_COURSE = _AS_"NO_MATCH_COURSE";
    const std::string COURSE_EXISTS = _AS_"COURSE_EXISTS";
    const std::string NO_COURSE_EXITS=_AS_"NO_COURSE_EXITS";

    const std::string NO_MATCH_RESERVE = _AS_"NO_MATCH_RESERVE";
    const std::string NO_LEFT_RESERVE = _AS_"NO_LEFT_RESERVE";
    const std::string NO_MATCH_TIME = _AS_"NO_MATCH_TIME";
    const std::string NO_DERESERVE_ACCESS= _AS_"NO_DERESERVE_ACCESS";
    const std::string RESERVE_EXISTS = _AS_"RESERVE_EXISTS";
    const std::string NO_RESERVE_EXISTS = _AS_"NO_RESERVE_EXISTS";
    const std::string TIME_HAVE_SET = _AS_"TIME_HAVE_SET";

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
    const std::string LIST_ACCOUNT = _AS_"LIST_ACCOUNT";

    const std::string SEND_MESSAGE = _AS_"SEND_MESSAGE";
    const std::string DELETE_MESSAGE = _AS_"DELETE_MESSAGE"; // 有这个权限才能删除或清空自己的消息
    const std::string DELETE_MESSAGE_OF_OTHERS = _AS_"DELETE_MESSAGE_OF_OTHERS"; // 有这个权限才能删除或清空别人的消息
    const std::string RESET_MAIL_SYSTEM = _AS_"RESET_MAIL_SYSTEM";
    
    const std::string ADD_COURSE = _AS_"ADD_COURSE";
    const std::string DELETE_COURSE = _AS_"DELETE_COURSE";
    const std::string ADM_ADD_COUR = _AS_"ADM_ADD_COUR";
    const std::string ADM_DELETE_COUR = _AS_"ADM_DELETE_COUR";

    const std::string ADM_SET_RESERVE_NUMBER = _AS_"ADM_SET_RESERVE_NUMBER"; // 管理员设置可预约数量
    const std::string ADM_ADD_RESERVE_TIME = _AS_"ADM_SET_RESERVE_TIME"; // 管理员增加可预约时间
    const std::string ADM_DELETE_RESERVE_TIME = _AS_"ADM_DELETE_RESERVE_TIME"; // 管理员删除可预约时间
    const std::string ADM_MODIFTY_RESERVE_NUMBER = _AS_"ADM_MODIFTY_RESERVE_NUMBER"; // 管理员修改可预约数量

    const std::string BOOK_MANAGE = _AS_"BOOK_MANAGE";
    const std::string BORROW_BOOK = _AS_"BORROW_BOOK";
    const std::string RESET_LIBRARY = _AS_"RESET_LIBRARY";
}
struct Account{
    using Tag = std::pair<std::string, std::string>;
    std::string code;                  // 学工号
    std::string hashedPassword;        // 密码哈希值
    std::vector<std::string> access;   // 权限列表
    std::vector<Tag> tags;             // 标签列表
    Account() noexcept = default;
    Account(const std::string &_code, const std::string &_hashedPassword, const std::vector<std::string> &_access = {}, const std::vector<Tag> &_tags = {}) noexcept : 
        code(_code), hashedPassword(_hashedPassword), access(_access), tags(_tags) {}
    operator std::string() const noexcept;
    Account(const std::string &content) noexcept;
    std::string operator[](const std::string &tagKey) noexcept;
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

    Date(time_t _currantTime = 0) noexcept { currantTime = _currantTime ? _currantTime : time(nullptr); timeInfo = new tm; localtime_s(timeInfo, &currantTime); }
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
//courseName, teacher, location, weeks（vector<string>）
struct CourseInformation {
    std::string courseName;
    std::string teacher;    // 上课老师
    std::string location;   // 上课地点
    //std::string time;      // 上课时间
    std::vector<std::string> weeks; // 上课周数
    CourseInformation(const std::string & _name,const std::string &_teacher, const std::string &_location, const std::vector<std::string> &_weeks) noexcept :
        courseName(_name), teacher(_teacher), location(_location), weeks(_weeks) {}
    operator std::string() const noexcept;
    CourseInformation(const std::string &content) noexcept;
};

struct IdAndPhone 
{
    std::string id; // 身份证号
    std::string phone; // 手机号
    IdAndPhone(const std::string &_id, const std::string &_phone) noexcept :
        id(_id), phone(_phone) {}
    IdAndPhone(const std::string &content) noexcept;
    operator std::string() const noexcept;
};


struct ReserveDate
{
    std::string month; // 月份
    std::string week; // 周数
    std::string date; // 日期
    ReserveDate(const std::string &_month, const std::string &_week, const std::string &_date) noexcept :
        month(_month), week(_week), date(_date) {}
    ReserveDate(const std::string &content) noexcept;
    operator std::string() const noexcept;
};


#pragma endregion

using Information = std::vector<std::string>;
/**
 * @brief 客户端用以发送请求的类。
 * @note 使用前务必完成初始化。
 */
class Sender {
public:
    static void Init(const std::string &link, const std::string &self, const std::string &selfAsSender) noexcept
        { SetLink(link); SetSelf(self); SetSelfAsSender(selfAsSender); }
    static void SetLink(const std::string &serverLink) noexcept { link = serverLink; }
    static void SetSelf(const std::string &selfSpace) noexcept { self = selfSpace; }
    static void SetSelfAsSender(const std::string &selfAsSenderForServer) noexcept { selfAsSender = selfAsSenderForServer; }
    explicit Sender(const Information &content = {rqs::CHECK_ONLINE}, bool autoSend = true) noexcept;
    void SetContent(const Information &content) noexcept;
    void Send() noexcept;
    std::pair<bool, trm::Information> Poll() noexcept;
    int GetID() const noexcept { return id; }
    int GetCount() const noexcept { return count; }
private:
    static std::string link;
    static std::string self;
    static std::string selfAsSender;
    int id;
    int count = 0;
    bool fail = false;
    Information saved;
};

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
 * @brief 将字符串数组信息转化为字符串。
 */
std::string Combine(const std::vector<std::string> &series) noexcept;

/**
 * @brief 将字符串转化为字符串数组。
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

template<typename List> concept Iterable = requires (List list) { list.begin(); list.end(); ++list.begin(); };
template<typename List, typename InputType> concept TypeCorrespond = requires (List list, InputType input) { input = *list.begin(); };
/**
 * TO_COMPLETE
 */
template<typename ReturnType, typename InputType, typename List> requires Iterable<List> && TypeCorrespond<List, InputType>
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
