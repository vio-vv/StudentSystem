#include "transmitter.hpp"

std::string trm::Sender::link;
std::string trm::Sender::self;
std::string trm::Sender::selfAsSender;

const std::string trm::Information::OUT_OF_RANGE = "";

std::vector<std::string> trm::Notice::patition = {"headline", "news", "notice"};

static const std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const trm::AccessInfo &trm::GetAccessInfo(Access access) noexcept
{
    static AccessInfo accessInfo[Access::_];
    static bool initialized = false;
    if (!initialized) {
        for (auto &each : accessInfo) {
            each = {
                "【未命名权限】",
                "【无说明】"
            };
        }
        
        /*******************************
         * @attention EEA 请在此处添加。*
         * *****************************
         */
        accessInfo[Access::ADM] = {"最高管理权限", "相当于拥有所有权限。"};
        accessInfo[Access::CREATE_ACCOUNT] = {"创建帐户", "可以在系统内创建新的帐户。"};
        accessInfo[Access::DELETE_ACCOUNT] = {"删除帐户", "可以删除系统内的帐户。"};
        accessInfo[Access::GRANT_ACCESS] = {"授予权限", "可以授予系统内帐户的权限。"};
        accessInfo[Access::REVOKE_ACCESS] = { "撤销权限", "可以撤销系统内帐户的权限。"};
        accessInfo[Access::ADD_TAG] = {"添加标签", "可以给系统内的帐户添加标签。"};
        accessInfo[Access::REMOVE_TAG] = {"删除标签", "可以删除系统内的帐户的标签。"};
        accessInfo[Access::RESET_ACCOUNT_AND_ACCESS] = {"重置帐户和权限系统", "可以重置帐户和权限系统，即删除所有帐户信息。"};
        accessInfo[Access::LIST_ACCOUNT] = {"查看系统内帐户", "可以查看系统内的帐户信息。"};

        /*******************************
         * @attention LAB 请在此处添加。*
         * *****************************
         */
        // accessInfo[???] = {???, ???};
        // 也可以这样写：accessInfo[???].name = "???";
        // 不写的话会有默认值 "【未命名权限】"、"【无说明】"。
        accessInfo[Access::ADD_COURSE] = {"添加课程", "学生账户可以添加课程。"};
        accessInfo[Access::DELETE_COURSE] = {"删除课程", "学生账户可以删除课程。"};
        accessInfo[Access::ADM_ADD_COUR] = {"开设课程", "管理员账户可以添加课程。"};
        accessInfo[Access::ADM_DELETE_COUR] = {"撤消课程", "管理员账户可以删除课程。"};
        accessInfo[Access::ADM_DELETE_RESERVE_TIME] = {"删除预约时间", "管理员账户可以删除预约时间。"};
        accessInfo[Access::ADM_ADD_RESERVE_TIME] = {"增加预约时间", "管理员账户可以增加预约时间。"};
        accessInfo[Access::ADM_MODIFTY_RESERVE_NUMBER] = {"修改预约数量", "管理员账户可以修改预约数量。"};
        /**********************************
         * @attention VIO_VV 请在此处添加。*
         * ********************************
         */
        accessInfo[Access::BOOK_MANAGE] = {"图书管理", "可以管理图书馆的图书。包括新增图书，修改图书信息，删除图书。"};
        accessInfo[Access::BORROW_BOOK] = {"借阅图书", "可以借阅图书。"};
        accessInfo[Access::RESET_LIBRARY] = {"重置图书馆", "可以重置图书馆，即删除所有图书信息。"};
        accessInfo[Access::MANAGE_NOLIFY] = {"管理通知", "可以管理系统的通知。包括新增通知，删除通知。"};
        // accessInfo[???] = {???, ???};
        // 也可以这样写：accessInfo[???].name = "???";
        // 不写的话会有默认值 "【未命名权限】"、"【无说明】"。

        initialized = true;
    }
    return accessInfo[access];
}

bool trm::Initialize(const std::string &self) noexcept
{
    if (file::CheckDirectoryExists(self)) {
        if (!file::DeleteDirectory(self)) {
            return false;
        }
    }
    if (!file::CreateDirectory(self)) {
        return false;
    }
    return true;
}

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
    std::string filePath = file::GetFilePath(link, Combine({ToStr(request.id), ToStr(GetTimestamp()), ToStr(GenerateRandomCode())}, '.'));
    auto info = request.content;
    info.push_back(request.sender);
    return file::WriteFile(filePath, Encrypt(Encode(info)));
}

