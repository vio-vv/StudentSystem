#ifndef __DATA_BASE_HPP__
#define __DATA_BASE_HPP__

/**
 * @brief 由文件系封装而成的数据库类。
 * @namespace bas
 * 
 * @par REQUIRES
 * NONE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include "file_system.hpp"
#include "string_integral.hpp"
#include <algorithm>

namespace dat {

class DataBase {
    friend std::ostream &operator<<(std::ostream &os, const DataBase &db);
public:
    class iterator {
    public:
        using innerInterator = std::vector<std::string>::const_iterator;
        iterator(const std::string *_space, const innerInterator &_it) noexcept : space(_space), it(_it) {}
        iterator &operator++() noexcept { ++it; return *this; }
        iterator operator++(int) noexcept { iterator tmp = *this; it++; return tmp; }
        iterator &operator--() noexcept { --it; return *this; }
        iterator operator--(int) noexcept { iterator tmp = *this; it--; return tmp; }
        iterator operator+(int n) const noexcept { return {space, it + n}; }
        iterator operator-(int n) const noexcept { return {space, it - n}; }
        bool operator==(const iterator &other) const noexcept { return it == other.it; }
        bool operator!=(const iterator &other) const noexcept { return it != other.it; }
        bool operator<(const iterator &other) const noexcept { return it < other.it; }
        bool operator<=(const iterator &other) const noexcept { return it <= other.it; }
        bool operator>(const iterator &other) const noexcept { return it > other.it; }
        bool operator>=(const iterator &other) const noexcept { return it >= other.it; }
        std::pair<std::string, DataBase> operator*() const noexcept { return {*it, DataBase(*space)[*it]}; }
        // std::pair<std::string, DataBase> operator->() const noexcept
        // {
        //     return {*it, DataBase(*space)[*it]};
        // }
    private:
        const std::string *space;
        innerInterator it;
    };
    /**
     * @brief 构造函数，设置工作目录。
     * @param workSpace 工作目录
     */
    explicit DataBase(const std::string &workSpace) noexcept : space(workSpace)
    {
        if (!file::CheckDirectoryExists(workSpace)) {
            assert(false); // Directory not found
            space = ".\\data";
        }
    }
    DataBase(const DataBase &other) noexcept : space(other.space), list(other.list), consideredAsFileOnly(other.consideredAsFileOnly) {}
    /**
     * @brief 当成目录进行索引。
     * @param keyName 键名
     * @return 下一层目录的对象
     */
    DataBase operator[](const std::string &keyName) const noexcept;
    /**
     * @brief 当成目录进行索引。
     * @param index 索引，是对文件名列表的索引，与文件名无任何关系。
     * @return 仅能当成文件的对象
     * @see List()
     */
    DataBase operator[](const unsigned long long index) noexcept;
    /**
     * @brief 当成目录增加元素。
     * @param value 值
     * @note 重载之一，文件名被指定。
     */
    [[deprecated("已弃用。重载函数之一的错误实现，请使用重载函数之一的另一个实现 Push(const std::string &keyName, const std::string &value) const noexcept。该函数可能在未来的 commit 中被彻底移除。")]]
    void Push(const std::pair<std::string, std::string> &key_value) const noexcept;
    /**
     * @brief 当成目录增加元素。
     * @param value 值
     * @note 重载之一，文件名被指定。
     */
    void Push(const std::string &keyName, const std::string &value) const noexcept;
    /**
     * @brief 当成目录增加元素。
     * @param value 值
     * @note 重载之二，文件根据最大元素数编号。
     */
    void Push(const std::string &value) noexcept;
    /**
     * @brief 当成目录进行列举。
     * @return 目录内容，按照文件名排序，不是字典序
     * @note 排序关键字：1）文件名长度，2）字符串顺序。
     */
    std::vector<std::string> List() noexcept;
    /**
     * @brief 当成目录进行迭代。
     * @return 头迭代器
     */
    dat::DataBase::iterator begin() noexcept;
    /**
     * @brief 当成目录进行迭代。
     * @return 尾迭代器
     */
    dat::DataBase::iterator end() const noexcept;
    /**
     * @brief 当成目录进行计数。
     */
    unsigned long long Size() noexcept;
    /**
     * @brief 当成文件（夹）进行判断是否存在。
     * @return 是否存在
     */
    bool Exists() const noexcept;
    /**
     * @brief 当成文件夹判断是否存在指定子文件（夹）
     * @return 是否存在
     */
    bool Exists(const std::string &keyName) const noexcept;
    /**
     * @brief 当成文件进行增改。
     * @param value 值
     * @return 原值
     */
    const std::string &operator=(const std::string &value) const noexcept;
    /**
     * @brief 当成文件进行追加。
     * @param delta 增量
     */
    void operator+=(const std::string &delta) const noexcept;
    /**
     * @brief 当成文件进行读取。
     * @return 值
     */
    operator std::string() const noexcept;
    /**
     * @brief 当成文件进行删除。
     */
    void Clear() const noexcept;
    /**
     * @brief 当成目录进行删除。
     */
    void Remove() const noexcept;
    /**
     * @brief 获取工作目录。
     * @return 工作目录
     */
    const std::string &GetSpace() const noexcept { return space; }
    static bool fail;
private:
    DataBase(const std::string &workSpace, bool considerAsFileOnly) : space(workSpace), consideredAsFileOnly(considerAsFileOnly) {}
    std::string space;
    std::vector<std::string> list;
    bool consideredAsFileOnly = false;
};

std::ostream &operator<<(std::ostream &os, const DataBase &db);

}

#endif
