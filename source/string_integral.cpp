#include "string_integral.hpp"

#define _BASE64CHARS_ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

std::string Encrypt(const std::string &str, const std::string &key) noexcept
{
    static const std::string BASE64CHARS = _BASE64CHARS_;
    auto base64Encode = [&](const unsigned char *str, int len) {
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
                    res += BASE64CHARS[char_4[i]];
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
                res += BASE64CHARS[char_4[j]];
            }

            while ((i++ < 3)) {
                res += '=';
            }
        }

        return res;
    };
    auto encode = [&](auto s) {
        return base64Encode(reinterpret_cast<const unsigned char*>(s.data()), s.size());
    };

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

std::string Decrypt(const std::string &str, const std::string &key) noexcept
{
    static const std::string BASE64CHARS = _BASE64CHARS_;
    auto base64Decode = [&](const std::string &str) {
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
                    char_4[i] = BASE64CHARS.find(char_4[i]) & 0xff;
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
                char_4[j] = BASE64CHARS.find(char_4[j]) & 0xff;
            }

            char_3[0] = (char_4[0] << 2) + ((char_4[1] & 0x30) >> 4);
            char_3[1] = ((char_4[1] & 0xf) << 4) + ((char_4[2] & 0x3c) >> 2);

            for (int j = 0; j < i - 1; ++j) res += char_3[j];
        }
        return res;
    };

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