std::pair<bool, std::vector<trm::Request>> trm::GetRequests(const std::string &self) noexcept
{
    if (!file::CheckDirectoryExists(self)) {
        return {false, {}};
    }
    std::vector<Request> result;
    auto [success, files] = file::ListDirectory(self);
    if (!success) {
        return {false, {}};
    }
    for (const auto &fileName : files) {
        Request request;
        auto id_time_code = Split(fileName, '.');
        request.id = ToNum(id_time_code[0]);
        auto [success, read] = file::ReadFile(file::GetFilePath(self, fileName));
        if (!success) {
            return {false, {}};
        }
        auto tmp = Decode(Decrypt(read));
        request.sender = tmp.back();
        tmp.pop_back();
        request.content = tmp;
        result.push_back(request);
    }
    for (const auto &fileName : files) {
        if (!file::DeleteFile(file::GetFilePath(self, fileName))) {
            assert(false); // Unexcepted error
        }
    }
    return {true, std::move(result)};
}

bool trm::SendReply(const std::string &link, int id, const Information &reply) noexcept
{
    if (!file::CheckDirectoryExists(link)) {
        return false;
    }
    auto filePath = file::GetFilePath(link, ToStr(id));
    return file::WriteFile(filePath, Encrypt(Encode(reply)));
}

std::pair<bool, trm::Information> trm::PollReply(const std::string &self, int id) noexcept
{
    auto filePath = file::GetFilePath(self, ToStr(id));
    if (!file::CheckFileExists(filePath)) {
        return {false, {}};
    }
    auto [success, read] = file::ReadFile(filePath);
    if (!success) {
        return {false, {}};
    }
    if (!file::DeleteFile(filePath)) {
        assert(false); // Unexcepted error
    }
    return {true, Decode(Decrypt(read))};
}

trm::Message trm::Encode(const Information &information) noexcept
{
    return Combine(information);
}

trm::Information trm::Decode(const Message &message) noexcept
{
    return Split(message);
}
//建议使用
std::string trm::Combine(const std::vector<std::string> &series) noexcept
{
    std::string result = "";
    for (const auto &each : series) {
        result += '\x1d' + each + '\x1f';
    }
    return std::move(result);
}
//建议使用
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
    return std::move(result);
}

std::string trm::Combine(const std::vector<std::string> &series, char delimiter) noexcept
{
    std::string result = "";
    for (const auto &each : series) {
        result += each + delimiter;
    }
    return std::move(result);
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
    return std::move(result);
}

unsigned long long trm::GenerateRandomCode() noexcept
{
    static std::mt19937 generator(time(nullptr));
    static std::uniform_int_distribution<unsigned long long> distribution(0, 1e18);
    return distribution(generator);
}

unsigned long long trm::GetTimestamp() noexcept
{
    return time(nullptr);
}

std::string trm::Hash(const std::string &str) noexcept
{
    std::hash<std::string> hashstr;
    auto hashValue = hashstr(str);
    std::stringstream s;
    s << std::hex << std::setw(16) << std::right << std::setfill('0') << 
        hashValue;
    std::string result;
    s >> result;
    return result;
}

trm::Account::operator std::string() const noexcept
{
    return Combine({
        code, 
        hashedPassword, 
        Combine(Foreach<std::string, Access>(access, [](const Access &each){
            return AccessBox{each};
        })), 
        Combine(Foreach<std::string, Tag>(tags, [](const Tag &each){
            return Combine({each.first, each.second});
        }))
    });
}

trm::MailContent::operator std::string() const noexcept
{
    return Combine({
        ToStr(timeStamp), 
        sender, 
        receiver, 
        subject, 
        content, 
        ToStr((int)read)
    });
}

trm::MailContent::MailContent(const std::string &content) noexcept
{
    auto mailContent = Split(content);
    *this = {
        ToNum<unsigned long long>(mailContent[0]), 
        mailContent[1], 
        mailContent[2], 
        mailContent[3], 
        mailContent[4], 
        (bool)ToNum(mailContent[5])
    };
}

trm::Account::Account(const std::string &content) noexcept
{
    auto account = Split(content);
    *this = {
        account[0], 
        account[1], 
        Foreach<Access, std::string>(trm::Split(account[2]), [](const std::string &each){
            return AccessBox{each};
        }), 
        trm::Foreach<std::pair<std::string, std::string>, std::string>(trm::Split(account[3]), [](const std::string &each){
            auto pair = trm::Split(each);
            return std::make_pair(pair[0], pair[1]);
        })
    };
}

std::string trm::Account::operator[](const std::string &tagKey) noexcept
{
    for (const auto &[k, v] : tags) {
        if (k == tagKey) {
            return v;
        }
    }
    return "";
}

trm::CourseInformation::operator std::string() const noexcept
{
    return Combine({
        courseName,
        teacher, 
        location, 
        Combine(weeks)
    });
}

trm::CourseInformation::CourseInformation(const std::string &content) noexcept
{
    auto course = Split(content);
    *this = {
        course[0], 
        course[1], 
        course[2],
        trm::Split(course[3])
    };
}

trm::IdAndPhone::operator std::string() const noexcept
{
    return Combine({id, phone}, '-');
}

trm::IdAndPhone::IdAndPhone(const std::string &content) noexcept
{
    auto idAndPhone = Split(content, '-');
    *this = {
        idAndPhone[0], 
        idAndPhone[1]
    };
}

trm::ReserveDate::operator std::string() const noexcept
{
    return Combine({ToStr(month), ToStr(week), ToStr(date)},'-');
}
trm::Book::Book(const std::string &content) noexcept
{
    auto data = trm::Split(content);
    *this = {
        data[0],
        data[1],
        data[2],
        data[3],
        data[4],
        trm::Split(data[5]),
        ToNum<unsigned int>(data[6]),
        ToNum<unsigned int>(data[7]),
    };
}

trm::Book::operator std::string() const noexcept
{
    return trm::Combine({
        bookIsbn, bookName,
        bookPublicationDate,
        bookCatagory,
        storePosition,
        trm::Combine(bookAuthor),
        ToStr(bookTot),
        ToStr(bookBorrowed),
    });
}

bool trm::Book::operator==(const Book &other) const noexcept
{
    if (this == &other) return true;
    if (this->bookIsbn != other.bookIsbn ||
        this->bookName != other.bookName ||
        this->bookPublicationDate != other.bookPublicationDate ||
        this->bookCatagory != other.bookCatagory ||
        this->storePosition != other.storePosition)
        {
            return false;
        }
    if (this->bookAuthor.size() != other.bookAuthor.size()) return false;
    for (long long unsigned int i = 0; i < this->bookAuthor.size(); ++i) {
        if (this->bookAuthor[i] != other.bookAuthor[i]) return false;
    }
    return true;
}

std::string trm::Book::GetInfo(const trm::Book &selectedBook) noexcept
{
    std::string tip = "";
    tip = "    ISBN " + selectedBook.bookIsbn + 
            "\n    书名 " + selectedBook.bookName + 
            "\n    作者 ";
    std::string author = "";
    for (long long unsigned int i = 0; i < selectedBook.bookAuthor.size(); ++i) {
        if (i == selectedBook.bookAuthor.size() - 1) author += selectedBook.bookAuthor[i];
        else author += selectedBook.bookAuthor[i] + ",";
    }
    tip += author;
    tip += "\n    出版日期 " + selectedBook.bookPublicationDate + 
            "\n    存放位置 " + selectedBook.storePosition + 
            "\n    图书分类 " + selectedBook.bookCatagory;
    return tip;
}

trm::Date::operator std::string() const noexcept
{
    return trm::Combine({
        ToStr(currantTime)
    });
}
//date 和reservedate的函数交叉有点混乱，但是不建议改位置，很容易冲突
trm::ReserveDate::ReserveDate(const std::string &content) noexcept
{
    auto date = trm::Split(content,'-');
    *this = {
       date[0],
       date[1],
       date[2],
    };
}

trm::Date::Date(const std::string & content) noexcept
{
    auto data = trm::Split(content);
    *this = {
        ToNum<time_t>(data[0])
    };
}

std::string trm::Date::GetDate() const noexcept
{
    std::string ret = "";
    ret += ToStr(timeInfo->tm_year + 1900) + "-" + ToStr(timeInfo->tm_mon + 1) + "-" + ToStr(timeInfo->tm_mday);
    return ret;
}

trm::BorrowLog::operator std::string() const noexcept
{
    return trm::Combine({
        ToStr(borrowLast),
        start,
        borrower,
        bookIsbn,
    });
}

trm::BorrowLog::BorrowLog(const std::string &content) noexcept
{
    auto data = trm::Split(content);
    *this = {
        ToNum<int>(data[0]),
        data[1],
        data[2],
        data[3],
    };
}

void trm::Sender::SetSelf(const std::string &selfSpace) noexcept
{
    self = selfSpace;
}

trm::Sender::Sender(const Information &content, bool autoSend) noexcept
{
    saved = std::move(content);
    if (autoSend) {
        Send();
    }
}

void trm::Sender::SetContent(const Information &content) noexcept
{
    saved = std::move(content);
}

void trm::Sender::Send() noexcept
{
    id = GenerateID();
    if (!MakeRequest(link, {id, selfAsSender, saved})) {
        fail = true;
    }
}

std::pair<bool, trm::Information> trm::Sender::Poll() noexcept
{
    if (fail) {
        return {true, {rpl::FAIL}};
    }
    ++count;
    return PollReply(self, id);
}

trm::AccessBox::operator std::string() const noexcept
{
    return Combine({ToStr((int)access), GetAccessInfo(access).name});
}

trm::AccessBox::AccessBox(const std::string &content) noexcept
{
    *this = {(Access)ToNum(Split(content)[0])};
}

trm::AccessBox::operator Access() const noexcept
{
    return access;
}

trm::Notice::operator std::string() const noexcept
{
    return Combine({
        title,
        content,
        date
    });
}

trm::Notice::Notice(const std::string &content) noexcept
{   
    auto data = trm::Split(content);
    *this = {
        data[0],
        data[1],
        data[2]
    };
}

std::string trm::Notice::GetTitle() const noexcept
{   
    std::string ret; 
    if (title.size() <= 15) {
        return title;
    }
    else {
        ret = title.substr(0, 15) + "...";
        return ret;
    }
}

std::string trm::Notice::GetHeadlineTitle() const noexcept
{
    int len = title.size();
    std::string ret;
    if (title.size() <= 18) {
        return title;
    }
    else if (title.size() <= 36) {
        ret = title.substr(0, 18) + '\n';
        ret += title.substr(18, len - 18);
    }
    else {
        ret = title.substr(0, 18) + '\n';
        ret += title.substr(18, 18) + "...";
    }
    return ret;
}

trm::Message trm::base64Encode(const unsigned char *str, int len) noexcept
{
    std::string res = "";
    
    int i = 0;
    int j = 0;
    unsigned char char_3[3];
    unsigned char char_4[4];

    while (len--) {
        char_3[i++] = *(str++);
        if (i == 3) {
            char_4[0] = (char_3[0] & 0xfc) >> 2;
            char_4[1] = ((char_3[0] & 0x03) << 4) + ((char_3[1] & 0xf0) >> 4);
            char_4[2] = ((char_3[1] & 0x0f) << 2) + ((char_3[2] & 0xc0) >> 6);
            char_4[3] = char_3[2] & 0x3f;
            
            for (i = 0; i < 4; i++) {
                res += base64Chars[char_4[i]];
            }
            i = 0;
        }

    }

    if (i) {
        for (j = i; j < 3; ++j) {
            char_3[j] = '\0';
        }

        char_4[0] = (char_3[0] & 0xfc) >> 2;
        char_4[1] = ((char_3[0] & 0x03) << 4) + ((char_3[1] & 0xf0) >> 4);
        char_4[2] = ((char_3[1] & 0x0f) << 2) + ((char_3[2] & 0xc0) >> 6);
        
        for (j = 0; j < i + 1; ++j) {
            res += base64Chars[char_4[j]];
        }

        while ((i++ < 3)) {
            res += '=';
        }
    }

    return res;
}

trm::Message trm::base64Decode(const trm::Message &str) noexcept
{
    int len = str.size();
    std::string res = "";
    unsigned char char_3[3];
    unsigned char char_4[4];
    int i = 0;
    int j = 0;
    int pos = 0;

    while (len-- && str[pos] != '=') {
        char_4[i++] = str[pos];
        ++pos;
        if (i == 4) {
            for (int i = 0; i < 4; ++i) {
                char_4[i] = base64Chars.find(char_4[i]) & 0xff;
            }
            char_3[0] = (char_4[0] << 2) + ((char_4[1] & 0x30) >> 4);
            char_3[1] = ((char_4[1] & 0xf) << 4) + ((char_4[2] & 0x3c) >> 2);
            char_3[2] = ((char_4[2] & 0x3) << 6) + char_4[3];
            
            for (int i = 0; i < 3; ++i) {
                res += char_3[i];
            }
            i = 0;
        }

    }

    if (i) {
        for (j = 0; j < i; ++j) {
            char_4[j] = base64Chars.find(char_4[j]) & 0xff;
        }

        char_3[0] = (char_4[0] << 2) + ((char_4[1] & 0x30) >> 4);
        char_3[1] = ((char_4[1] & 0xf) << 4) + ((char_4[2] & 0x3c) >> 2);

        for (int j = 0; j < i - 1; ++j) res += char_3[j];
    }
    return res;
}

template<typename String>
std::string encode(String s) {
    return trm::base64Encode(reinterpret_cast<const unsigned char*>(s.data()), s.size());
}

trm::Message trm::Encrypt(const trm::Message &str, const std::string &key) noexcept
{
     int len = str.length();

    std::string res = str;
    
    std::string _key = "&!#^zY-zE)>2d9'cD|*6F<g.h8:_7H=m";
    int keylen = key.size();
    _key = key + _key;

    std::vector<std::string> keybox;

    if (keylen < 32) keylen = 32;
    else if (keylen % 8) keylen += 8 - keylen % 8;

    std::string subkey = "";
    for (int i = 0; i < keylen; ++i) {
        subkey += _key[i];
        if ((i + 1) % 8 == 0) {
            keybox.emplace_back(subkey);
            subkey = "";
        }
    }

    int loop = keybox.size();
    std::string leftstr;
    std::string rightstr;

    while (loop < 8) {
        subkey = "";
        if ((loop + 1) % 4 == 0) {
            subkey = keybox[loop - 1];
            for (int i = 0; i < 8; ++i) {
                subkey[i] = ((subkey[i] * loop) ^ keybox[loop - 4][i]) % 128;
            }
        }
        else {
            subkey = keybox[loop - 1];
            for (int i = 0; i < 8; ++i) {
                subkey[i] ^= keybox[loop - 4][i];
            }
        }
        keybox.emplace_back(subkey);
        ++loop;
    }

    for (int i = 0; i < loop; ++i) {
        for (int j = 0; j < len; ++j) {
            res[j] ^= keybox[i][j % 8];
        }
        if (i % 2) {
            for (int i = 0; i + 1 < len; ++i) {
                if (i % 2) res[i + 1] ^= (res[i] * 51 >> 1) % 71;
                else res[i + 1] ^= (res[i] * 53 << 1) % 67;
            }
        }
        else {
            for (int i = len - 1; i > 0; --i) {
                if (i % 2) res[i - 1] ^= (res[i] * 51 >> 1) % 71;
                else res[i - 1] ^= (res[i] * 53 << 1) % 67;
            }
        }
        leftstr = res.substr(0, len / 3);
        for (auto &c : leftstr) {
            c ^= keybox[i][i % 8];
        }
        rightstr = res.substr(len / 3, len - len / 3);
        res = rightstr + leftstr;
    }

    res = encode(res);

    return res;
}

trm::Message trm::Decrypt(const trm::Message &str, const std::string &key) noexcept
{
    std::string res = str;
    res = base64Decode(res);

    int len = res.length();

    std::string _key = "&!#^zY-zE)>2d9'cD|*6F<g.h8:_7H=m";
    int keylen = key.size();
    _key = key + _key;

    std::vector<std::string> keybox;

    if (keylen < 32) keylen = 32;
    else if (keylen % 8) keylen += 8 - keylen % 8;

    std::string subkey = "";
    for (int i = 0; i < keylen; ++i) {
        subkey += _key[i];
        if ((i + 1) % 8 == 0) {
            keybox.emplace_back(subkey);
            subkey = "";
        }
    }

    int loop = keybox.size();
    std::string leftstr;
    std::string rightstr;

    while (loop < 8) {
        subkey = "";
        if ((loop + 1) % 4 == 0) {
            subkey = keybox[loop - 1];
            for (int i = 0; i < 8; ++i) {
                subkey[i] = ((subkey[i] * loop) ^ keybox[loop - 4][i]) % 128;
            }
        }
        else {
            subkey = keybox[loop - 1];
            for (int i = 0; i < 8; ++i) {
                subkey[i] ^= keybox[loop - 4][i];
            }
        }
        keybox.emplace_back(subkey);
        ++loop;
    }

    for (int i = loop - 1; i >= 0; --i) {
        rightstr = res.substr(0, len - len / 3);
        leftstr = res.substr(len - len / 3, len / 3);
        for (auto &c : leftstr) {
            c ^= keybox[i][i % 8];
        }
        res = leftstr + rightstr;
        if (i % 2) {
            for (int i = len - 1; i > 0; --i) {
                if ((i - 1) % 2) res[i] ^= (res[i - 1] * 51 >> 1) % 71;
                else res[i] ^= (res[i - 1] * 53 << 1) % 67;
            }
        }
        else {
            for (int i = 1; i < len; ++i) {
                if (i % 2) res[i - 1] ^= (res[i] * 51 >> 1) % 71;
                else res[i - 1] ^= (res[i] * 53 << 1) % 67;
            }
        }
        for (int j = 0; j < len; ++j) {
            res[j] ^= keybox[i][j % 8];
        }
    }

    return res;
}

std::string trm::timestampToString(const std::string &timestamp)
{
    time_t t = std::stoll(timestamp);
    tm local_time;
    localtime_s(&local_time, &t);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
    return buffer;
}
